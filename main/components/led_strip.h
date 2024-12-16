#pragma once

#include <led_strip.h>

/**
 * @brief Initializes the onboard LED strip.
 *
 * This function configures the LED strip using the RMT peripheral and clears
 * any existing LED data. It must be called before using other LED functions.
 */
void led_strip_init();

/**
 * @brief Parameters for the LED strip blink task.
 *
 * This structure holds the configuration for the LED strip blinking task.
 */
struct LedStripBlinkTaskParameter {
    /**
     * @brief Red color intensity.
     *
     * Specifies the intensity of the red color channel (0-255).
     */
    uint8_t red;

    /**
     * @brief Green color intensity.
     *
     * Specifies the intensity of the green color channel (0-255).
     */
    uint8_t green;

    /**
     * @brief Blue color intensity.
     *
     * Specifies the intensity of the blue color channel (0-255).
     */
    uint8_t blue;

    /**
     * @brief Blinks per minute.
     *
     * Defines the number of blinks per minute for the LED strip. For example,
     * a value of 120 means the LED blinks 120 times in one minute (2 blinks per second).
     */
    uint16_t blinksPerMinute;

    /**
     * @brief Task termination flag.
     *
     * A pointer to a boolean value that indicates whether the task should terminate.
     * If the value is set to true, the task will clean up and terminate.
     */
    volatile bool *terminateTask;
};

/**
 * @brief LED strip blinking task.
 *
 * This task blinks the LED strip with the specified color and frequency. It continues
 * until the terminateTask flag is set to true.
 *
 * @param pvParameter Pointer to LedStripBlinkTaskParameter containing the task parameters.
 */
void led_strip_blink_task(void *pvParameter);