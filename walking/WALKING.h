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

    void walking_func1(void);
    void walking_func2(void);

    void set_tick(uint8_t onoff, microseconds wait_time);

    void set_profile(int8_t count, int8_t stride_front,
                           int8_t stride_rear, int8_t pattern);
                            
    void start_walking(void);
    void stop_walking(void);

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

    Ticker walking_tick1;
    Ticker walking_tick2;

    int8_t direction_;
    int8_t cont_;

    int8_t stride_front;
    int8_t stride_rear;
    float period_front_go;
    float period_front_back;    
    float period_rear_back;
    float period_rear_go;

    int32_t delay_time;

    int8_t walk1_count;
    int8_t walk2_count;

    int32_t glob_wait1; 
    int32_t glob_wait2;

    uint32_t motor_ang_arr[4];
    uint32_t pre_motor_ang_arr[4];
    uint32_t velocity_arr[4];

    Thread thread;
};

#endif