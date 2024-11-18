#pragma once

#include "driver/gpio.h"

#define BOOT_BUTTON_GPIO GPIO_NUM_9

/**
 * @brief Task to monitor the boot button press and release.
 *
 * This function continuously monitors the boot button for a press (active low).
 * When the button is released, it invokes the provided callback function.
 *
 * @param pvParameter Pointer to a callback function executed on button release.
 */
void button_monitor_task(void *pvParameter);
