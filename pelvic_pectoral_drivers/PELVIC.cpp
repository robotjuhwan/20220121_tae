#include "PELVIC.h"

PELVIC::PELVIC(uint8_t id1, uint8_t id2, XH430 *dxl):led(LED2)
{
    id1_ = id1;
    id2_ = id2;
    dxl_ = dxl;

    pel_count = 0;
    pel_count_sub = 0;

    direction_ = 0;
    cont_ = 0;
    period_ = 1.0;
    count_diff_ = 0;

    glob_pelvic_wait = 100;

    motor_ang_arr1 = 2048;
    motor_ang_arr2 = 2048;

    PELVIC::set_profile(1.0, 1.0, 0);
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
    }
    //*********variable initailiation -end****//
}

PELVIC::~PELVIC(){};

void PELVIC::set_profile(float amplitude, float offset, int8_t pattern)
{
    // profile 1 = 90'
    amplitude = amplitude / 90;
    offset = offset / 90;
    if (pattern == 0) // proportional
    {
        for (int i = 0; i < 32; i++)
        {
            pelvic_profile[i] = (pro_profile[i] * amplitude + offset) * 1024 + 2048;
            // pcpc.printf("%d ", profile[i]);
        }
    }
    else if (pattern == 1) // sinusodal
    {
        for (int i = 0; i < 32; i++)
        {
            pelvic_profile[i] = (sin_profile[i] * amplitude + offset) * 1024 + 2048;
            // pcpc.printf("%d ", profile[i]);
        }
    }

    // pcpc.printf("\r\n");
}

void PELVIC::pelvic_func(void)
{
    if (cont_ == 1)
    {
        if (direction_ == 0)
        {
            pel_count = 0;
            pel_count_sub = 0;
            motor_ang_arr1 = 2048;
            motor_ang_arr2 = 2048;
        }
        else if (direction_ == 1) // forward
        {
            pel_count_sub = pel_count - count_diff_;
            if (pel_count_sub < 0)
            {
                pel_count_sub += 32;
            }
            motor_ang_arr1 = pelvic_profile[pel_count]; // ID: 11
            motor_ang_arr2 = pelvic_profile[pel_count_sub];
        }
        else if (direction_ == 2) // backward
        {
            pel_count_sub = pel_count + count_diff_;
            if (pel_count_sub > 31)
            {
                pel_count_sub -= 32;
            }
            motor_ang_arr1 = pelvic_profile[pel_count]; // ID: 11
            motor_ang_arr2 = pelvic_profile[pel_count_sub];
        }
        else if (direction_ == 3) // left
        {
            motor_ang_arr1 = pelvic_profile[pel_count]; // ID: 11
            motor_ang_arr2 = pelvic_profile[pel_count];
        }
        else if (direction_ == 4) // right
        {
            if (pel_count >= 8 && pel_count <= 24)
            {

                if (pel_count + pel_count_sub >= 24)
                {
                    motor_ang_arr1 = pelvic_profile[pel_count]; // ID: 11
                    motor_ang_arr2 = pelvic_profile[24];
                }
                else
                {
                    motor_ang_arr1 = pelvic_profile[pel_count]; // ID: 11
                    motor_ang_arr2 = pelvic_profile[pel_count + pel_count_sub];
                }
                if (pel_count_sub < count_diff_)
                {
                    pel_count_sub++;
                    pel_count--;
                }
            }
            else
            {
                pel_count_sub = 0;
                motor_ang_arr1 = pelvic_profile[pel_count]; // ID: 11
                motor_ang_arr2 = pelvic_profile[pel_count];
            }
        }

        pel_count++;
        if (pel_count > 31)
        {
            pel_count = 0;
        }
        // DXL.make_4byte_packet_sync(GOAL_POSITION, motor_ang_arr[0],
        // motor_ang_arr[1], motor_ang_arr[2], motor_ang_arr[3], motor_ang_arr1,
        // motor_ang_arr[5], motor_ang_arr2, motor_ang_arr[7], motor_ang_arr[8]);

        if (motor_ang_arr1 >= pre_motor_ang_arr1)
        {
            velocity_arr1 = 60 / 4096.0 *
                            (motor_ang_arr1 - pre_motor_ang_arr1) /
                            (glob_pelvic_wait / 1000.0) / 0.229;
        }
        else
        {
            velocity_arr1 = 60 / 4096.0 *
                            (pre_motor_ang_arr1 - motor_ang_arr1) /
                            (glob_pelvic_wait / 1000.0) / 0.229;
        }
        if (velocity_arr1 >= 130)
        {
            velocity_arr1 = 130;
        }

        if (motor_ang_arr2 >= pre_motor_ang_arr2)
        {
            velocity_arr2 = 60 / 4096.0 *
                            (motor_ang_arr2 - pre_motor_ang_arr2) /
                            (glob_pelvic_wait / 1000.0) / 0.229;
        }
        else
        {
            velocity_arr2 = 60 / 4096.0 *
                            (pre_motor_ang_arr2 - motor_ang_arr2) /
                            (glob_pelvic_wait / 1000.0) / 0.229;
        }
        if (velocity_arr2 >= 130)
        {
            velocity_arr2 = 130;
        }

        dxl_->make_4byte_packet_sync_velocity(id1_, id2_, velocity_arr1, velocity_arr2);
        dxl_->make_4byte_packet_sync(id1_, id2_, motor_ang_arr1, motor_ang_arr2);

        pre_motor_ang_arr1 = motor_ang_arr1;
        pre_motor_ang_arr2 = motor_ang_arr2;

        led = !led;
    }
}

void PELVIC::set_tick(uint8_t onoff, microseconds wait_time)
{
    glob_pelvic_wait = wait_time/1ms;
    if (onoff == 1)
    {
        pelvic_tick.attach(callback(this, &PELVIC::pelvic_func), wait_time);
    }
    else
    {
        pelvic_tick.detach();
    }
}

void PELVIC::set_cont(uint8_t cont)
{
    cont_ = cont;
}

void PELVIC::set_direction(uint8_t direction)
{
     direction_ = direction;
}

void PELVIC::set_period(float period)
{
     period_ = period;

     PELVIC::set_tick(1, (int)(1000.0 / 32.0 * period_)*1ms);
}

void PELVIC::set_count_diff(int8_t count_diff)
{
     count_diff_ = count_diff;
}