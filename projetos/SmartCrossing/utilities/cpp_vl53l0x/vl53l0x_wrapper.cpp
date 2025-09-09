#include "VL53L0X.h" // The original C++ header
#include "vl53l0x_wrapper.h" // Our new C wrapper header

// We are now in a .cpp file, so we can implement the C functions
// using C++ features like `new`, `delete`, and class methods.

extern "C" {

// Create a new VL53L0X object and return it as an opaque pointer
VL53L0X_t* VL53L0X_create(i2c_inst_t* i2cPort, uint8_t address) {
    // `new` allocates memory and calls the C++ constructor
    return new VL53L0X(i2cPort, address);
}

// Delete the VL53L0X object
void VL53L0X_destroy(VL53L0X_t* sensor) {
    // `delete` calls the C++ destructor and frees the memory
    if (sensor) {
        delete sensor;
    }
}

// Call the init method on the object
bool VL53L0X_init(VL53L0X_t* sensor, bool io_2v8) {
    if (!sensor) return false;
    // Cast the opaque pointer back to the C++ class pointer and call the method
    return sensor->init(io_2v8);
}

// Call the readRangeSingleMillimeters method
uint16_t VL53L0X_readRangeSingleMillimeters(VL53L0X_t* sensor) {
    if (!sensor) return 65535; // Return error value
    return sensor->readRangeSingleMillimeters();
}

// Call the startContinuous method
void VL53L0X_startContinuous(VL53L0X_t* sensor, uint32_t period_ms) {
    if (!sensor) return;
    sensor->startContinuous(period_ms);
}

// Call the stopContinuous method
void VL53L0X_stopContinuous(VL53L0X_t* sensor) {
    if (!sensor) return;
    sensor->stopContinuous();
}

// Call the readRangeContinuousMillimeters method
uint16_t VL53L0X_readRangeContinuousMillimeters(VL53L0X_t* sensor) {
    if (!sensor) return 65535;
    return sensor->readRangeContinuousMillimeters();
}

// Call the timeoutOccurred method
bool VL53L0X_timeoutOccurred(VL53L0X_t* sensor) {
    if (!sensor) return true;
    return sensor->timeoutOccurred();
}

} // extern "C"
