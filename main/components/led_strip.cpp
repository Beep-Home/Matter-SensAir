#include "led_strip.h"

#include <esp_log.h>
#include <cstdlib>

static const char *TAG = "LED_STRIP";

static led_strip_handle_t led_strip;

void led_strip_init()
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

void led_strip_blink_task(void *pvParameter)
{
    auto *params = (LedStripBlinkTaskParameter *)pvParameter;

    auto blinksPerSecond = static_cast<double>(params->blinksPerMinute) / 60.0;
    auto delayMs = static_cast<uint16_t>(1000 / (blinksPerSecond * 2.0));

    while (true) {
        led_strip_set_pixel(led_strip, 0, params->red, params->green, params->blue);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(delayMs));

        led_strip_set_pixel(led_strip, 0, 0, 0, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(delayMs));

        if (*params->terminateTask) {
            vTaskDelete(nullptr);
            break;
        }
    }
}
