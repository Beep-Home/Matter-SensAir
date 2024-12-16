#include "button.h"

#include "freertos/FreeRTOS.h"

#include <esp_log.h>

static const char *TAG = "BOOT_BUTTON";

void button_monitor_task(void *pvParameter) {
    void (*on_button_release_callback)(void) = (void (*)(void)) pvParameter;

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << gpio_num_t(BOOT_BUTTON_GPIO)),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    ESP_LOGI(TAG, "Boot button monitoring task started!");

    while (true) {
        if (!gpio_get_level(gpio_num_t(BOOT_BUTTON_GPIO))) {  // Active low check
            ESP_LOGI(TAG, "Boot button pressed!");
            while (!gpio_get_level(gpio_num_t(BOOT_BUTTON_GPIO))) vTaskDelay(pdMS_TO_TICKS(10));  // Debounce
            ESP_LOGI(TAG, "Boot button released!");

            if (on_button_release_callback) on_button_release_callback();
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}