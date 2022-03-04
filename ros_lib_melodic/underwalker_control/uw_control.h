#ifndef _ROS_underwalker_control_uw_control_h
#define _ROS_underwalker_control_uw_control_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace underwalker_control
{

  class uw_control : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int8_t _mode_type;
      _mode_type mode;
      typedef int8_t _gait_type;
      _gait_type gait;
      typedef int8_t _gait_side_type;
      _gait_side_type gait_side;
      typedef int8_t _pattern_type;
      _pattern_type pattern;
      typedef int8_t _direction_type;
      _direction_type direction;
      typedef int8_t _direction2_type;
      _direction2_type direction2;
      typedef int32_t _rotation_type;
      _rotation_type rotation;
      typedef float _velocity_type;
      _velocity_type velocity;
      typedef int32_t _ft_angle_type;
      _ft_angle_type ft_angle;
      typedef int32_t _rr_angle_type;
      _rr_angle_type rr_angle;
      typedef int32_t _up_angle_type;
      _up_angle_type up_angle;
      typedef int32_t _down_angle_type;
      _down_angle_type down_angle;
      typedef int32_t _delay_time_type;
      _delay_time_type delay_time;
      typedef int8_t _front_buoy_type;
      _front_buoy_type front_buoy;
      typedef int8_t _rear_buoy_type;
      _rear_buoy_type rear_buoy;

    uw_control():
      header(),
      mode(0),
      gait(0),
      gait_side(0),
      pattern(0),
      direction(0),
      direction2(0),
      rotation(0),
      velocity(0),
      ft_angle(0),
      rr_angle(0),
      up_angle(0),
      down_angle(0),
      delay_time(0),
      front_buoy(0),
      rear_buoy(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const 
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_mode;
      u_mode.real = this->mode;
      *(outbuffer + offset + 0) = (u_mode.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      union {
        int8_t real;
        uint8_t base;
      } u_gait;
      u_gait.real = this->gait;
      *(outbuffer + offset + 0) = (u_gait.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->gait);
      union {
        int8_t real;
        uint8_t base;
      } u_gait_side;
      u_gait_side.real = this->gait_side;
      *(outbuffer + offset + 0) = (u_gait_side.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->gait_side);
      union {
        int8_t real;
        uint8_t base;
      } u_pattern;
      u_pattern.real = this->pattern;
      *(outbuffer + offset + 0) = (u_pattern.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pattern);
      union {
        int8_t real;
        uint8_t base;
      } u_direction;
      u_direction.real = this->direction;
      *(outbuffer + offset + 0) = (u_direction.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction);
      union {
        int8_t real;
        uint8_t base;
      } u_direction2;
      u_direction2.real = this->direction2;
      *(outbuffer + offset + 0) = (u_direction2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction2);
      union {
        int32_t real;
        uint32_t base;
      } u_rotation;
      u_rotation.real = this->rotation;
      *(outbuffer + offset + 0) = (u_rotation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rotation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rotation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rotation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rotation);
      union {
        float real;
        uint32_t base;
      } u_velocity;
      u_velocity.real = this->velocity;
      *(outbuffer + offset + 0) = (u_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity);
      union {
        int32_t real;
        uint32_t base;
      } u_ft_angle;
      u_ft_angle.real = this->ft_angle;
      *(outbuffer + offset + 0) = (u_ft_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ft_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ft_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ft_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ft_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_rr_angle;
      u_rr_angle.real = this->rr_angle;
      *(outbuffer + offset + 0) = (u_rr_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rr_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rr_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rr_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rr_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_up_angle;
      u_up_angle.real = this->up_angle;
      *(outbuffer + offset + 0) = (u_up_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_up_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_up_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_up_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->up_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_down_angle;
      u_down_angle.real = this->down_angle;
      *(outbuffer + offset + 0) = (u_down_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_down_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_down_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_down_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->down_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_delay_time;
      u_delay_time.real = this->delay_time;
      *(outbuffer + offset + 0) = (u_delay_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_delay_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_delay_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_delay_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->delay_time);
      union {
        int8_t real;
        uint8_t base;
      } u_front_buoy;
      u_front_buoy.real = this->front_buoy;
      *(outbuffer + offset + 0) = (u_front_buoy.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->front_buoy);
      union {
        int8_t real;
        uint8_t base;
      } u_rear_buoy;
      u_rear_buoy.real = this->rear_buoy;
      *(outbuffer + offset + 0) = (u_rear_buoy.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->rear_buoy);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_mode;
      u_mode.base = 0;
      u_mode.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->mode = u_mode.real;
      offset += sizeof(this->mode);
      union {
        int8_t real;
        uint8_t base;
      } u_gait;
      u_gait.base = 0;
      u_gait.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->gait = u_gait.real;
      offset += sizeof(this->gait);
      union {
        int8_t real;
        uint8_t base;
      } u_gait_side;
      u_gait_side.base = 0;
      u_gait_side.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->gait_side = u_gait_side.real;
      offset += sizeof(this->gait_side);
      union {
        int8_t real;
        uint8_t base;
      } u_pattern;
      u_pattern.base = 0;
      u_pattern.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pattern = u_pattern.real;
      offset += sizeof(this->pattern);
      union {
        int8_t real;
        uint8_t base;
      } u_direction;
      u_direction.base = 0;
      u_direction.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->direction = u_direction.real;
      offset += sizeof(this->direction);
      union {
        int8_t real;
        uint8_t base;
      } u_direction2;
      u_direction2.base = 0;
      u_direction2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->direction2 = u_direction2.real;
      offset += sizeof(this->direction2);
      union {
        int32_t real;
        uint32_t base;
      } u_rotation;
      u_rotation.base = 0;
      u_rotation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rotation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rotation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rotation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rotation = u_rotation.real;
      offset += sizeof(this->rotation);
      union {
        float real;
        uint32_t base;
      } u_velocity;
      u_velocity.base = 0;
      u_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->velocity = u_velocity.real;
      offset += sizeof(this->velocity);
      union {
        int32_t real;
        uint32_t base;
      } u_ft_angle;
      u_ft_angle.base = 0;
      u_ft_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ft_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ft_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ft_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ft_angle = u_ft_angle.real;
      offset += sizeof(this->ft_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_rr_angle;
      u_rr_angle.base = 0;
      u_rr_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rr_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rr_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rr_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rr_angle = u_rr_angle.real;
      offset += sizeof(this->rr_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_up_angle;
      u_up_angle.base = 0;
      u_up_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_up_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_up_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_up_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->up_angle = u_up_angle.real;
      offset += sizeof(this->up_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_down_angle;
      u_down_angle.base = 0;
      u_down_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_down_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_down_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_down_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->down_angle = u_down_angle.real;
      offset += sizeof(this->down_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_delay_time;
      u_delay_time.base = 0;
      u_delay_time.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_delay_time.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_delay_time.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_delay_time.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->delay_time = u_delay_time.real;
      offset += sizeof(this->delay_time);
      union {
        int8_t real;
        uint8_t base;
      } u_front_buoy;
      u_front_buoy.base = 0;
      u_front_buoy.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->front_buoy = u_front_buoy.real;
      offset += sizeof(this->front_buoy);
      union {
        int8_t real;
        uint8_t base;
      } u_rear_buoy;
      u_rear_buoy.base = 0;
      u_rear_buoy.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->rear_buoy = u_rear_buoy.real;
      offset += sizeof(this->rear_buoy);
     return offset;
    }

    virtual const char * getType() { return "underwalker_control/uw_control"; };
    virtual const char * getMD5() { return "a2060a0f56164af5dedbe273ec768d14"; };

  };

}
#endif