// ups.cpp
#include "ups.h"

char result[256];  // Global buffer for storing the response

/**
 * Initializes the libusb context.
 * @return Initialized libusb context, or NULL if initialization fails.
 */
libusb_context* initialize() {
    libusb_context *ctx = nullptr;
    int r = libusb_init(&ctx);
    if (r < 0) {
        return NULL;
    }
    return ctx;
}

/**
 * Opens a USB device by Vendor ID (VID) and Product ID (PID).
 * @param ctx The libusb context.
 * @param vendor_id The Vendor ID.
 * @param product_id The Product ID.
 * @return Handle to the opened USB device, or NULL if opening fails.
 */
libusb_device_handle* open_device(libusb_context *ctx, int vendor_id, int product_id) {
    return libusb_open_device_with_vid_pid(ctx, vendor_id, product_id);
}

/**
 * Closes the USB device and exits the libusb context.
 * @param dev_handle Handle to the opened USB device.
 * @param ctx The libusb context.
 */
void close_device(libusb_device_handle *dev_handle, libusb_context *ctx) {
    libusb_close(dev_handle);
    libusb_exit(ctx);
}

/**
 * Retrieves the last response stored in the global result buffer.
 * @return Pointer to the global result buffer.
 */
char* get_last_response() {
    return result;
}

/**
 * Retrieves a string descriptor from the UPS device.
 * @param dev_handle Handle to the USB device.
 * @param index Index of the string descriptor.
 * @param wLength Length of the string descriptor.
 * @return 0 if successful, 1 if the function likely returns no data, -1 if an error occurs.
 */
int get_string_descriptor(libusb_device_handle *dev_handle, int index, uint16_t wLength) {
    unsigned char data[256];
    int j = 0;
    int r = libusb_control_transfer(dev_handle, LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_DEVICE,
            LIBUSB_REQUEST_GET_DESCRIPTOR, (LIBUSB_DT_STRING << 8) | index, 0,
            data, wLength, 0);

    if (r >= 3) {
        for (int i = 0; i < r; i++) {
            if (IS_VALID_CHAR(data[i])) {
                result[j++] = (char)data[i];
            }
        }
        result[j] = '\0';
        return 0;
    }

    if (r < REQ_NO_RET_MAX) {
        return 1;
    }

    return -1;
}