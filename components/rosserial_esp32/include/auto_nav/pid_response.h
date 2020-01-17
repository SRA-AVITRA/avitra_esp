#ifndef _ROS_auto_nav_pid_response_h
#define _ROS_auto_nav_pid_response_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace auto_nav
{

  class pid_response : public ros::Msg
  {
    public:
      typedef float _duty_cycle_type;
      _duty_cycle_type duty_cycle;
      typedef float _actual_duty_cycle_type;
      _actual_duty_cycle_type actual_duty_cycle;
      typedef int16_t _err_type;
      _err_type err;
      typedef int16_t _pre_err_type;
      _pre_err_type pre_err;
      typedef float _pterm_type;
      _pterm_type pterm;
      typedef float _dTerm_type;
      _dTerm_type dTerm;
      typedef float _iTerm_type;
      _iTerm_type iTerm;
      typedef int16_t _desr_rpm_type;
      _desr_rpm_type desr_rpm;
      typedef int16_t _curr_rpm_type;
      _curr_rpm_type curr_rpm;
      typedef int16_t _pre_rpm_type;
      _pre_rpm_type pre_rpm;

    pid_response():
      duty_cycle(0),
      actual_duty_cycle(0),
      err(0),
      pre_err(0),
      pterm(0),
      dTerm(0),
      iTerm(0),
      desr_rpm(0),
      curr_rpm(0),
      pre_rpm(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_duty_cycle;
      u_duty_cycle.real = this->duty_cycle;
      *(outbuffer + offset + 0) = (u_duty_cycle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_duty_cycle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_duty_cycle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_duty_cycle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duty_cycle);
      union {
        float real;
        uint32_t base;
      } u_actual_duty_cycle;
      u_actual_duty_cycle.real = this->actual_duty_cycle;
      *(outbuffer + offset + 0) = (u_actual_duty_cycle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_actual_duty_cycle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_actual_duty_cycle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_actual_duty_cycle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->actual_duty_cycle);
      union {
        int16_t real;
        uint16_t base;
      } u_err;
      u_err.real = this->err;
      *(outbuffer + offset + 0) = (u_err.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_err.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->err);
      union {
        int16_t real;
        uint16_t base;
      } u_pre_err;
      u_pre_err.real = this->pre_err;
      *(outbuffer + offset + 0) = (u_pre_err.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pre_err.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->pre_err);
      union {
        float real;
        uint32_t base;
      } u_pterm;
      u_pterm.real = this->pterm;
      *(outbuffer + offset + 0) = (u_pterm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pterm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pterm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pterm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pterm);
      union {
        float real;
        uint32_t base;
      } u_dTerm;
      u_dTerm.real = this->dTerm;
      *(outbuffer + offset + 0) = (u_dTerm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dTerm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dTerm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dTerm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dTerm);
      union {
        float real;
        uint32_t base;
      } u_iTerm;
      u_iTerm.real = this->iTerm;
      *(outbuffer + offset + 0) = (u_iTerm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_iTerm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_iTerm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_iTerm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->iTerm);
      union {
        int16_t real;
        uint16_t base;
      } u_desr_rpm;
      u_desr_rpm.real = this->desr_rpm;
      *(outbuffer + offset + 0) = (u_desr_rpm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_desr_rpm.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->desr_rpm);
      union {
        int16_t real;
        uint16_t base;
      } u_curr_rpm;
      u_curr_rpm.real = this->curr_rpm;
      *(outbuffer + offset + 0) = (u_curr_rpm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_curr_rpm.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->curr_rpm);
      union {
        int16_t real;
        uint16_t base;
      } u_pre_rpm;
      u_pre_rpm.real = this->pre_rpm;
      *(outbuffer + offset + 0) = (u_pre_rpm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pre_rpm.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->pre_rpm);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_duty_cycle;
      u_duty_cycle.base = 0;
      u_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->duty_cycle = u_duty_cycle.real;
      offset += sizeof(this->duty_cycle);
      union {
        float real;
        uint32_t base;
      } u_actual_duty_cycle;
      u_actual_duty_cycle.base = 0;
      u_actual_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_actual_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_actual_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_actual_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->actual_duty_cycle = u_actual_duty_cycle.real;
      offset += sizeof(this->actual_duty_cycle);
      union {
        int16_t real;
        uint16_t base;
      } u_err;
      u_err.base = 0;
      u_err.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_err.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->err = u_err.real;
      offset += sizeof(this->err);
      union {
        int16_t real;
        uint16_t base;
      } u_pre_err;
      u_pre_err.base = 0;
      u_pre_err.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pre_err.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->pre_err = u_pre_err.real;
      offset += sizeof(this->pre_err);
      union {
        float real;
        uint32_t base;
      } u_pterm;
      u_pterm.base = 0;
      u_pterm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pterm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pterm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pterm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pterm = u_pterm.real;
      offset += sizeof(this->pterm);
      union {
        float real;
        uint32_t base;
      } u_dTerm;
      u_dTerm.base = 0;
      u_dTerm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dTerm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dTerm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dTerm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dTerm = u_dTerm.real;
      offset += sizeof(this->dTerm);
      union {
        float real;
        uint32_t base;
      } u_iTerm;
      u_iTerm.base = 0;
      u_iTerm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_iTerm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_iTerm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_iTerm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->iTerm = u_iTerm.real;
      offset += sizeof(this->iTerm);
      union {
        int16_t real;
        uint16_t base;
      } u_desr_rpm;
      u_desr_rpm.base = 0;
      u_desr_rpm.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_desr_rpm.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->desr_rpm = u_desr_rpm.real;
      offset += sizeof(this->desr_rpm);
      union {
        int16_t real;
        uint16_t base;
      } u_curr_rpm;
      u_curr_rpm.base = 0;
      u_curr_rpm.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_curr_rpm.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->curr_rpm = u_curr_rpm.real;
      offset += sizeof(this->curr_rpm);
      union {
        int16_t real;
        uint16_t base;
      } u_pre_rpm;
      u_pre_rpm.base = 0;
      u_pre_rpm.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pre_rpm.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->pre_rpm = u_pre_rpm.real;
      offset += sizeof(this->pre_rpm);
     return offset;
    }

    const char * getType(){ return "auto_nav/pid_response"; };
    const char * getMD5(){ return "fa7fd941f69cd24b769e3d8074cfe9c5"; };

  };

}
#endif
