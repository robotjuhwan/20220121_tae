#ifndef _ROS_underwalker_control_uw_control_v2_h
#define _ROS_underwalker_control_uw_control_v2_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace underwalker_control
{

  class uw_control_v2 : public ros::Msg
  {
    public:
      typedef int8_t _mode_type;
      _mode_type mode;
      typedef int8_t _direction_type;
      _direction_type direction;
      typedef int8_t _pectoral_cont_type;
      _pectoral_cont_type pectoral_cont;
      typedef double _pectoral_amp_type;
      _pectoral_amp_type pectoral_amp;
      typedef double _pectoral_offset_type;
      _pectoral_offset_type pectoral_offset;
      typedef double _pectoral_period_type;
      _pectoral_period_type pectoral_period;
      typedef int8_t _pectoral_pattern_type;
      _pectoral_pattern_type pectoral_pattern;
      typedef int8_t _pectoral_count_diff_type;
      _pectoral_count_diff_type pectoral_count_diff;
      typedef int8_t _pelvic_cont_type;
      _pelvic_cont_type pelvic_cont;
      typedef double _pelvic_amp_type;
      _pelvic_amp_type pelvic_amp;
      typedef double _pelvic_offset_type;
      _pelvic_offset_type pelvic_offset;
      typedef double _pelvic_period_type;
      _pelvic_period_type pelvic_period;
      typedef int8_t _pelvic_pattern_type;
      _pelvic_pattern_type pelvic_pattern;
      typedef int8_t _pelvic_count_diff_type;
      _pelvic_count_diff_type pelvic_count_diff;

    uw_control_v2():
      mode(0),
      direction(0),
      pectoral_cont(0),
      pectoral_amp(0),
      pectoral_offset(0),
      pectoral_period(0),
      pectoral_pattern(0),
      pectoral_count_diff(0),
      pelvic_cont(0),
      pelvic_amp(0),
      pelvic_offset(0),
      pelvic_period(0),
      pelvic_pattern(0),
      pelvic_count_diff(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
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
      } u_direction;
      u_direction.real = this->direction;
      *(outbuffer + offset + 0) = (u_direction.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction);
      union {
        int8_t real;
        uint8_t base;
      } u_pectoral_cont;
      u_pectoral_cont.real = this->pectoral_cont;
      *(outbuffer + offset + 0) = (u_pectoral_cont.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pectoral_cont);
      union {
        double real;
        uint64_t base;
      } u_pectoral_amp;
      u_pectoral_amp.real = this->pectoral_amp;
      *(outbuffer + offset + 0) = (u_pectoral_amp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pectoral_amp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pectoral_amp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pectoral_amp.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_pectoral_amp.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_pectoral_amp.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_pectoral_amp.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_pectoral_amp.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->pectoral_amp);
      union {
        double real;
        uint64_t base;
      } u_pectoral_offset;
      u_pectoral_offset.real = this->pectoral_offset;
      *(outbuffer + offset + 0) = (u_pectoral_offset.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pectoral_offset.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pectoral_offset.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pectoral_offset.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_pectoral_offset.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_pectoral_offset.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_pectoral_offset.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_pectoral_offset.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->pectoral_offset);
      union {
        double real;
        uint64_t base;
      } u_pectoral_period;
      u_pectoral_period.real = this->pectoral_period;
      *(outbuffer + offset + 0) = (u_pectoral_period.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pectoral_period.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pectoral_period.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pectoral_period.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_pectoral_period.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_pectoral_period.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_pectoral_period.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_pectoral_period.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->pectoral_period);
      union {
        int8_t real;
        uint8_t base;
      } u_pectoral_pattern;
      u_pectoral_pattern.real = this->pectoral_pattern;
      *(outbuffer + offset + 0) = (u_pectoral_pattern.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pectoral_pattern);
      union {
        int8_t real;
        uint8_t base;
      } u_pectoral_count_diff;
      u_pectoral_count_diff.real = this->pectoral_count_diff;
      *(outbuffer + offset + 0) = (u_pectoral_count_diff.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pectoral_count_diff);
      union {
        int8_t real;
        uint8_t base;
      } u_pelvic_cont;
      u_pelvic_cont.real = this->pelvic_cont;
      *(outbuffer + offset + 0) = (u_pelvic_cont.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pelvic_cont);
      union {
        double real;
        uint64_t base;
      } u_pelvic_amp;
      u_pelvic_amp.real = this->pelvic_amp;
      *(outbuffer + offset + 0) = (u_pelvic_amp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pelvic_amp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pelvic_amp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pelvic_amp.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_pelvic_amp.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_pelvic_amp.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_pelvic_amp.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_pelvic_amp.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->pelvic_amp);
      union {
        double real;
        uint64_t base;
      } u_pelvic_offset;
      u_pelvic_offset.real = this->pelvic_offset;
      *(outbuffer + offset + 0) = (u_pelvic_offset.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pelvic_offset.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pelvic_offset.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pelvic_offset.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_pelvic_offset.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_pelvic_offset.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_pelvic_offset.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_pelvic_offset.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->pelvic_offset);
      union {
        double real;
        uint64_t base;
      } u_pelvic_period;
      u_pelvic_period.real = this->pelvic_period;
      *(outbuffer + offset + 0) = (u_pelvic_period.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pelvic_period.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pelvic_period.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pelvic_period.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_pelvic_period.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_pelvic_period.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_pelvic_period.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_pelvic_period.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->pelvic_period);
      union {
        int8_t real;
        uint8_t base;
      } u_pelvic_pattern;
      u_pelvic_pattern.real = this->pelvic_pattern;
      *(outbuffer + offset + 0) = (u_pelvic_pattern.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pelvic_pattern);
      union {
        int8_t real;
        uint8_t base;
      } u_pelvic_count_diff;
      u_pelvic_count_diff.real = this->pelvic_count_diff;
      *(outbuffer + offset + 0) = (u_pelvic_count_diff.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pelvic_count_diff);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
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
      } u_direction;
      u_direction.base = 0;
      u_direction.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->direction = u_direction.real;
      offset += sizeof(this->direction);
      union {
        int8_t real;
        uint8_t base;
      } u_pectoral_cont;
      u_pectoral_cont.base = 0;
      u_pectoral_cont.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pectoral_cont = u_pectoral_cont.real;
      offset += sizeof(this->pectoral_cont);
      union {
        double real;
        uint64_t base;
      } u_pectoral_amp;
      u_pectoral_amp.base = 0;
      u_pectoral_amp.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pectoral_amp.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pectoral_amp.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pectoral_amp.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_pectoral_amp.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_pectoral_amp.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_pectoral_amp.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_pectoral_amp.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->pectoral_amp = u_pectoral_amp.real;
      offset += sizeof(this->pectoral_amp);
      union {
        double real;
        uint64_t base;
      } u_pectoral_offset;
      u_pectoral_offset.base = 0;
      u_pectoral_offset.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pectoral_offset.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pectoral_offset.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pectoral_offset.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_pectoral_offset.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_pectoral_offset.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_pectoral_offset.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_pectoral_offset.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->pectoral_offset = u_pectoral_offset.real;
      offset += sizeof(this->pectoral_offset);
      union {
        double real;
        uint64_t base;
      } u_pectoral_period;
      u_pectoral_period.base = 0;
      u_pectoral_period.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pectoral_period.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pectoral_period.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pectoral_period.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_pectoral_period.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_pectoral_period.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_pectoral_period.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_pectoral_period.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->pectoral_period = u_pectoral_period.real;
      offset += sizeof(this->pectoral_period);
      union {
        int8_t real;
        uint8_t base;
      } u_pectoral_pattern;
      u_pectoral_pattern.base = 0;
      u_pectoral_pattern.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pectoral_pattern = u_pectoral_pattern.real;
      offset += sizeof(this->pectoral_pattern);
      union {
        int8_t real;
        uint8_t base;
      } u_pectoral_count_diff;
      u_pectoral_count_diff.base = 0;
      u_pectoral_count_diff.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pectoral_count_diff = u_pectoral_count_diff.real;
      offset += sizeof(this->pectoral_count_diff);
      union {
        int8_t real;
        uint8_t base;
      } u_pelvic_cont;
      u_pelvic_cont.base = 0;
      u_pelvic_cont.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pelvic_cont = u_pelvic_cont.real;
      offset += sizeof(this->pelvic_cont);
      union {
        double real;
        uint64_t base;
      } u_pelvic_amp;
      u_pelvic_amp.base = 0;
      u_pelvic_amp.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pelvic_amp.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pelvic_amp.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pelvic_amp.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_pelvic_amp.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_pelvic_amp.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_pelvic_amp.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_pelvic_amp.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->pelvic_amp = u_pelvic_amp.real;
      offset += sizeof(this->pelvic_amp);
      union {
        double real;
        uint64_t base;
      } u_pelvic_offset;
      u_pelvic_offset.base = 0;
      u_pelvic_offset.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pelvic_offset.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pelvic_offset.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pelvic_offset.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_pelvic_offset.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_pelvic_offset.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_pelvic_offset.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_pelvic_offset.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->pelvic_offset = u_pelvic_offset.real;
      offset += sizeof(this->pelvic_offset);
      union {
        double real;
        uint64_t base;
      } u_pelvic_period;
      u_pelvic_period.base = 0;
      u_pelvic_period.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pelvic_period.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pelvic_period.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pelvic_period.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_pelvic_period.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_pelvic_period.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_pelvic_period.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_pelvic_period.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->pelvic_period = u_pelvic_period.real;
      offset += sizeof(this->pelvic_period);
      union {
        int8_t real;
        uint8_t base;
      } u_pelvic_pattern;
      u_pelvic_pattern.base = 0;
      u_pelvic_pattern.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pelvic_pattern = u_pelvic_pattern.real;
      offset += sizeof(this->pelvic_pattern);
      union {
        int8_t real;
        uint8_t base;
      } u_pelvic_count_diff;
      u_pelvic_count_diff.base = 0;
      u_pelvic_count_diff.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pelvic_count_diff = u_pelvic_count_diff.real;
      offset += sizeof(this->pelvic_count_diff);
     return offset;
    }

    virtual const char * getType() { return "underwalker_control/uw_control_v2"; };
    virtual const char * getMD5() { return "aa321638c85d92b391ed56d0d5f9df2b"; };

  };

}
#endif
