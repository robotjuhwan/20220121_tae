#ifndef WALKING_H
#define WALKING_H

#include "mbed.h"

#include "XH430_Driver.h"

#define PI 3.14159265359

using namespace std::chrono;

class WALKING
{
public:
    WALKING(uint8_t id1, uint8_t id2, uint8_t id3, uint8_t id4, XH430 *dxl);
    ~WALKING();
    /***Reboot***/

    void walking_func(void);
    void set_tick(uint8_t onoff, microseconds wait_time);

    void set_profile(int8_t count, float amplitude,
                            float offset, int8_t pattern, int8_t count_diff);
                            
    void set_cont(uint8_t cont);
    void set_direction(uint8_t direction);    
    void set_period(float period);

private:
    uint8_t id1_;
    uint8_t id2_;
    uint8_t id3_;
    uint8_t id4_;
    XH430 *dxl_;

    float pro_profile[32];
    float sin_profile[32];

    int32_t walking_profile[4][32];

    Ticker walking_tick0;
    Ticker walking_tick1;

    int8_t stride_front;
    int8_t stride_rear;
    float period_front_go;
    float period_front_back;
    float period_rear_go;
    float period_rear_back;

    float delay_time;

    int8_t walk_count;

    int32_t glob_wait; 

    uint32_t motor_ang_arr[4];
    uint32_t pre_motor_ang_arr[4];
    uint32_t velocity_arr[4];

    Thread thread;
};

#endif