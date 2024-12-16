#include <esp_err.h>
#include <esp_log.h>
#include <nvs_flash.h>

#include <esp_matter.h>
#include <esp_matter_console.h>

#include <common_macros.h>
#include <app_priv.h>
#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
#include <platform/ESP32/OpenthreadLauncher.h>
#endif

#include <app/server/CommissioningWindowManager.h>
#include <app/server/Server.h>

#include "components/button.h"
#include "components/led.h"

using namespace esp_matter;
using namespace esp_matter::attribute;
using namespace esp_matter::endpoint;
using namespace chip::app::Clusters;

constexpr auto k_timeout_seconds = 300;
static const char *TAG = "app_main";

static volatile bool terminate_identification_task = false;

#if CONFIG_ENABLE_ENCRYPTED_OTA
extern const char decryption_key_start[] asm("_binary_esp_image_encryption_key_pem_start");
extern const char decryption_key_end[] asm("_binary_esp_image_encryption_key_pem_end");

static const char *s_decryption_key = decryption_key_start;
static const uint16_t s_decryption_key_len = decryption_key_end - decryption_key_start;
#endif // CONFIG_ENABLE_ENCRYPTED_OTA

// Event Callback
static void app_event_cb(const ChipDeviceEvent *event, intptr_t arg)
{
    switch (event->Type) {
    case chip::DeviceLayer::DeviceEventType::kInterfaceIpAddressChanged:
        ESP_LOGI(TAG, "Interface IP Address changed");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningComplete:
        ESP_LOGI(TAG, "Commissioning complete");
        break;

    case chip::DeviceLayer::DeviceEventType::kFailSafeTimerExpired:
        ESP_LOGI(TAG, "Commissioning failed, fail safe timer expired");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStarted:
        ESP_LOGI(TAG, "Commissioning session started");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStopped:
        ESP_LOGI(TAG, "Commissioning session stopped");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningWindowOpened:
        ESP_LOGI(TAG, "Commissioning window opened");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningWindowClosed:
        ESP_LOGI(TAG, "Commissioning window closed");
        break;

    case chip::DeviceLayer::DeviceEventType::kFabricRemoved: {
        ESP_LOGI(TAG, "Fabric removed successfully");
        if (chip::Server::GetInstance().GetFabricTable().FabricCount() == 0) {
            chip::CommissioningWindowManager &commissionMgr = chip::Server::GetInstance().GetCommissioningWindowManager();
            if (!commissionMgr.IsCommissioningWindowOpen()) {
                constexpr auto kTimeoutSeconds = chip::System::Clock::Seconds16(k_timeout_seconds);
                CHIP_ERROR err = commissionMgr.OpenBasicCommissioningWindow(kTimeoutSeconds,
                                                                            chip::CommissioningWindowAdvertisement::kDnssdOnly);
                if (err != CHIP_NO_ERROR) {
                    ESP_LOGE(TAG, "Failed to open commissioning window, err:%" CHIP_ERROR_FORMAT, err.Format());
                }
            }
        }
        break;
    }

    case chip::DeviceLayer::DeviceEventType::kFabricWillBeRemoved:
        ESP_LOGI(TAG, "Fabric will be removed");
        break;

    case chip::DeviceLayer::DeviceEventType::kFabricUpdated:
        ESP_LOGI(TAG, "Fabric is updated");
        break;

    case chip::DeviceLayer::DeviceEventType::kFabricCommitted:
        ESP_LOGI(TAG, "Fabric is committed");
        break;

    case chip::DeviceLayer::DeviceEventType::kBLEDeinitialized:
        ESP_LOGI(TAG, "BLE de-initialized and memory reclaimed");
        break;

    default:
        break;
    }
}

// This callback is invoked when clients interact with the Identify Cluster.
// In the callback implementation, an endpoint can identify itself. (e.g., by flashing an LED or light).
static esp_err_t app_identification_cb(identification::callback_type_t type, uint16_t endpoint_id, uint8_t effect_id,
                                       uint8_t effect_variant, void *priv_data)
{
    ESP_LOGI(TAG, "Identification callback: type: %u, effect: %u, variant: %u", type, effect_id, effect_variant);

    if (type == esp_matter::identification::START) {
        terminate_identification_task = false;
        xTaskCreate(led_blink_task, "led_blink_task", 4096, (void *)&terminate_identification_task, 5, nullptr);
    } else if (type == esp_matter::identification::STOP) {
        terminate_identification_task = true;
    }

    return ESP_OK;
}

