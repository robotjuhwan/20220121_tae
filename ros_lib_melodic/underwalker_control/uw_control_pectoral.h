#ifndef _ROS_underwalker_control_uw_control_pectoral_h
#define _ROS_underwalker_control_uw_control_pectoral_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace underwalker_control
{

  class uw_control_pectoral : public ros::Msg
  {
    public:
      typedef uint8_t _cont_type;
      _cont_type cont;
      typedef uint8_t _direction_type;
      _direction_type direction;
      typedef float _period_type;
      _period_type period;
      typedef int8_t _count_type;
      _count_type count;
      typedef float _amplitude_type;
      _amplitude_type amplitude;
      typedef float _offset_type;
      _offset_type offset;
      typedef int8_t _pattern_type;
      _pattern_type pattern;
      typedef int8_t _count_diff_type;
      _count_diff_type count_diff;

    uw_control_pectoral():
      cont(0),
      direction(0),
      period(0),
      count(0),
      amplitude(0),
      offset(0),
      pattern(0),
      count_diff(0)
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
      } u_period;
      u_period.real = this->period;
      *(outbuffer + offset + 0) = (u_period.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_period.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_period.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_period.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->period);
      union {
        int8_t real;
        uint8_t base;
      } u_count;
      u_count.real = this->count;
      *(outbuffer + offset + 0) = (u_count.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->count);
      union {
        float real;
        uint32_t base;
      } u_amplitude;
      u_amplitude.real = this->amplitude;
      *(outbuffer + offset + 0) = (u_amplitude.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_amplitude.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_amplitude.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_amplitude.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->amplitude);
      union {
        float real;
        uint32_t base;
      } u_offset;
      u_offset.real = this->offset;
      *(outbuffer + offset + 0) = (u_offset.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_offset.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_offset.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_offset.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->offset);
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
      } u_count_diff;
      u_count_diff.real = this->count_diff;
      *(outbuffer + offset + 0) = (u_count_diff.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->count_diff);
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
      } u_period;
      u_period.base = 0;
      u_period.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_period.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_period.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_period.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->period = u_period.real;
      offset += sizeof(this->period);
      union {
        int8_t real;
        uint8_t base;
      } u_count;
      u_count.base = 0;
      u_count.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->count = u_count.real;
      offset += sizeof(this->count);
      union {
        float real;
        uint32_t base;
      } u_amplitude;
      u_amplitude.base = 0;
      u_amplitude.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_amplitude.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_amplitude.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_amplitude.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->amplitude = u_amplitude.real;
      offset += sizeof(this->amplitude);
      union {
        float real;
        uint32_t base;
      } u_offset;
      u_offset.base = 0;
      u_offset.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_offset.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_offset.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_offset.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->offset = u_offset.real;
      offset += sizeof(this->offset);
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
      } u_count_diff;
      u_count_diff.base = 0;
      u_count_diff.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->count_diff = u_count_diff.real;
      offset += sizeof(this->count_diff);
     return offset;
    }

    const char * getType(){ return "underwalker_control/uw_control_pectoral"; };
    const char * getMD5(){ return "fa2a6062e3304988563f06d519a97845"; };

  };

}
#endif
