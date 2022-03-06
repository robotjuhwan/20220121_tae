#ifndef _ROS_underwalker_control_uw_control_walking_h
#define _ROS_underwalker_control_uw_control_walking_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace underwalker_control
{

  class uw_control_walking : public ros::Msg
  {
    public:
      typedef uint8_t _cont_type;
      _cont_type cont;
      typedef uint8_t _direction_type;
      _direction_type direction;
      typedef float _f_go_type;
      _f_go_type f_go;
      typedef float _f_back_type;
      _f_back_type f_back;
      typedef float _r_go_type;
      _r_go_type r_go;
      typedef float _r_back_type;
      _r_back_type r_back;
      typedef float _f_go2_type;
      _f_go2_type f_go2;
      typedef float _f_back2_type;
      _f_back2_type f_back2;
      typedef float _r_go2_type;
      _r_go2_type r_go2;
      typedef float _r_back2_type;
      _r_back2_type r_back2;
      typedef int32_t _d_time_type;
      _d_time_type d_time;
      typedef int32_t _d_time2_type;
      _d_time2_type d_time2;
      typedef int8_t _count_type;
      _count_type count;
      typedef uint8_t _stride_front_type;
      _stride_front_type stride_front;
      typedef uint8_t _stride_rear_type;
      _stride_rear_type stride_rear;
      typedef int8_t _pattern_type;
      _pattern_type pattern;
      typedef int8_t _start_sig_type;
      _start_sig_type start_sig;

    uw_control_walking():
      cont(0),
      direction(0),
      f_go(0),
      f_back(0),
      r_go(0),
      r_back(0),
      f_go2(0),
      f_back2(0),
      r_go2(0),
      r_back2(0),
      d_time(0),
      d_time2(0),
      count(0),
      stride_front(0),
      stride_rear(0),
      pattern(0),
      start_sig(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->cont >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cont);
      *(outbuffer + offset + 0) = (this->direction >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction);
      union {
        float real;
        uint32_t base;
      } u_f_go;
      u_f_go.real = this->f_go;
      *(outbuffer + offset + 0) = (u_f_go.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_f_go.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_f_go.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_f_go.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->f_go);
      union {
        float real;
        uint32_t base;
      } u_f_back;
      u_f_back.real = this->f_back;
      *(outbuffer + offset + 0) = (u_f_back.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_f_back.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_f_back.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_f_back.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->f_back);
      union {
        float real;
        uint32_t base;
      } u_r_go;
      u_r_go.real = this->r_go;
      *(outbuffer + offset + 0) = (u_r_go.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_r_go.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_r_go.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_r_go.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->r_go);
      union {
        float real;
        uint32_t base;
      } u_r_back;
      u_r_back.real = this->r_back;
      *(outbuffer + offset + 0) = (u_r_back.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_r_back.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_r_back.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_r_back.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->r_back);
      union {
        float real;
        uint32_t base;
      } u_f_go2;
      u_f_go2.real = this->f_go2;
      *(outbuffer + offset + 0) = (u_f_go2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_f_go2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_f_go2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_f_go2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->f_go2);
      union {
        float real;
        uint32_t base;
      } u_f_back2;
      u_f_back2.real = this->f_back2;
      *(outbuffer + offset + 0) = (u_f_back2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_f_back2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_f_back2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_f_back2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->f_back2);
      union {
        float real;
        uint32_t base;
      } u_r_go2;
      u_r_go2.real = this->r_go2;
      *(outbuffer + offset + 0) = (u_r_go2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_r_go2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_r_go2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_r_go2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->r_go2);
      union {
        float real;
        uint32_t base;
      } u_r_back2;
      u_r_back2.real = this->r_back2;
      *(outbuffer + offset + 0) = (u_r_back2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_r_back2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_r_back2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_r_back2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->r_back2);
      union {
        int32_t real;
        uint32_t base;
      } u_d_time;
      u_d_time.real = this->d_time;
      *(outbuffer + offset + 0) = (u_d_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_d_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_d_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_d_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->d_time);
      union {
        int32_t real;
        uint32_t base;
      } u_d_time2;
      u_d_time2.real = this->d_time2;
      *(outbuffer + offset + 0) = (u_d_time2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_d_time2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_d_time2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_d_time2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->d_time2);
      union {
        int8_t real;
        uint8_t base;
      } u_count;
      u_count.real = this->count;
      *(outbuffer + offset + 0) = (u_count.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->count);
      *(outbuffer + offset + 0) = (this->stride_front >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stride_front);
      *(outbuffer + offset + 0) = (this->stride_rear >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stride_rear);
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
      } u_start_sig;
      u_start_sig.real = this->start_sig;
      *(outbuffer + offset + 0) = (u_start_sig.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->start_sig);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->cont =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->cont);
      this->direction =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->direction);
      union {
        float real;
        uint32_t base;
      } u_f_go;
      u_f_go.base = 0;
      u_f_go.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_f_go.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_f_go.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_f_go.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->f_go = u_f_go.real;
      offset += sizeof(this->f_go);
      union {
        float real;
        uint32_t base;
      } u_f_back;
      u_f_back.base = 0;
      u_f_back.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_f_back.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_f_back.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_f_back.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->f_back = u_f_back.real;
      offset += sizeof(this->f_back);
      union {
        float real;
        uint32_t base;
      } u_r_go;
      u_r_go.base = 0;
      u_r_go.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_r_go.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_r_go.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_r_go.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->r_go = u_r_go.real;
      offset += sizeof(this->r_go);
      union {
        float real;
        uint32_t base;
      } u_r_back;
      u_r_back.base = 0;
      u_r_back.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_r_back.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_r_back.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_r_back.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->r_back = u_r_back.real;
      offset += sizeof(this->r_back);
      union {
        float real;
        uint32_t base;
      } u_f_go2;
      u_f_go2.base = 0;
      u_f_go2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_f_go2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_f_go2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_f_go2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->f_go2 = u_f_go2.real;
      offset += sizeof(this->f_go2);
      union {
        float real;
        uint32_t base;
      } u_f_back2;
      u_f_back2.base = 0;
      u_f_back2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_f_back2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_f_back2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_f_back2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->f_back2 = u_f_back2.real;
      offset += sizeof(this->f_back2);
      union {
        float real;
        uint32_t base;
      } u_r_go2;
      u_r_go2.base = 0;
      u_r_go2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_r_go2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_r_go2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_r_go2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->r_go2 = u_r_go2.real;
      offset += sizeof(this->r_go2);
      union {
        float real;
        uint32_t base;
      } u_r_back2;
      u_r_back2.base = 0;
      u_r_back2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_r_back2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_r_back2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_r_back2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->r_back2 = u_r_back2.real;
      offset += sizeof(this->r_back2);
      union {
        int32_t real;
        uint32_t base;
      } u_d_time;
      u_d_time.base = 0;
      u_d_time.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_d_time.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_d_time.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_d_time.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->d_time = u_d_time.real;
      offset += sizeof(this->d_time);
      union {
        int32_t real;
        uint32_t base;
      } u_d_time2;
      u_d_time2.base = 0;
      u_d_time2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_d_time2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_d_time2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_d_time2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->d_time2 = u_d_time2.real;
      offset += sizeof(this->d_time2);
      union {
        int8_t real;
        uint8_t base;
      } u_count;
      u_count.base = 0;
      u_count.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->count = u_count.real;
      offset += sizeof(this->count);
      this->stride_front =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->stride_front);
      this->stride_rear =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->stride_rear);
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
      } u_start_sig;
      u_start_sig.base = 0;
      u_start_sig.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->start_sig = u_start_sig.real;
      offset += sizeof(this->start_sig);
     return offset;
    }

    const char * getType(){ return "underwalker_control/uw_control_walking"; };
    const char * getMD5(){ return "610a8b04bd5ec2dc3050298ffea018b3"; };

  };

}
#endif