// This callback is called for every attribute update. The callback implementation shall
// handle the desired attributes and return an appropriate error code. If the attribute
// is not of your interest, please do not return an error code and strictly return ESP_OK.
static esp_err_t app_attribute_update_cb(attribute::callback_type_t type, uint16_t endpoint_id, uint32_t cluster_id,
                                         uint32_t attribute_id, esp_matter_attr_val_t *val, void *priv_data)
{
    ESP_LOGI(TAG, "Attribute Update callback: type: %u, endpoint: %u, cluster: %lu, attribute: %lu, value: %lu", type, endpoint_id, cluster_id, attribute_id, uint32_t(val));
    return ESP_OK;
}

static void app_factory_reset_cb()
{
    ESP_LOGW(TAG, "Factory reset started");
    chip::DeviceLayer::ConfigurationMgr().InitiateFactoryReset();
}

extern "C" void app_main()
{
    esp_err_t err = ESP_OK;

    nvs_flash_init();

    led_init();

    ButtonMonitorTaskParameter params = {
        .pin = gpio_num_t(CONFIG_BUTTON_GPIO),
        .longPressThreshold = 10000, // 10000ms = 10 seconds
        .onPressCallback = nullptr,
        .onLongPressCallback = app_factory_reset_cb
    };
    xTaskCreate(button_monitor_task, "button_monitor_task", 4096, &params, 10, nullptr);

    node::config_t node_config;
    node_t *node = node::create(&node_config, app_attribute_update_cb, app_identification_cb);

    temperature_sensor::config_t temperature_measurement_config;
    endpoint_t *sensor_endpoint = temperature_sensor::create(node, &temperature_measurement_config, ENDPOINT_FLAG_NONE, nullptr);
    uint16_t endpoint_id = endpoint::get_id(sensor_endpoint);

    cluster_t *temperature_cluster = cluster::create(sensor_endpoint, TemperatureMeasurement::Id, CLUSTER_FLAG_SERVER);
    attribute::create(temperature_cluster, TemperatureMeasurement::Attributes::MeasuredValue::Id, ATTRIBUTE_FLAG_NONE, esp_matter_uint16(0));

    cluster_t *pressure_cluster = cluster::create(sensor_endpoint, PressureMeasurement::Id, CLUSTER_FLAG_SERVER);
    attribute::create(pressure_cluster, PressureMeasurement::Attributes::MeasuredValue::Id, ATTRIBUTE_FLAG_NONE, esp_matter_uint16(0));

    cluster_t *relative_humidity_cluster = cluster::create(sensor_endpoint, RelativeHumidityMeasurement::Id, CLUSTER_FLAG_SERVER);
    attribute::create(relative_humidity_cluster, RelativeHumidityMeasurement::Attributes::MeasuredValue::Id, ATTRIBUTE_FLAG_NONE, esp_matter_uint16(0));

    xTaskCreate(app_driver_attribute_update_task, "attribute_update_task", 4096, &endpoint_id, 5, nullptr);

#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
    /* Set OpenThread platform config */
    esp_openthread_platform_config_t config = {
        .radio_config = ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_OPENTHREAD_DEFAULT_HOST_CONFIG(),
        .port_config = ESP_OPENTHREAD_DEFAULT_PORT_CONFIG(),
    };
    set_openthread_platform_config(&config);
#endif

    err = esp_matter::start(app_event_cb);
    ABORT_APP_ON_FAILURE(err == ESP_OK, ESP_LOGE(TAG, "Failed to start Matter, err:%d", err));

#if CONFIG_ENABLE_CHIP_SHELL
    esp_matter::console::diagnostics_register_commands();
    esp_matter::console::wifi_register_commands();
#if CONFIG_OPENTHREAD_CLI
    esp_matter::console::otcli_register_commands();
#endif
    esp_matter::console::init();
#endif
}
