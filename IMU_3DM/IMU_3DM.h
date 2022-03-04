#ifndef IMU_3DM_H
#define IMU_3DM_H

#include "mbed.h"

#define PI 3.14159265359

using namespace std::chrono;

class IMU_3DM
{
public:
    IMU_3DM(uint32_t baud, PinName tx, PinName rx);
    ~IMU_3DM();
    /***Reboot***/

    struct Quaternion
    {
        double w, x, y, z;
    };

    struct EulerAngles
    {
        double roll, pitch, yaw;
    };

    EulerAngles ToEulerAngles(Quaternion q);
    void on_rx_interrupt(void);
    EulerAngles Get_Angles(void);
    Quaternion Get_Angles_q(void);

private:
    int serial_count = 0;
    uint8_t inputString[100];    // a String to hold incoming data
    bool stringComplete = false; // whether the string is complete

    uint8_t imu_check = 0;

    union
    {
        float real;
        uint32_t base;
    } u_data;

    float quaternion[4];

    float roll, pitch, yaw;

    float vel_roll, vel_pitch, vel_yaw;
    float acc_x = 0, acc_y = 0, acc_z = 0;
    uint8_t ahrs_valid1, ahrs_valid2, ahrs_valid3;

    uint8_t yaw_calid_command = 0;
    char yaw_calib = 0;
    float pre_yaw = 0;
    float yaw_calib2 = 0;

    UnbufferedSerial imu_serial;
};

#endif