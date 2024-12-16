#include "led.h"

#include <esp_log.h>
#include <cstdlib>

static const char *TAG = "LED_STRIP";

static led_strip_handle_t led_strip;

void led_init()
{
    ESP_LOGI(TAG, "Initializing onboard LED strip");

    led_strip_config_t strip_config = {
            .strip_gpio_num = CONFIG_LED_GPIO,
            .max_leds = 1
    };

    led_strip_rmt_config_t rmt_config = {
            .resolution_hz = 10'000'000,
            .flags = {
                    .with_dma = false
            }
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    led_strip_clear(led_strip);
}

void led_blink_task(void *pvParameter)
{
    bool *terminate_task = (bool *)pvParameter;

    uint8_t blinksPerSecond = 4;
    uint16_t delayMs = 1000 / (blinksPerSecond * 2);

    while (true) {
        led_strip_set_pixel(led_strip, 0, 255, 0, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(delayMs));

        led_strip_set_pixel(led_strip, 0, 0, 0, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(delayMs));

        if (*terminate_task) {
            vTaskDelete(nullptr);
            break;
        }
    }
}
