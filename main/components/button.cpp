#include "button.h"

#include "freertos/FreeRTOS.h"
#include <esp_log.h>

static const char *TAG = "BUTTON";

void button_monitor_task(void *pvParameter) {
    auto *params = (ButtonMonitorTaskParameter *)pvParameter;
    gpio_num_t pin = params->pin;
    unsigned long longPressThreshold = params->longPressThreshold;
    button_callback_t onPressCallback = params->onPressCallback;
    button_callback_t onLongPressCallback = params->onLongPressCallback;

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    ESP_LOGI(TAG, "Button monitoring task started for pin %d", pin);

    while (true) {
        if (!gpio_get_level(pin)) {
            ESP_LOGI(TAG, "Button on pin %d pressed!", pin);
            TickType_t pressStartTick = xTaskGetTickCount();

            while (!gpio_get_level(pin)) {
                vTaskDelay(pdMS_TO_TICKS(10));
            }

            ESP_LOGI(TAG, "Button on pin %d released!", pin);
            TickType_t pressEndTick = xTaskGetTickCount();
            TickType_t pressDurationTicks = pressEndTick - pressStartTick;
            unsigned long pressDurationMs = pressDurationTicks * portTICK_PERIOD_MS;

            if (pressDurationMs >= longPressThreshold && onLongPressCallback) {
                ESP_LOGI(TAG, "Long press detected on pin %d (Duration: %lu ms)", pin, pressDurationMs);
                onLongPressCallback();
            } else if (onPressCallback) {
                ESP_LOGI(TAG, "Short press detected on pin %d (Duration: %lu ms)", pin, pressDurationMs);
                onPressCallback();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}