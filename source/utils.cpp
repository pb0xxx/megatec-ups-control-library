// utils.cpp
#include "ups.h"

/**
 * Calculates a special value based on the number of minutes.
 * The value is used for UPS test functions.
 * @param minutes Number of minutes (1-99).
 * @return Calculated value or -1 if the input is invalid.
 */
int calculate_time(int minutes) {
    if (minutes < 1 || minutes > 99) {
        return -1;  // Invalid input
    }

    int base = 100;
    int level = (minutes - 1) / 10;
    int value = base + minutes + level * 6;

    if (minutes % 10 == 0) {
        value += 6;
    }

    return value;
}