#ifndef _ROS_auto_nav_tuning_msg_h
#define _ROS_auto_nav_tuning_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace auto_nav
{

  class tuning_msg : public ros::Msg
  {
    public:
      typedef float _Kp_type;
      _Kp_type Kp;
      typedef float _Ki_type;
      _Ki_type Ki;
      typedef float _Kd_type;
      _Kd_type Kd;
      typedef float _alpha_type;
      _alpha_type alpha;
      typedef float _iTerm_limit_type;
      _iTerm_limit_type iTerm_limit;

    tuning_msg():
      Kp(0),
      Ki(0),
      Kd(0),
      alpha(0),
      iTerm_limit(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Kp;
      u_Kp.real = this->Kp;
      *(outbuffer + offset + 0) = (u_Kp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Kp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Kp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Kp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Kp);
      union {
        float real;
        uint32_t base;
      } u_Ki;
      u_Ki.real = this->Ki;
      *(outbuffer + offset + 0) = (u_Ki.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Ki.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Ki.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Ki.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Ki);
      union {
        float real;
        uint32_t base;
      } u_Kd;
      u_Kd.real = this->Kd;
      *(outbuffer + offset + 0) = (u_Kd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Kd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Kd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Kd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Kd);
      union {
        float real;
        uint32_t base;
      } u_alpha;
      u_alpha.real = this->alpha;
      *(outbuffer + offset + 0) = (u_alpha.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_alpha.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_alpha.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_alpha.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->alpha);
      union {
        float real;
        uint32_t base;
      } u_iTerm_limit;
      u_iTerm_limit.real = this->iTerm_limit;
      *(outbuffer + offset + 0) = (u_iTerm_limit.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_iTerm_limit.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_iTerm_limit.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_iTerm_limit.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->iTerm_limit);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Kp;
      u_Kp.base = 0;
      u_Kp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Kp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Kp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Kp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Kp = u_Kp.real;
      offset += sizeof(this->Kp);
      union {
        float real;
        uint32_t base;
      } u_Ki;
      u_Ki.base = 0;
      u_Ki.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Ki.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Ki.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Ki.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Ki = u_Ki.real;
      offset += sizeof(this->Ki);
      union {
        float real;
        uint32_t base;
      } u_Kd;
      u_Kd.base = 0;
      u_Kd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Kd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Kd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Kd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Kd = u_Kd.real;
      offset += sizeof(this->Kd);
      union {
        float real;
        uint32_t base;
      } u_alpha;
      u_alpha.base = 0;
      u_alpha.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_alpha.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_alpha.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_alpha.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->alpha = u_alpha.real;
      offset += sizeof(this->alpha);
      union {
        float real;
        uint32_t base;
      } u_iTerm_limit;
      u_iTerm_limit.base = 0;
      u_iTerm_limit.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_iTerm_limit.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_iTerm_limit.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_iTerm_limit.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->iTerm_limit = u_iTerm_limit.real;
      offset += sizeof(this->iTerm_limit);
     return offset;
    }

    const char * getType(){ return "auto_nav/tuning_msg"; };
    const char * getMD5(){ return "725010a6824889adc4983723e3d2a44b"; };

  };

}
#endif
