#include "IMU_3DM.h"

IMU_3DM::IMU_3DM(uint32_t baud, PinName tx, PinName rx)
    : imu_serial(tx, rx)
{
    imu_serial.baud(baud);
    imu_serial.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1);

    // Register a callback to process a Rx (receive) interrupt.
    imu_serial.attach(callback(this, &IMU_3DM::on_rx_interrupt), SerialBase::RxIrq);
}

IMU_3DM::~IMU_3DM(){};

IMU_3DM::EulerAngles IMU_3DM::ToEulerAngles(IMU_3DM::Quaternion q)
{
    IMU_3DM::EulerAngles angles;

    // roll (x-axis rotation)
    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    angles.roll = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = 2 * (q.w * q.y - q.z * q.x);
    if (std::abs(sinp) >= 1)
        angles.pitch =
            std::copysign(PI / 2, sinp); // use 90 degrees if out of range
    else
        angles.pitch = std::asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    angles.yaw = std::atan2(siny_cosp, cosy_cosp);

    return angles;
}

IMU_3DM::EulerAngles IMU_3DM::Get_Angles(void)
{
    IMU_3DM::Quaternion q;

    q.x = quaternion[1];
    q.y = quaternion[2];
    q.z = quaternion[3];
    q.w = quaternion[0];

    return ToEulerAngles(q);
}

IMU_3DM::Quaternion IMU_3DM::Get_Angles_q(void)
{
    IMU_3DM::Quaternion q;

    q.x = quaternion[1];
    q.y = quaternion[2];
    q.z = quaternion[3];
    q.w = quaternion[0];

    return q;
}

void IMU_3DM::on_rx_interrupt(void)
{ // USART에 RX가 들어왔을때 동작하는 interrupt

    char inChar;
    imu_serial.read(&inChar, 1);

    if (imu_check == 0 && inChar == (char)0x75)
    {
        imu_check = 1;
        inputString[0] = inChar;
    }
    else if (imu_check == 1 && inChar == (char)0x65)
    {
        imu_check = 2;
        inputString[1] = inChar;
    }
    else if (imu_check == 2 && inChar == (char)0x82)
    {
        imu_check = 3;
        inputString[2] = inChar;
        serial_count = 3;
    }
    else if (imu_check == 3)
    {
        inputString[serial_count] = inChar;
        serial_count++;
    }
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    // inputString[19] == 1 &&

    if (serial_count == 58) //수신이 완료
    {
        stringComplete = true;
        serial_count = 0;
        imu_check = 0;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[9]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[8]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[7]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[6]) << (8 * 3);
        quaternion[0] = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[13]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[12]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[11]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[10]) << (8 * 3);
        quaternion[1] = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[17]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[16]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[15]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[14]) << (8 * 3);
        quaternion[2] = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[21]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[20]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[19]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[18]) << (8 * 3);
        quaternion[3] = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[29]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[28]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[27]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[26]) << (8 * 3);
        vel_roll = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[33]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[32]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[31]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[30]) << (8 * 3);
        vel_pitch = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[37]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[36]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[35]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[34]) << (8 * 3);
        vel_yaw = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[45]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[44]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[43]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[42]) << (8 * 3);

        acc_x = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[49]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[48]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[47]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[46]) << (8 * 3);

        acc_y = u_data.real;

        u_data.base = 0;
        u_data.base |= ((uint32_t)inputString[53]) << (8 * 0);
        u_data.base |= ((uint32_t)inputString[52]) << (8 * 1);
        u_data.base |= ((uint32_t)inputString[51]) << (8 * 2);
        u_data.base |= ((uint32_t)inputString[50]) << (8 * 3);

        acc_z = u_data.real;

        ahrs_valid1 = inputString[23];
        ahrs_valid2 = inputString[39];
        ahrs_valid3 = inputString[55];
    }
    else if (serial_count >
             58) //데이터가 10개 넘게 들어옴 (데inputString[19]이터 수신 실패)
    {
        inputString[0] = '\0';
        serial_count = 0;
        stringComplete = false;
        imu_check = 0;
    }
}

