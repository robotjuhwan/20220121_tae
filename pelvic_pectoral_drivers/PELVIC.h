#ifndef PELVIC_H
#define PELVIC_H

#include "mbed.h"

#include "XH430_Driver.h"

#define PI 3.14159265359

using namespace std::chrono;

class PELVIC
{
public:
    PELVIC(uint8_t id1, uint8_t id2, XH430 *dxl);
    ~PELVIC();

    void pelvic_func(void);
    void set_tick(uint8_t onoff, microseconds wait_time);

    void set_profile(float amplitude, float offset, int8_t pattern);
    void set_cont(uint8_t cont);
    void set_direction(uint8_t direction);
    void set_period(float period);
    void set_count_diff(int8_t count_diff);

private:
    uint8_t id1_;
    uint8_t id2_;
    XH430 *dxl_;

    float pro_profile[32];
    float sin_profile[32];

    int32_t pelvic_profile[32];

    Ticker pelvic_tick;

    int8_t direction_;
    int8_t cont_;
    float period_;
    int8_t count_diff_;

    int8_t pel_count;
    int8_t pel_count_sub;

    int32_t glob_pelvic_wait;

    uint32_t motor_ang_arr1;
    uint32_t motor_ang_arr2;

    uint32_t pre_motor_ang_arr1;
    uint32_t pre_motor_ang_arr2;

    uint32_t velocity_arr1;
    uint32_t velocity_arr2;

    DigitalOut led;
};

#endif