#ifndef _ROS_auto_nav_ticks_msg_h
#define _ROS_auto_nav_ticks_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace auto_nav
{

  class ticks_msg : public ros::Msg
  {
    public:
      typedef uint64_t _motor_L_type;
      _motor_L_type motor_L;
      typedef uint64_t _motor_R_type;
      _motor_R_type motor_R;

    ticks_msg():
      motor_L(0),
      motor_R(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->motor_L >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->motor_L >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->motor_L >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->motor_L >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->motor_L >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->motor_L >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->motor_L >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->motor_L >> (8 * 7)) & 0xFF;
      offset += sizeof(this->motor_L);
      *(outbuffer + offset + 0) = (this->motor_R >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->motor_R >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->motor_R >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->motor_R >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->motor_R >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->motor_R >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->motor_R >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->motor_R >> (8 * 7)) & 0xFF;
      offset += sizeof(this->motor_R);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->motor_L =  ((uint64_t) (*(inbuffer + offset)));
      this->motor_L |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->motor_L |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->motor_L |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_L |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->motor_L |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->motor_L |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->motor_L |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->motor_L);
      this->motor_R =  ((uint64_t) (*(inbuffer + offset)));
      this->motor_R |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->motor_R |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->motor_R |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_R |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->motor_R |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->motor_R |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->motor_R |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->motor_R);
     return offset;
    }

    const char * getType(){ return "auto_nav/ticks_msg"; };
    const char * getMD5(){ return "d31ebb42ad2cd8a7430d04cef15fd41c"; };

  };

}
#endif
