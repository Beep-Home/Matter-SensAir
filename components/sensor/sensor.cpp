#include <sensor.h>

#include <esp_log.h>
#include <cstdlib>

static const char *TAG = "sensor";

bmx280_t *sensor_init() {
    i2c_config_t i2c_cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SENSOR_I2C_SDA_IO,
        .scl_io_num = SENSOR_I2C_SCL_IO,
        .sda_pullup_en = false,
        .scl_pullup_en = false,
        .master = {
            .clk_speed = SENSOR_I2C_FREQ_HZ
        }
    };

    ESP_ERROR_CHECK(i2c_param_config(SENSOR_I2C_MASTER_NUM, &i2c_cfg));
    ESP_ERROR_CHECK(i2c_driver_install(SENSOR_I2C_MASTER_NUM, I2C_MODE_MASTER, 0, 0, 0));

    bmx280_t *bmx280 = bmx280_create(SENSOR_I2C_MASTER_NUM);

    if (!bmx280) {
        ESP_LOGI(TAG, "Could not create an instance of the BMX280 driver.");
        return bmx280;
    }

    ESP_ERROR_CHECK(bmx280_init(bmx280));

    bmx280_config_t bmx_cfg = BMX280_DEFAULT_CONFIG;

    ESP_ERROR_CHECK(bmx280_configure(bmx280, &bmx_cfg));

    return bmx280;
}

void sensor_read(bmx280_t *bmx280, float *temperature, float *pressure, float *humidity) {
    ESP_ERROR_CHECK(bmx280_setMode(bmx280, BMX280_MODE_FORCE));

    do {
        vTaskDelay(pdMS_TO_TICKS(1));
    } while (bmx280_isSampling(bmx280));

    ESP_ERROR_CHECK(bmx280_readoutFloat(bmx280, temperature, pressure, humidity));

    ESP_LOGI(TAG, "Readout (temperature = %f, pressure = %f, humidity = %f)", *temperature, *pressure, *humidity);
}