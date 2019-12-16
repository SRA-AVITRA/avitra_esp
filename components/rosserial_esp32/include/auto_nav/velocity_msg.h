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
      typedef float _motor_F_type;
      _motor_F_type motor_F;
      typedef float _motor_B_type;
      _motor_B_type motor_B;

    velocity_msg():
      motor_L(0),
      motor_R(0),
      motor_F(0),
      motor_B(0)
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
      union {
        float real;
        uint32_t base;
      } u_motor_F;
      u_motor_F.real = this->motor_F;
      *(outbuffer + offset + 0) = (u_motor_F.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_F.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_F.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_F.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_F);
      union {
        float real;
        uint32_t base;
      } u_motor_B;
      u_motor_B.real = this->motor_B;
      *(outbuffer + offset + 0) = (u_motor_B.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_B.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_B.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_B.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_B);
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
      union {
        float real;
        uint32_t base;
      } u_motor_F;
      u_motor_F.base = 0;
      u_motor_F.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_F.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_F.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_F.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_F = u_motor_F.real;
      offset += sizeof(this->motor_F);
      union {
        float real;
        uint32_t base;
      } u_motor_B;
      u_motor_B.base = 0;
      u_motor_B.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_B.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_B.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_B.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_B = u_motor_B.real;
      offset += sizeof(this->motor_B);
     return offset;
    }

    const char * getType(){ return "auto_nav/velocity_msg"; };
    const char * getMD5(){ return "203d7f6e594d0b47858d9ee8070dd28f"; };

  };

}
#endif
