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
      typedef int64_t _motor_L_type;
      _motor_L_type motor_L;
      typedef int64_t _motor_R_type;
      _motor_R_type motor_R;

    ticks_msg():
      motor_L(0),
      motor_R(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_motor_L;
      u_motor_L.real = this->motor_L;
      *(outbuffer + offset + 0) = (u_motor_L.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_L.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_L.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_L.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_motor_L.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_motor_L.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_motor_L.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_motor_L.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->motor_L);
      union {
        int64_t real;
        uint64_t base;
      } u_motor_R;
      u_motor_R.real = this->motor_R;
      *(outbuffer + offset + 0) = (u_motor_R.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_R.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_R.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_R.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_motor_R.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_motor_R.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_motor_R.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_motor_R.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->motor_R);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_motor_L;
      u_motor_L.base = 0;
      u_motor_L.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_L.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_L.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_L.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_motor_L.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_motor_L.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_motor_L.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_motor_L.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->motor_L = u_motor_L.real;
      offset += sizeof(this->motor_L);
      union {
        int64_t real;
        uint64_t base;
      } u_motor_R;
      u_motor_R.base = 0;
      u_motor_R.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_R.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_R.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_R.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_motor_R.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_motor_R.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_motor_R.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_motor_R.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->motor_R = u_motor_R.real;
      offset += sizeof(this->motor_R);
     return offset;
    }

    const char * getType(){ return "auto_nav/ticks_msg"; };
    const char * getMD5(){ return "2fc7a14e4e689ce5473d89f0b2cfd59a"; };

  };

}
#endif
