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
      typedef uint32_t _position1_type;
      _position1_type position1;
      typedef uint32_t _position2_type;
      _position2_type position2;
      typedef uint32_t _position3_type;
      _position3_type position3;
      typedef uint32_t _position4_type;
      _position4_type position4;
      typedef uint16_t _current1_type;
      _current1_type current1;
      typedef uint16_t _current2_type;
      _current2_type current2;
      typedef uint16_t _current3_type;
      _current3_type current3;
      typedef uint16_t _current4_type;
      _current4_type current4;

    uw_read_sensor():
      position1(0),
      position2(0),
      position3(0),
      position4(0),
      current1(0),
      current2(0),
      current3(0),
      current4(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->position1 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->position1 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->position1 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->position1 >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position1);
      *(outbuffer + offset + 0) = (this->position2 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->position2 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->position2 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->position2 >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position2);
      *(outbuffer + offset + 0) = (this->position3 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->position3 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->position3 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->position3 >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position3);
      *(outbuffer + offset + 0) = (this->position4 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->position4 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->position4 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->position4 >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position4);
      *(outbuffer + offset + 0) = (this->current1 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->current1 >> (8 * 1)) & 0xFF;
      offset += sizeof(this->current1);
      *(outbuffer + offset + 0) = (this->current2 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->current2 >> (8 * 1)) & 0xFF;
      offset += sizeof(this->current2);
      *(outbuffer + offset + 0) = (this->current3 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->current3 >> (8 * 1)) & 0xFF;
      offset += sizeof(this->current3);
      *(outbuffer + offset + 0) = (this->current4 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->current4 >> (8 * 1)) & 0xFF;
      offset += sizeof(this->current4);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->position1 =  ((uint32_t) (*(inbuffer + offset)));
      this->position1 |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->position1 |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->position1 |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->position1);
      this->position2 =  ((uint32_t) (*(inbuffer + offset)));
      this->position2 |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->position2 |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->position2 |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->position2);
      this->position3 =  ((uint32_t) (*(inbuffer + offset)));
      this->position3 |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->position3 |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->position3 |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->position3);
      this->position4 =  ((uint32_t) (*(inbuffer + offset)));
      this->position4 |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->position4 |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->position4 |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->position4);
      this->current1 =  ((uint16_t) (*(inbuffer + offset)));
      this->current1 |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->current1);
      this->current2 =  ((uint16_t) (*(inbuffer + offset)));
      this->current2 |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->current2);
      this->current3 =  ((uint16_t) (*(inbuffer + offset)));
      this->current3 |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->current3);
      this->current4 =  ((uint16_t) (*(inbuffer + offset)));
      this->current4 |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->current4);
     return offset;
    }

    virtual const char * getType() { return "underwalker_control/uw_read_sensor"; };
    virtual const char * getMD5() { return "1bf3d12d7663a5c4686eb74331c3815a"; };

  };

}
#endif
