#pragma once

#include "driver/gpio.h"

/**
 * @brief Callback function type for button events.
 *
 * The callback is invoked when a button press or long press is detected.
 */
typedef void (*button_callback_t)(void);

/**
 * @brief Parameters for the button monitoring task.
 *
 * This structure holds the configuration and callback functions
 * for monitoring a specific button.
 */
struct ButtonMonitorTaskParameter {
    gpio_num_t pin;                        ///< GPIO pin assigned to the button
    unsigned long longPressThreshold;      ///< Threshold duration (in milliseconds) to qualify as a long press
    button_callback_t onPressCallback;     ///< Callback for a short button press event
    button_callback_t onLongPressCallback; ///< Callback for a long button press event
};

/**
 * @brief Task to monitor button presses and detect press types.
 *
 * This task configures the GPIO pin for input, and continuously monitors
 * the button state to detect press events. When a press or long press is
 * detected, the corresponding callback function is invoked if defined.
 *
 * @param pvParameters Pointer to a ButtonMonitorTaskParameter structure
 *                     containing the button's configuration and callbacks.
 *
 * Example usage:
 * @code
 * ButtonMonitorTaskParameter params = {
 *     .pin = GPIO_NUM_0,
 *     .longPressThreshold = 1000, // 1000ms = 1 second
 *     .onPressCallback = onButtonPress,
 *     .onLongPressCallback = onButtonLongPress
 * };
 * xTaskCreate(button_monitor_task, "Button Task", 2048, &params, 5, NULL);
 * @endcode
 */
[[noreturn]] void button_monitor_task(void *pvParameters);
