#ifndef VL53L0X_C_WRAPPER_H
#define VL53L0X_C_WRAPPER_H

#include "hardware/i2c.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
class VL53L0X;
typedef VL53L0X VL53L0X_t;
#else
typedef struct VL53L0X_t VL53L0X_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates and allocates a new VL53L0X sensor object.
 *
 * @param i2cPort The I2C instance (e.g., i2c0, i2c1).
 * @param address The I2C address of the sensor.
 * @return A pointer to the sensor object, or NULL on failure.
 */
VL53L0X_t* VL53L0X_create(i2c_inst_t* i2cPort, uint8_t address);

/**
 * @brief Destroys and frees the VL53L0X sensor object.
 *
 * @param sensor A pointer to the sensor object.
 */
void VL53L0X_destroy(VL53L0X_t* sensor);

/**
 * @brief Initializes the sensor.
 *
 * @param sensor A pointer to the sensor object.
 * @param io_2v8 Set to true if using 2.8V I/O, false for 1.8V.
 * @return true on success, false on failure.
 */
bool VL53L0X_init(VL53L0X_t* sensor, bool io_2v8);

/**
 * @brief Performs a single-shot range measurement.
 *
 * @param sensor A pointer to the sensor object.
 * @return The range in millimeters, or 65535 on timeout.
 */
uint16_t VL53L0X_readRangeSingleMillimeters(VL53L0X_t* sensor);

/**
 * @brief Starts continuous ranging measurements.
 *
 * @param sensor A pointer to the sensor object.
 * @param period_ms Inter-measurement period in milliseconds. 0 for back-to-back mode.
 */
void VL53L0X_startContinuous(VL53L0X_t* sensor, uint32_t period_ms);

/**
 * @brief Stops continuous ranging measurements.
 *
 * @param sensor A pointer to the sensor object.
 */
void VL53L0X_stopContinuous(VL53L0X_t* sensor);

/**
 * @brief Reads a range measurement when in continuous mode.
 *
 * @param sensor A pointer to the sensor object.
 * @return The range in millimeters, or 65535 on timeout.
 */
uint16_t VL53L0X_readRangeContinuousMillimeters(VL53L0X_t* sensor);

/**
 * @brief Checks if a timeout occurred during the last read.
 *
 * @param sensor A pointer to the sensor object.
 * @return true if a timeout occurred, false otherwise.
 */
bool VL53L0X_timeoutOccurred(VL53L0X_t* sensor);

#ifdef __cplusplus
}
#endif

#endif // VL53L0X_C_WRAPPER_H
