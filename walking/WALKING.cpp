#include "WALKING.h"

WALKING::WALKING(uint8_t id1, uint8_t id2, uint8_t id3, uint8_t id4, XH430 *dxl)
{
    id1_ = id1;
    id2_ = id2;
    id3_ = id3;
    id4_ = id4;

    dxl_ = dxl;

    stride_front = 30;
    stride_rear = 30;
    period_front_go = 1.0;
    period_front_back = 1.0;
    period_rear_go = 1.0;
    period_rear_back = 1.0;

    delay_time = 0.0;

    walk_count = 0;

    glob_wait = 100;

    motor_ang_arr[0] = 2048;
    motor_ang_arr[1] = 2048;
    motor_ang_arr[2] = 2048;
    motor_ang_arr[3] = 2048;

    //********variable initialization*******///
    for (int i = 0; i < 32; i++)
    {
        if (i < 8)
        {
            pro_profile[i] = i * 0.125;
        }
        else if (i < 24)
        {
            pro_profile[i] = 1 - (i - 8) * 0.125;
        }
        else if (i < 32)
        {
            pro_profile[i] = -1 + (i - 24) * 0.125;
        }

        sin_profile[i] = sin(PI * i / 16);
        for (int j = 0; j < 4; j++)
        {
            pectoral_profile[j][i] = 2048;
        }
    }
    //*********variable initailiation -end****//

    thread.start(walking_thread);
}

WALKING::~WALKING(){};

void WALKING::walking_thread()
{
    while (true)
    {
        ThisThread::sleep_for(100ms);
    }
}

void WALKING::set_profile(int8_t count, float amplitude,
                          float offset, int8_t pattern, int8_t count_diff)
{
    // profile 1 = 90'
    amplitude = amplitude / 90;
    offset = offset / 90;
    if (pattern == 0) // proportional
    {
        for (int i = 0; i < 32; i++)
        {
            if (count_diff > 0 && count_diff < 32)
            {
                if (i + count_diff >= 32)
                {
                    pectoral_profile[count][i + count_diff - 32] = (pro_profile[i] * amplitude + offset) * 1024 + 2048;
                }
                else
                {
                    pectoral_profile[count][i + count_diff] = (pro_profile[i] * amplitude + offset) * 1024 + 2048;
                }
            }
            else if (count_diff < 0 && count_diff > -32)
            {
                if (i + count_diff < 0)
                {
                    pectoral_profile[count][i + count_diff + 32] = (pro_profile[i] * amplitude + offset) * 1024 + 2048;
                }
                else
                {
                    pectoral_profile[count][i + count_diff] = (pro_profile[i] * amplitude + offset) * 1024 + 2048;
                }
            }
            else
            {
                pectoral_profile[count][i] = (pro_profile[i] * amplitude + offset) * 1024 + 2048;
            }
        }
    }
    else if (pattern == 1) // sinusodal
    {
        for (int i = 0; i < 32; i++)
        {
            if (count_diff > 0 && count_diff < 32)
            {
                if (i + count_diff >= 32)
                {
                    pectoral_profile[count][i + count_diff - 32] = (sin_profile[i] * amplitude + offset) * 1024 + 2048;
                }
                else
                {
                    pectoral_profile[count][i + count_diff] = (sin_profile[i] * amplitude + offset) * 1024 + 2048;
                }
            }
            else if (count_diff < 0 && count_diff > -32)
            {
                if (i + count_diff < 0)
                {
                    pectoral_profile[count][i + count_diff + 32] = (sin_profile[i] * amplitude + offset) * 1024 + 2048;
                }
                else
                {
                    pectoral_profile[count][i + count_diff] = (sin_profile[i] * amplitude + offset) * 1024 + 2048;
                }
            }
            else
            {
                pectoral_profile[count][i] = (sin_profile[i] * amplitude + offset) * 1024 + 2048;
            }
        }
    }
}

void WALKING::pectoral_func(void)
{
    if (cont_ == 1)
    {
        if (direction_ == 0)
        {
            pec_count = 0;
            motor_ang_arr[0] = 2048;
            motor_ang_arr[1] = 2048;
            motor_ang_arr[2] = 2048;
            motor_ang_arr[3] = 2048;
        }
        else if (direction_ == 1) // forward
        {
            motor_ang_arr[0] = pectoral_profile[0][pec_count];
            motor_ang_arr[1] = pectoral_profile[1][pec_count];
            motor_ang_arr[2] = pectoral_profile[2][pec_count];
            motor_ang_arr[3] = pectoral_profile[3][pec_count];
        }

        pec_count++;
        if (pec_count > 31)
        {
            pec_count = 0;
        }
        // DXL.make_4byte_packet_sync(GOAL_POSITION, motor_ang_arr[0],
        // motor_ang_arr[1], motor_ang_arr[2], motor_ang_arr[3], motor_ang_arr1,
        // motor_ang_arr[5], motor_ang_arr2, motor_ang_arr[7], motor_ang_arr[8]);

        for (int i = 0; i < 4; i++)
        {
            if (motor_ang_arr[i] >= pre_motor_ang_arr[i])
            {
                velocity_arr[i] = 60 / 4096.0 *
                                  (motor_ang_arr[i] - pre_motor_ang_arr[i]) /
                                  (glob_pectoral_wait / 1000.0) / 0.229;
            }
            else
            {
                velocity_arr[i] = 60 / 4096.0 *
                                  (pre_motor_ang_arr[i] - motor_ang_arr[i]) /
                                  (glob_pectoral_wait / 1000.0) / 0.229;
            }
            if (velocity_arr[i] >= 130)
            {
                velocity_arr[i] = 130;
            }
        }

        dxl_->make_4byte_packet_sync_velocity(id1_, id2_, id3_, id4_, velocity_arr[0], velocity_arr[1], velocity_arr[2], velocity_arr[3]);
        dxl_->make_4byte_packet_sync(id1_, id2_, id3_, id4_, motor_ang_arr[0], motor_ang_arr[1], motor_ang_arr[2], motor_ang_arr[3]);

        for (int i = 0; i < 4; i++)
        {
            pre_motor_ang_arr[i] = motor_ang_arr[i];
        }

        led = !led;
    }
}

void WALKING::set_tick(uint8_t onoff, microseconds wait_time)
{
    glob_pectoral_wait = wait_time / 1ms;

    if (onoff == 1)
    {
        pectoral_tick.attach(callback(this, &PECTORAL::pectoral_func), wait_time);
    }
    else
    {
        pectoral_tick.detach();
    }
}

void WALKING::set_cont(uint8_t cont)
{
    cont_ = cont;
}

void WALKING::set_direction(uint8_t direction)
{
    direction_ = direction;
}

void WALKING::set_period(float period)
{
    period_ = period;

    PECTORAL::set_tick(1, (int)(1000.0 / 32.0 * period_) * 1ms);
}