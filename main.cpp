/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#include "XH430_Driver.h"
#include "MS5837.h"
#include "PELVIC.h"
#include "PECTORAL.h"
#include "IMU_3DM.h"
#include "BUOYANCY.h"
#include "WALKING.h"

#include <ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Empty.h>
#include <underwalker_control/uw_control_pectoral.h>
#include <underwalker_control/uw_control_pelvic.h>
#include <underwalker_control/uw_read_sensor.h>
#include <underwalker_control/uw_control_v.h>
#include <underwalker_control/uw_control_walking.h>

#define BLINKING_RATE 20ms
// swimming////////////////////////////////////////////////////////////

ros::NodeHandle nh;

ros::Publisher *p_pub_sensor;

//**global variable

XH430 DXL(115200, p9, p10, p8);

PELVIC pelvic_l(11, 13, &DXL);
PELVIC pelvic_r(12, 14, &DXL);

PECTORAL pectoral(1, 2, 3, 4, &DXL);

BUOYANCY buoyancy(98, 99, &DXL); // taesik 추가

WALKING walking(1, 2, 3, 4, &DXL);

MS5837 bar_sensor(p28, p27, 0x76);
IMU_3DM imu(115200, p13, p14);

int8_t glob_direction = 0;
//**global variable -end

// function statement
void init_main_all(void);
// function statement end

////////////////////////////////////////////////////////////////////////////////////////////////////

// Blinking rate in milliseconds

// static BufferedSerial pc_serial(USBTX, USBRX, 115200);

// FileHandle *mbed::mbed_override_console(int fd) { return &pc_serial; }

Thread thread1;

int ccount = 0;

void bar_thread() // 압력계
{
  bar_sensor.init();
  bar_sensor.setModel(MS5837::MS5837_02BA);
  bar_sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
  while (true)
  {
    bar_sensor.read();
    //
  }
}

void read_dy_func()
{
  uint8_t id[9] = {1, 2, 3, 4, 11, 12, 13, 14, 55};
  uint16_t position[9];
  int16_t current[9];

  IMU_3DM::Quaternion q;

  underwalker_control::uw_read_sensor msg_uw_sensor;

  if (DXL.read_4byte_packet_sync(id, position) == 1) // dynamixel read 되면,
  {
    for (int i = 0; i < 9; i++)
    {
      msg_uw_sensor.position[i] = position[i]; // position update
    }
    if (DXL.read_2byte_packet_sync(id, current) == 1)
    {
      for (int i = 0; i < 9; i++)
      {
        msg_uw_sensor.current[i] = current[i]; // current update
      }
    }
    else
    {
      for (int i = 0; i < 9; i++)
      {
        msg_uw_sensor.current[i] = 0;
      }
    }
  }
  else
  {
    for (int i = 0; i < 9; i++)
    {
      msg_uw_sensor.position[i] = 0;
      msg_uw_sensor.current[i] = 0;
    }
  }

  msg_uw_sensor.depth = bar_sensor.depth();
  q = imu.Get_Angles_q();
  msg_uw_sensor.q1 = q.x;
  msg_uw_sensor.q2 = q.y;
  msg_uw_sensor.q3 = q.z;
  msg_uw_sensor.q4 = q.w;

  p_pub_sensor->publish(&msg_uw_sensor);
}

Ticker read_dy_tick;

void message_v(const underwalker_control::uw_control_v &msg_) // taesik buoyancy callback function
{
  buoyancy.set_mode(msg_.mode);
  buoyancy.set_angle(msg_.buoy_front, msg_.buoy_rear);
}
// Buoyancy Control//

void message_pelvic_l(const underwalker_control::uw_control_pelvic &msg_)
{
  pelvic_l.set_profile(msg_.amplitude, msg_.offset, msg_.pattern);

  pelvic_l.set_cont(msg_.cont);
  pelvic_l.set_direction(msg_.direction);
  pelvic_l.set_period(msg_.period);
  pelvic_l.set_count_diff(msg_.count_diff);
}

