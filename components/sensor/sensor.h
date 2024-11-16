#pragma once

#include "bmx280.h"
#include "driver/i2c.h"

#define SENSOR_I2C_MASTER_NUM I2C_NUM_0        // I2C port number for master
#define SENSOR_I2C_SDA_IO GPIO_NUM_22          // I2C SDA pin
#define SENSOR_I2C_SCL_IO GPIO_NUM_12          // I2C SCL pin
#define SENSOR_I2C_FREQ_HZ 100000              // I2C clock frequency (100 kHz)

/**
 * @brief Initialize the BMX280 sensor.
 *
 * Configures the I2C interface and initializes the BMX280 sensor with default settings.
 *
 * @return Pointer to the initialized `bmx280_t` structure.
 *         Returns NULL if the sensor could not be created.
 */
bmx280_t *sensor_init();

/**
 * @brief Read temperature, pressure, and humidity from the BMX280 sensor.
 *
 * Forces a reading from the sensor in forced mode and retrieves the values.
 *
 * @param[in] bmx280 Pointer to the `bmx280_t` sensor instance.
 * @param[out] temperature Pointer to store the temperature value in degrees Celsius.
 * @param[out] pressure Pointer to store the pressure value in Pascals.
 * @param[out] humidity Pointer to store the humidity value in percentage (%).
 */
void sensor_read(bmx280_t *bmx280, float *temperature, float *pressure, float *humidity);
