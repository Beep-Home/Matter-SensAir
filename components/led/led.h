#pragma once

#include <led_strip.h>

/**
 * @brief Initializes the onboard LED strip.
 *
 * This function configures the LED strip using the RMT peripheral and clears
 * any existing LED data. It must be called before using other LED functions.
 */
void led_init();

/**
 * @brief Task that blinks an LED at a specified rate until terminated.
 *
 * This task controls an LED strip to blink the first LED with a specified
 * frequency. It toggles the LED on and off at a rate determined by the
 * `blinksPerSecond` variable, which is set to 4 blinks per second by default.
 * The task checks for termination status on each cycle and exits cleanly when
 * requested.
 *
 * @param pvParameter Pointer to a boolean flag (`bool *terminate_task`).
 *                    When the boolean flag is set to `true`, the task will
 *                    stop blinking and terminate itself by calling `vTaskDelete`.
 */
void led_blink_task(void *pvParameter);