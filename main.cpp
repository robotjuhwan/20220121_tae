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

#define BLINKING_RATE 100ms
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

int8_t bouy_cali = 0;
uint8_t glob_mode = 0;
uint8_t bouy_front = 0;
uint8_t bouy_rear = 0;

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
  glob_mode = msg_.mode;
  bouy_front = msg_.buoy_front;
  bouy_rear = msg_.buoy_rear;
  buoyancy.write_ang(bouy_front, bouy_rear);
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

  nh.subscribe(sub_pel_l);
  nh.subscribe(sub_pel_r);
  nh.subscribe(sub_pec);
  nh.subscribe(sub_v);

  read_dy_tick.attach(&read_dy_func, BLINKING_RATE); // Ticker read_dy_tick(&callback, timing)

  printf("Start\r\n");

  printf("set_profile_0\r\n");
  walking.set_profile(0, 45, 25, 1);
  ThisThread::sleep_for(300ms);

  printf("set_profile_1\r\n");
  walking.set_profile(1, 45, 25, 1);
  ThisThread::sleep_for(300ms);

  printf("set_profile_2\r\n");
  walking.set_profile(2, 60, 60, 0);
  ThisThread::sleep_for(300ms);

  printf("set_profile_3\r\n");
  walking.set_profile(3, 60, 60, 0);
  ThisThread::sleep_for(300ms);

  printf("start_walking\r\n");
  walking.start_walking();
  ThisThread::sleep_for(300ms);
  printf("initialization\r\n");
  buoyancy.initialization();
  
  while (true)
  {
    led = !led;
    printf("%d  %d\r\n",walking.get_walk_count(1),walking.get_walk_count(2));
    if (glob_mode == 1 && bouy_cali == 0)
    {
      
      bouy_cali = 1;
    }
    else if (glob_mode == 2)
    {
      int rot_angle_ft = -1 * int(4096 * bouy_front); // -1 is direction
      int rot_angle_rr = -1 * int(4096 * bouy_rear);
      DXL.make_4byte_packet(98, WRITE, GOAL_POSITION, rot_angle_ft);
      ThisThread::sleep_for(300ms);
      DXL.make_4byte_packet(99, WRITE, GOAL_POSITION, rot_angle_rr);
      ThisThread::sleep_for(300ms);
    }

    //nh.spinOnce(); // callback 함수처리

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
