#include "WALKING.h"

WALKING::WALKING(uint8_t id1, uint8_t id2, uint8_t id3, uint8_t id4, XH430 *dxl)
{
    id1_ = id1;
    id2_ = id2;
    id3_ = id3;
    id4_ = id4;

    dxl_ = dxl;

    direction_ = 0;
    cont_ = 0;

    stride_front = 30;
    stride_rear = 30;
    period_front_go = 1.0;
    period_front_back = 1.0;
    period_rear_go = 1.0;
    period_rear_back = 1.0;

    delay_time = 0.0;

    walk1_count = 0;
    walk2_count = 0;

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
        if (walk1_count == 8)
        {
            ThisThread::sleep_for(delay_time * 1ms);
            WALKING::set_tick(1, 1, (int)(1000.0 / 32.0 * period_front_back) * 1ms);
        }
        else if (walk1_count == 24)
        {
            ThisThread::sleep_for(delay_time * 1ms);
            WALKING::set_tick(1, 1, (int)(1000.0 / 32.0 * period_rear_go) * 1ms);
        }

        ThisThread::sleep_for(100ms);
    }
}

void PECTORAL::set_profile(int8_t count, int8_t stride_front,
                           int8_t stride_rear, int8_t pattern)
{
    // profile 1 = 90'
    float amplitude_front = stride_front / 90;
    float amplitude_rear = stride_rear / 90;

    if (pattern == 0) // proportional
    {
        for (int i = 0; i < 32; i++)
        {
            if (i < 16)
            {
                walking_profile[count][i] = (pro_profile[i] * amplitude_front) * 1024 + 2048;
            }
            else
            {
                walking_profile[count][i] = (pro_profile[i] * amplitude_rear) * 1024 + 2048;
            }
        }
    }
    else if (pattern == 1) // sinusodal
    {
        for (int i = 0; i < 32; i++)
        {
            if (i < 16)
            {
                walking_profile[count][i] = (sin_profile[i] * amplitude_front) * 1024 + 2048;
            }
            else
            {
                walking_profile[count][i] = (sin_profile[i] * amplitude_rear) * 1024 + 2048;
            }
        }
    }
}

void WALKING::walking_func1(void)
{
    if (cont_ == 1)
    {
        if (direction_ == 0)
        {

            walk1_count = 0;
            motor_ang_arr[0] = 2048;
            motor_ang_arr[1] = 2048;
        }
        else if (direction_ == 1) // forward
        {
            motor_ang_arr[0] = walking_profile[0][walk1_count];
            motor_ang_arr[1] = walking_profile[1][walk1_count];
        }

        if (walk1_count == 0) // 1st period
        {
            WALKING::set_tick(1, 1, (int)(1000.0 / 32.0 * period_front_go) * 1ms);
        }
        else if (walk1_count == 8) // 1st period
        {
            WALKING::set_tick(1, 0, 0);
        }
        else if (walk1_count == 16) // 2nd period
        {
            WALKING::set_tick(1, 1, (int)(1000.0 / 32.0 * period_rear_back) * 1ms);
        }
        else if (walk1_count == 24)
        {
            WALKING::set_tick(1, 0, 0);
        }

        walk1_count++;
        if (walk1_count > 31)
        {
            walk1_count = 0;
        }

        for (int i = 0; i < 2; i++)
        {
            if (motor_ang_arr[i] >= pre_motor_ang_arr[i])
            {
                velocity_arr[i] = 60 / 4096.0 *
                                  (motor_ang_arr[i] - pre_motor_ang_arr[i]) /
                                  (glob_wait1 / 1000.0) / 0.229;
            }
            else
            {
                velocity_arr[i] = 60 / 4096.0 *
                                  (pre_motor_ang_arr[i] - motor_ang_arr[i]) /
                                  (glob_wait1 / 1000.0) / 0.229;
            }
            if (velocity_arr[i] >= 130)
            {
                velocity_arr[i] = 130;
            }
        }

        dxl_->make_4byte_packet_sync_velocity(id1_, id2_, velocity_arr[0], velocity_arr[1]);
        dxl_->make_4byte_packet_sync(id1_, id2_, motor_ang_arr[0], motor_ang_arr[1]);

        for (int i = 0; i < 2; i++)
        {
            pre_motor_ang_arr[i] = motor_ang_arr[i];
        }
    }
}

void WALKING::walking_func2(void)
{
    if (cont_ == 1)
    {
        if (direction_ == 0)
        {

            walk2_count = 0;
            motor_ang_arr[2] = 2048;
            motor_ang_arr[3] = 2048;
        }
        else if (direction_ == 1) // forward
        {
            motor_ang_arr[2] = walking_profile[2][walk2_count];
            motor_ang_arr[3] = walking_profile[3][walk2_count];
        }
        
        if (walk2_count == 0) // 1st period
        {
            WALKING::set_tick(1, 1, (int)(1000.0 / 32.0 * period_front_go) * 1ms);
        }
        else if (walk2_count == 8) // 1st period
        {
            WALKING::set_tick(1, 0, 0);
        }
        else if (walk2_count == 16) // 2nd period
        {
            WALKING::set_tick(1, 1, (int)(1000.0 / 32.0 * period_rear_back) * 1ms);
        }
        else if (walk2_count == 24)
        {
            WALKING::set_tick(1, 0, 0);
        }

        walk2_count++;
        if (walk2_count > 31)
        {
            walk2_count = 0;
        }

        for (int i = 2; i < 4; i++)
        {
            if (motor_ang_arr[i] >= pre_motor_ang_arr[i])
            {
                velocity_arr[i] = 60 / 4096.0 *
                                  (motor_ang_arr[i] - pre_motor_ang_arr[i]) /
                                  (glob_wait2 / 1000.0) / 0.229;
            }
            else
            {
                velocity_arr[i] = 60 / 4096.0 *
                                  (pre_motor_ang_arr[i] - motor_ang_arr[i]) /
                                  (glob_wait2 / 1000.0) / 0.229;
            }
            if (velocity_arr[i] >= 130)
            {
                velocity_arr[i] = 130;
            }
        }

        dxl_->make_4byte_packet_sync_velocity(id1_, id2_, velocity_arr[0], velocity_arr[1]);
        dxl_->make_4byte_packet_sync(id1_, id2_, motor_ang_arr[0], motor_ang_arr[1]);

        for (int i = 0; i < 2; i++)
        {
            pre_motor_ang_arr[i] = motor_ang_arr[i];
        }
    }
}

void WALKING::set_tick(uint8_t select, uint8_t onoff, microseconds wait_time)
{
    if (select == 1)
    {
        glob_wait1 = wait_time / 1ms;
        if (onoff == 1)
        {
            walking_tick1.attach(callback(this, &WALKING::walking_func1), wait_time);
        }
        else
        {
            walking_tick1.detach();
        }
    }
    else if (select == 2)
    {
        glob_wait2 = wait_time / 1ms;
        if (onoff == 1)
        {
            walking_tick2.attach(callback(this, &WALKING::walking_func1), wait_time);
        }
        else
        {
            walking_tick2.detach();
        }
    }
}

void WALKING::start_walking(void)
{
    WALKING::set_tick(1, 1, (int)(1000.0 / 32.0 * period_front_go) * 1ms);
}

void WALKING::stop_walking(void)
{
    WALKING::set_tick(1, 0, 0);
    WALKING::set_tick(2, 0, 0);
}

void WALKING::set_direction(uint8_t direction)
{
    direction_ = direction;
}

void WALKING::set_period(float period)
{
    WALKING::set_tick(1, (int)(1000.0 / 32.0 * period) * 1ms);
}