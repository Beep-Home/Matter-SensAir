#pragma once

#include <esp_err.h>
#include <esp_matter.h>

#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
#include "esp_openthread_types.h"
#endif

/**
 * @brief Update a specific attribute in a given cluster and endpoint.
 *
 * @param endpoint_id   The ID of the endpoint to update.
 * @param cluster_id    The ID of the cluster containing the attribute.
 * @param attribute_id  The ID of the attribute to update.
 * @param number        The new value to set for the attribute.
 *
 * @return esp_err_t    ESP_OK on success, or an error code on failure.
 */
esp_err_t app_driver_attribute_update(uint16_t endpoint_id,
                                      uint32_t cluster_id,
                                      uint32_t attribute_id,
                                      float number);

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
