// operations.cpp
#include "ups.h"
#include <chrono>
#include <thread>

/**
 * Retrieves the name of the UPS.
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int get_ups_name(libusb_device_handle *dev_handle) {
    return get_string_descriptor(dev_handle, 2, 256);
}

/**
 * Retrieves the status of the UPS.
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int get_ups_status(libusb_device_handle *dev_handle) {
    get_string_descriptor(dev_handle, 3, 256);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return get_string_descriptor(dev_handle, 3, 256);
}

/**
 * Retrieves the UPS status without acknowledgment (no ACK).
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int get_ups_status_no_ack(libusb_device_handle *dev_handle) {
    return get_string_descriptor(dev_handle, 3, 256);
}

/**
 * Tests the UPS for 10 seconds.
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int test_ups(libusb_device_handle *dev_handle) {
    return get_string_descriptor(dev_handle, 4, 256);
}

/**
 * Tests the UPS until the battery is low.
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int test_ups_until_battery_low(libusb_device_handle *dev_handle) {
    return get_string_descriptor(dev_handle, 5, 256);
}

/**
 * Toggles the UPS beep signal on or off.
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int switch_ups_beep(libusb_device_handle *dev_handle) {
    return get_string_descriptor(dev_handle, 7, 256);
}

/**
 * Shuts down the UPS after 1 minute.
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int shutdown_ups(libusb_device_handle *dev_handle) {
    return get_string_descriptor(dev_handle, 105, 2460);
}

/**
 * Aborts any ongoing UPS test.
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int abort_ups_test(libusb_device_handle *dev_handle) {
    return get_string_descriptor(dev_handle, 11, 256);
}

/**
 * Retrieves the rating of the UPS.
 * @param dev_handle Handle to the USB device.
 * @return 0 if successful, otherwise an error code.
 */
int get_ups_rating(libusb_device_handle *dev_handle) {
    return get_string_descriptor(dev_handle, 13, 256);
}

/**
 * Tests the UPS for a specified number of minutes.
 * @param dev_handle Handle to the USB device.
 * @param minutes Number of minutes to run the test.
 * @return Calculated value or -1 if the input is invalid.
 */
int test_ups_with_time(libusb_device_handle *dev_handle, int minutes) {
    int c_minutes = calculate_time(minutes);
    get_string_descriptor(dev_handle, 6, c_minutes);
    return c_minutes;
}
