#pragma once

#include <esp_err.h>
#include <esp_matter.h>

#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
#include "esp_openthread_types.h"
#endif

/**
 * @brief A FreeRTOS task to periodically update sensor attributes based on a given endpoint ID.
 *
 * @param pvParameter Pointer to the `endpoint_id` (expected to be of type `uint16_t*`).
 *
 * This task initializes a BMX280 sensor and reads temperature, pressure, and relative
 * humidity measurements. It updates these attributes using the `app_driver_attribute_update`
 * function every 30 seconds, using the provided `endpoint_id`.
 * The task runs indefinitely.
 *
 * @note Ensure that `sensor_init` and `app_driver_attribute_update` functions
 * are properly defined and accessible. The `pvParameter` should be cast to `uint16_t*`.
 */
[[noreturn]] void app_driver_attribute_update_task(void *pvParameter);

/**
 * @brief Updates a specified attribute within a given cluster and endpoint.
 *
 * This function updates the value of a specified attribute in a given cluster
 * on a specified endpoint, converting the provided value to the appropriate format
 * as needed for Matter compliance.
 *
 * @param endpoint_id   The identifier of the endpoint where the attribute resides.
 * @param cluster_id    The identifier of the cluster containing the attribute to be updated.
 * @param attribute_id  The identifier of the attribute to be updated.
 * @param number        Pointer to the new value to set for the attribute (as a float).
 *
 * @return esp_err_t    Returns ESP_OK on successful update, or an appropriate error code on failure.
 */
esp_err_t app_driver_attribute_update(uint16_t endpoint_id,
                                      uint32_t cluster_id,
                                      uint32_t attribute_id,
                                      const float *number);

#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
#define ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG()                                           \
    {                                                                                   \
        .radio_mode = RADIO_MODE_NATIVE,                                                \
    }

#define ESP_OPENTHREAD_DEFAULT_HOST_CONFIG()                                            \
    {                                                                                   \
        .host_connection_mode = HOST_CONNECTION_MODE_NONE,                              \
    }

#define ESP_OPENTHREAD_DEFAULT_PORT_CONFIG()                                            \
    {                                                                                   \
        .storage_partition_name = "nvs", .netif_queue_size = 10, .task_queue_size = 10, \
    }
#endif
