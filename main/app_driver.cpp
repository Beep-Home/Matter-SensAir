#include <esp_log.h>
#include <esp_matter.h>

using namespace chip::app::Clusters;
using namespace esp_matter;

static const char *TAG = "app_driver";

esp_err_t app_driver_attribute_update(uint16_t endpoint_id, uint32_t cluster_id, uint32_t attribute_id, float *number) {
    esp_err_t err = ESP_OK;

    attribute_t *attribute = attribute::get(endpoint_id, cluster_id, attribute_id);
    if (!attribute) {
        ESP_LOGE(TAG, "Attribute not found (Endpoint: %u, Cluster: %lu, Attribute: %lu)",
                 endpoint_id, cluster_id, attribute_id);
        return ESP_FAIL;
    }

    esp_matter_attr_val_t val = esp_matter_invalid(nullptr);
    err = attribute::get_val(attribute, &val);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to retrieve attribute value (Endpoint: %u, Cluster: %lu, Attribute: %lu)",
                 endpoint_id, cluster_id, attribute_id);
        return ESP_FAIL;
    }

    switch (cluster_id) {
        case PressureMeasurement::Id:
            // Convert pressure to Matter standard (divide by 100).
            val.val.i = static_cast<int>(*number / 100);
            ESP_LOGD(TAG, "Converting to Matter standard units: Raw Value = %.2f, Converted (divided by 100) = %d", *number, val.val.i);
            break;

        case TemperatureMeasurement::Id:
        case RelativeHumidityMeasurement::Id:
            // Convert temperature/humidity to Matter standard (multiply by 100).
            val.val.i = static_cast<int>(*number * 100);
            ESP_LOGD(TAG, "Converting to Matter standard units: Raw Value = %.2f, Converted (multiplied by 100) = %d", *number, val.val.i);
            break;

        default:
            val.val.i = static_cast<int>(*number);
            ESP_LOGW(TAG, "Unknown Measurement ID: Raw Value = %.2f, Converted (direct cast) = %d", *number, val.val.i);
            break;
    }

    ESP_LOGI(TAG, "Updating attribute (Endpoint: %u, Cluster: %lu, Attribute: %lu) to value: %i",
             endpoint_id, cluster_id, attribute_id, val.val.i);

    err = attribute::update(endpoint_id, cluster_id, attribute_id, &val);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to update attribute value (Endpoint: %u, Cluster: %lu, Attribute: %lu)",
                 endpoint_id, cluster_id, attribute_id);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Successfully updated attribute (Endpoint: %u, Cluster: %lu, Attribute: %lu)",
             endpoint_id, cluster_id, attribute_id);
    return ESP_OK;
}
