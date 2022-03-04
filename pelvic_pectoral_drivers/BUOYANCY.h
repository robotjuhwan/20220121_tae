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

	void set_current(int32_t current);
	void off(void);
	void on(void);
	void write_ang(int fr_ang, int rr_ang);
    void initialization(void);

private:
    uint8_t id1_;
    uint8_t id2_;
    XH430 *dxl_;

    DigitalOut led;
};

#endif