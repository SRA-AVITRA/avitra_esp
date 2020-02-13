#ifndef _ROS_auto_nav_motor_msg_h
#define _ROS_auto_nav_motor_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace auto_nav
{

  class motor_msg : public ros::Msg
  {
    public:
      typedef float _motor_L_type;
      _motor_L_type motor_L;
      typedef float _motor_R_type;
      _motor_R_type motor_R;
      typedef int8_t _command_type;
      _command_type command;

    motor_msg():
      motor_L(0),
      motor_R(0),
      command(0)
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
        int8_t real;
        uint8_t base;
      } u_command;
      u_command.real = this->command;
      *(outbuffer + offset + 0) = (u_command.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->command);
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
        int8_t real;
        uint8_t base;
      } u_command;
      u_command.base = 0;
      u_command.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->command = u_command.real;
      offset += sizeof(this->command);
     return offset;
    }

    const char * getType(){ return "auto_nav/motor_msg"; };
    const char * getMD5(){ return "abd541b618c1fbc7bfae63b5a2338e1f"; };

  };

}
#endif
