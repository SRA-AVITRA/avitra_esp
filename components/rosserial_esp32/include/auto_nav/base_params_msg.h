#ifndef _ROS_auto_nav_base_params_msg_h
#define _ROS_auto_nav_base_params_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace auto_nav
{

  class base_params_msg : public ros::Msg
  {
    public:
      typedef int32_t _ticks_L_type;
      _ticks_L_type ticks_L;
      typedef int32_t _ticks_R_type;
      _ticks_R_type ticks_R;
      typedef float _desr_rpm_L_type;
      _desr_rpm_L_type desr_rpm_L;
      typedef float _desr_rpm_R_type;
      _desr_rpm_R_type desr_rpm_R;
      typedef float _curr_rpm_L_type;
      _curr_rpm_L_type curr_rpm_L;
      typedef float _curr_rpm_R_type;
      _curr_rpm_R_type curr_rpm_R;

    base_params_msg():
      ticks_L(0),
      ticks_R(0),
      desr_rpm_L(0),
      desr_rpm_R(0),
      curr_rpm_L(0),
      curr_rpm_R(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_ticks_L;
      u_ticks_L.real = this->ticks_L;
      *(outbuffer + offset + 0) = (u_ticks_L.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ticks_L.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ticks_L.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ticks_L.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ticks_L);
      union {
        int32_t real;
        uint32_t base;
      } u_ticks_R;
      u_ticks_R.real = this->ticks_R;
      *(outbuffer + offset + 0) = (u_ticks_R.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ticks_R.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ticks_R.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ticks_R.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ticks_R);
      union {
        float real;
        uint32_t base;
      } u_desr_rpm_L;
      u_desr_rpm_L.real = this->desr_rpm_L;
      *(outbuffer + offset + 0) = (u_desr_rpm_L.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_desr_rpm_L.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_desr_rpm_L.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_desr_rpm_L.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->desr_rpm_L);
      union {
        float real;
        uint32_t base;
      } u_desr_rpm_R;
      u_desr_rpm_R.real = this->desr_rpm_R;
      *(outbuffer + offset + 0) = (u_desr_rpm_R.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_desr_rpm_R.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_desr_rpm_R.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_desr_rpm_R.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->desr_rpm_R);
      union {
        float real;
        uint32_t base;
      } u_curr_rpm_L;
      u_curr_rpm_L.real = this->curr_rpm_L;
      *(outbuffer + offset + 0) = (u_curr_rpm_L.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_curr_rpm_L.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_curr_rpm_L.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_curr_rpm_L.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->curr_rpm_L);
      union {
        float real;
        uint32_t base;
      } u_curr_rpm_R;
      u_curr_rpm_R.real = this->curr_rpm_R;
      *(outbuffer + offset + 0) = (u_curr_rpm_R.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_curr_rpm_R.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_curr_rpm_R.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_curr_rpm_R.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->curr_rpm_R);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_ticks_L;
      u_ticks_L.base = 0;
      u_ticks_L.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ticks_L.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ticks_L.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ticks_L.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ticks_L = u_ticks_L.real;
      offset += sizeof(this->ticks_L);
      union {
        int32_t real;
        uint32_t base;
      } u_ticks_R;
      u_ticks_R.base = 0;
      u_ticks_R.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ticks_R.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ticks_R.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ticks_R.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ticks_R = u_ticks_R.real;
      offset += sizeof(this->ticks_R);
      union {
        float real;
        uint32_t base;
      } u_desr_rpm_L;
      u_desr_rpm_L.base = 0;
      u_desr_rpm_L.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_desr_rpm_L.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_desr_rpm_L.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_desr_rpm_L.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->desr_rpm_L = u_desr_rpm_L.real;
      offset += sizeof(this->desr_rpm_L);
      union {
        float real;
        uint32_t base;
      } u_desr_rpm_R;
      u_desr_rpm_R.base = 0;
      u_desr_rpm_R.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_desr_rpm_R.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_desr_rpm_R.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_desr_rpm_R.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->desr_rpm_R = u_desr_rpm_R.real;
      offset += sizeof(this->desr_rpm_R);
      union {
        float real;
        uint32_t base;
      } u_curr_rpm_L;
      u_curr_rpm_L.base = 0;
      u_curr_rpm_L.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_curr_rpm_L.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_curr_rpm_L.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_curr_rpm_L.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->curr_rpm_L = u_curr_rpm_L.real;
      offset += sizeof(this->curr_rpm_L);
      union {
        float real;
        uint32_t base;
      } u_curr_rpm_R;
      u_curr_rpm_R.base = 0;
      u_curr_rpm_R.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_curr_rpm_R.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_curr_rpm_R.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_curr_rpm_R.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->curr_rpm_R = u_curr_rpm_R.real;
      offset += sizeof(this->curr_rpm_R);
     return offset;
    }

    const char * getType(){ return "auto_nav/base_params_msg"; };
    const char * getMD5(){ return "4ec75baf2dbe72517636afe9c84dccfd"; };

  };

}
#endif
