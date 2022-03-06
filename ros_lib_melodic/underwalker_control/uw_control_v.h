#ifndef _ROS_underwalker_control_uw_control_v_h
#define _ROS_underwalker_control_uw_control_v_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace underwalker_control
{

  class uw_control_v : public ros::Msg
  {
    public:
      typedef uint8_t _mode_type;
      _mode_type mode;
      typedef uint8_t _buoy_front_type;
      _buoy_front_type buoy_front;
      typedef uint8_t _buoy_rear_type;
      _buoy_rear_type buoy_rear;

    uw_control_v():
      mode(0),
      buoy_front(0),
      buoy_rear(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      *(outbuffer + offset + 0) = (this->buoy_front >> (8 * 0)) & 0xFF;
      offset += sizeof(this->buoy_front);
      *(outbuffer + offset + 0) = (this->buoy_rear >> (8 * 0)) & 0xFF;
      offset += sizeof(this->buoy_rear);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
      this->buoy_front =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->buoy_front);
      this->buoy_rear =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->buoy_rear);
     return offset;
    }

    const char * getType(){ return "underwalker_control/uw_control_v"; };
    const char * getMD5(){ return "0b5864e326602d3b2187aacbd055d030"; };

  };

}
#endif
