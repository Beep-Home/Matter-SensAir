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
 * @brief A FreeRTOS task to blink the onboard LED.
 *
 * @param pvParameter Unused parameter (can be set to nullptr).
 *
 * This task blinks the LED at a frequency of 4 blinks per second for a total duration
 * of 3 seconds. It deletes itself after completing the blinking sequence.
 */
void led_blink_task(void *pvParameter);