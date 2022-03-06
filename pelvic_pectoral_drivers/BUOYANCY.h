#ifndef BUOYANCY_H
#define BUOYANCY_H

#include "mbed.h"

#include "XH430_Driver.h"

#define PI 3.14159265359

using namespace std::chrono;

class BUOYANCY
{
public:
    BUOYANCY(uint8_t id1, uint8_t id2, XH430 *dxl);
    ~BUOYANCY();

    void set_angle(uint8_t b_front,uint8_t b_rear);
    void set_mode(uint8_t b_mode);

private:

    void buoyancy_thread();
    void set_current(int32_t current);
    void off(void);
    void on(void);    
    void initialization(void);
    void write_ang(int fr_ang, int rr_ang);

private:
    uint8_t id1_;
    uint8_t id2_;
    XH430 *dxl_;

    Thread thread_b;

    int8_t bouy_cali;
    uint8_t bouy_mode;
    uint8_t bouy_front;
    uint8_t bouy_rear;
};

#endif