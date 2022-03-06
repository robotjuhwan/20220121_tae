#ifndef _ROS_underwalker_control_uw_read_sensor_h
#define _ROS_underwalker_control_uw_read_sensor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace underwalker_control
{

  class uw_read_sensor : public ros::Msg
  {
    public:
      uint16_t position[9];
      int16_t current[9];
      typedef float _depth_type;
      _depth_type depth;
      typedef float _q1_type;
      _q1_type q1;
      typedef float _q2_type;
      _q2_type q2;
      typedef float _q3_type;
      _q3_type q3;
      typedef float _q4_type;
      _q4_type q4;

    uw_read_sensor():
      position(),
      current(),
      depth(0),
      q1(0),
      q2(0),
      q3(0),
      q4(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 9; i++){
      *(outbuffer + offset + 0) = (this->position[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->position[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->position[i]);
      }
      for( uint32_t i = 0; i < 9; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_currenti;
      u_currenti.real = this->current[i];
      *(outbuffer + offset + 0) = (u_currenti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_currenti.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->current[i]);
      }
      union {
        float real;
        uint32_t base;
      } u_depth;
      u_depth.real = this->depth;
      *(outbuffer + offset + 0) = (u_depth.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_depth.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_depth.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_depth.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->depth);
      union {
        float real;
        uint32_t base;
      } u_q1;
      u_q1.real = this->q1;
      *(outbuffer + offset + 0) = (u_q1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_q1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_q1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_q1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->q1);
      union {
        float real;
        uint32_t base;
      } u_q2;
      u_q2.real = this->q2;
      *(outbuffer + offset + 0) = (u_q2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_q2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_q2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_q2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->q2);
      union {
        float real;
        uint32_t base;
      } u_q3;
      u_q3.real = this->q3;
      *(outbuffer + offset + 0) = (u_q3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_q3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_q3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_q3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->q3);
      union {
        float real;
        uint32_t base;
      } u_q4;
      u_q4.real = this->q4;
      *(outbuffer + offset + 0) = (u_q4.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_q4.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_q4.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_q4.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->q4);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 9; i++){
      this->position[i] =  ((uint16_t) (*(inbuffer + offset)));
      this->position[i] |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->position[i]);
      }
      for( uint32_t i = 0; i < 9; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_currenti;
      u_currenti.base = 0;
      u_currenti.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_currenti.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->current[i] = u_currenti.real;
      offset += sizeof(this->current[i]);
      }
      union {
        float real;
        uint32_t base;
      } u_depth;
      u_depth.base = 0;
      u_depth.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_depth.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_depth.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_depth.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->depth = u_depth.real;
      offset += sizeof(this->depth);
      union {
        float real;
        uint32_t base;
      } u_q1;
      u_q1.base = 0;
      u_q1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_q1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_q1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_q1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->q1 = u_q1.real;
      offset += sizeof(this->q1);
      union {
        float real;
        uint32_t base;
      } u_q2;
      u_q2.base = 0;
      u_q2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_q2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_q2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_q2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->q2 = u_q2.real;
      offset += sizeof(this->q2);
      union {
        float real;
        uint32_t base;
      } u_q3;
      u_q3.base = 0;
      u_q3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_q3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_q3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_q3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->q3 = u_q3.real;
      offset += sizeof(this->q3);
      union {
        float real;
        uint32_t base;
      } u_q4;
      u_q4.base = 0;
      u_q4.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_q4.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_q4.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_q4.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->q4 = u_q4.real;
      offset += sizeof(this->q4);
     return offset;
    }

    const char * getType(){ return "underwalker_control/uw_read_sensor"; };
    const char * getMD5(){ return "c5f9811c87afd9b69ae8ef198604d734"; };

  };

}
#endif
