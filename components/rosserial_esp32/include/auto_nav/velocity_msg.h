#ifndef _ROS_auto_nav_velocity_msg_h
#define _ROS_auto_nav_velocity_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace auto_nav
{

  class velocity_msg : public ros::Msg
  {
    public:
      typedef float _motor_L_type;
      _motor_L_type motor_L;
      typedef float _motor_R_type;
      _motor_R_type motor_R;

    velocity_msg():
      motor_L(0),
      motor_R(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_motor_L;
      u_motor_L.real = this->motor_L;
      *(outbuffer + offset + 0) = (u_motor_L.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_L.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_L.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_L.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_L);
      union {
        float real;
        uint32_t base;
      } u_motor_R;
      u_motor_R.real = this->motor_R;
      *(outbuffer + offset + 0) = (u_motor_R.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_R.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_R.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_R.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_R);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_motor_L;
      u_motor_L.base = 0;
      u_motor_L.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_L.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_L.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_L.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_L = u_motor_L.real;
      offset += sizeof(this->motor_L);
      union {
        float real;
        uint32_t base;
      } u_motor_R;
      u_motor_R.base = 0;
      u_motor_R.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_R.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_R.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_R.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_R = u_motor_R.real;
      offset += sizeof(this->motor_R);
     return offset;
    }

    const char * getType(){ return "auto_nav/velocity_msg"; };
    const char * getMD5(){ return "b1d58d5d416127aa3178034f8061853a"; };

  };

}
#endif
