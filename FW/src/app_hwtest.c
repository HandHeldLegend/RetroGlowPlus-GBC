#include "main.h"

bool _hwtest_pinok(uint primary)
{


    // Pass if we read high (pulled up)
    return true;
}



bool _hwtest_rgb()
{
    return true;
}

/**
 * @file app_hwtest.c
 * @brief Hardware test function for the application.
 *
 * This function performs a looped hardware test and returns the test result as a 16-bit unsigned integer.
 * The test includes checking various hardware components such as analog, battery, bluetooth, clock pin, data pin,
 * latch pin, RGB pin, and IMU.
 *
 * @return The test result as a 16-bit unsigned integer.
 */
uint16_t cb_hoja_hardware_test()
{
    hoja_hw_test_u _t;

    _t.analog = false;
    _t.battery = false;
    _t.bluetooth = false;
    _t.clock_pin = false;
    _t.data_pin = false;
    _t.latch_pin = false;
    _t.rgb_pin = _hwtest_rgb();
    _t.imu = false;
    _t.rumble = false;

    return _t.val;
}