void message_pelvic_r(const underwalker_control::uw_control_pelvic &msg_)
{
  pelvic_r.set_profile(msg_.amplitude, msg_.offset, msg_.pattern);

  pelvic_r.set_cont(msg_.cont);
  pelvic_r.set_direction(msg_.direction);
  pelvic_r.set_period(msg_.period);
  pelvic_r.set_count_diff(msg_.count_diff);
}

void message_pec(const underwalker_control::uw_control_pectoral &msg_)
{
  pectoral.set_profile(msg_.count, msg_.amplitude, msg_.offset, msg_.pattern, msg_.count_diff);

  pectoral.set_cont(msg_.cont);
  pectoral.set_direction(msg_.direction);
  pectoral.set_period(msg_.period);
}

void message_walking(const underwalker_control::uw_control_walking &msg_)
{
  walking.set_profile(msg_.count, msg_.stride_front, msg_.stride_rear, msg_.pattern);

  walking.set_cont(msg_.cont);
  walking.set_direction(msg_.direction);
  walking.set_period(msg_.f_go, msg_.f_back, msg_.r_go, msg_.r_back, msg_.f_go2, msg_.f_back2, msg_.r_go2, msg_.r_back2);
  walking.set_delay_time(msg_.d_time, msg_.d_time2);

  if (msg_.start_sig == 1)
  {
    walking.start_walking();
  }
  if (msg_.start_sig == 2)
  {
    walking.stop_walking();
  }
}

char inChar = 0;

int main()
{
  thread1.start(bar_thread);
  // Set desired properties (9600-8-N-1).
  init_main_all();
  // Initialise the digital pin LED1 as an output
  DigitalOut led(LED1);

  ros::NodeHandle nh;
  nh.initNode();

  underwalker_control::uw_read_sensor msg_uw_sensor;

  ros::Publisher pub_sensor("uw_sensor", &msg_uw_sensor); // uw_sensor : topic name
  nh.advertise(pub_sensor);
  p_pub_sensor = &pub_sensor;

  ros::Subscriber<underwalker_control::uw_control_pelvic> sub_pel_l("uw_pelvic_l", &message_pelvic_l);
  ros::Subscriber<underwalker_control::uw_control_pelvic> sub_pel_r("uw_pelvic_r", &message_pelvic_r);
  ros::Subscriber<underwalker_control::uw_control_pectoral> sub_pec("uw_pectoral", &message_pec);
  ros::Subscriber<underwalker_control::uw_control_v> sub_v("uw_v", &message_v);
  ros::Subscriber<underwalker_control::uw_control_walking> sub_walk("uw_walking", &message_walking);

  nh.subscribe(sub_pel_l);
  nh.subscribe(sub_pel_r);
  nh.subscribe(sub_pec);
  nh.subscribe(sub_v);
  nh.subscribe(sub_walk);

  read_dy_tick.attach(&read_dy_func, 100ms); // Ticker read_dy_tick(&callback, timing)

  while (true)
  {
    led = !led;

    nh.spinOnce(); // callback 함수처리

    /*
    printf("%f   %f %f %f %d   %f %f %f %d   %f %f %f %d \r\n", bar, roll,
           pitch, yaw, ahrs_valid1, vel_roll, vel_pitch, vel_yaw, ahrs_valid2,
           acc_x, acc_y, acc_z, ahrs_valid3);
*/
    ThisThread::sleep_for(BLINKING_RATE);
  }
}

void init_main_all(void)
{
  //********dynamixel initialization*******///
  DXL.make_1byte_packet(0xfe, WRITE, TORQUE_ENABLE, 0);
  ThisThread::sleep_for(100ms);
  DXL.make_1byte_packet(0xfe, WRITE, TORQUE_ENABLE, 1);
  ThisThread::sleep_for(100ms);

  DXL.make_1byte_packet(0xfe, WRITE, TORQUE_ENABLE, 0);
  ThisThread::sleep_for(100ms);
  DXL.make_1byte_packet(0xfe, WRITE, TORQUE_ENABLE, 1);
  ThisThread::sleep_for(100ms);
  //*********dynamixel initailiation -end****//

  DXL.make_4byte_packet_sync(
      GOAL_POSITION, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048);
}
