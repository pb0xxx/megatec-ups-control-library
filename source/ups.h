// ups.h
#ifndef UPS_H
#define UPS_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

#include <libusb-1.0/libusb.h>

// Constants for ASCII range and special characters
#define ASCII_MIN 32
#define ASCII_MAX 126
#define CHAR_QUOTE 34
#define CHAR_BACKTICK 96
#define CHAR_PAREN 40

// Maximum size for requests without return data
#define REQ_NO_RET_MAX 3

// Macro to check if a character is valid
#define IS_VALID_CHAR(c) ((c) >= ASCII_MIN && (c) <= ASCII_MAX && (c) != CHAR_QUOTE && (c) != CHAR_BACKTICK && (c) != CHAR_PAREN)

// Global result buffer for responses
extern char result[256];

extern "C" {
    EXPORT libusb_context* initialize();
    EXPORT libusb_device_handle* open_device(libusb_context *ctx, int vendor_id, int product_id);
    EXPORT int get_string_descriptor(libusb_device_handle *dev_handle, int index, uint16_t wLength);
    EXPORT void close_device(libusb_device_handle *dev_handle, libusb_context *ctx);
    EXPORT int calculate_time(int minutes);
    EXPORT char* get_last_response();
    EXPORT int get_ups_name(libusb_device_handle *dev_handle);
    EXPORT int get_ups_status(libusb_device_handle *dev_handle);
    EXPORT int get_ups_status_no_ack(libusb_device_handle *dev_handle);
    EXPORT int test_ups(libusb_device_handle *dev_handle);
    EXPORT int test_ups_until_battery_low(libusb_device_handle *dev_handle);
    EXPORT int switch_ups_beep(libusb_device_handle *dev_handle);
    EXPORT int shutdown_ups(libusb_device_handle *dev_handle);
    EXPORT int abort_ups_test(libusb_device_handle *dev_handle);
    EXPORT int get_ups_rating(libusb_device_handle *dev_handle);
    EXPORT int test_ups_with_time(libusb_device_handle *dev_handle, int minutes);
}

#endif

