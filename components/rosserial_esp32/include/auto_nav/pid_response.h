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
      typedef const char* _name_type;
      _name_type name;
      typedef float _duty_cycle_type;
      _duty_cycle_type duty_cycle;
      typedef float _prev_duty_cycle_type;
      _prev_duty_cycle_type prev_duty_cycle;
      typedef float _actual_duty_cycle_type;
      _actual_duty_cycle_type actual_duty_cycle;
      typedef float _desr_rpm_type;
      _desr_rpm_type desr_rpm;
      typedef float _curr_rpm_type;
      _curr_rpm_type curr_rpm;
      typedef float _prev_rpm_type;
      _prev_rpm_type prev_rpm;
      typedef float _err_type;
      _err_type err;
      typedef float _prev_err_type;
      _prev_err_type prev_err;
      typedef float _cum_err_type;
      _cum_err_type cum_err;
      typedef float _pTerm_type;
      _pTerm_type pTerm;
      typedef float _dTerm_type;
      _dTerm_type dTerm;
      typedef float _iTerm_type;
      _iTerm_type iTerm;
      typedef float _iTerm_limit_type;
      _iTerm_limit_type iTerm_limit;
      typedef float _alpha_type;
      _alpha_type alpha;

    pid_response():
      name(""),
      duty_cycle(0),
      prev_duty_cycle(0),
      actual_duty_cycle(0),
      desr_rpm(0),
      curr_rpm(0),
      prev_rpm(0),
      err(0),
      prev_err(0),
      cum_err(0),
      pTerm(0),
      dTerm(0),
      iTerm(0),
      iTerm_limit(0),
      alpha(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
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
      } u_prev_duty_cycle;
      u_prev_duty_cycle.real = this->prev_duty_cycle;
      *(outbuffer + offset + 0) = (u_prev_duty_cycle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_prev_duty_cycle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_prev_duty_cycle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_prev_duty_cycle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->prev_duty_cycle);
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
        float real;
        uint32_t base;
      } u_desr_rpm;
      u_desr_rpm.real = this->desr_rpm;
      *(outbuffer + offset + 0) = (u_desr_rpm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_desr_rpm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_desr_rpm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_desr_rpm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->desr_rpm);
      union {
        float real;
        uint32_t base;
      } u_curr_rpm;
      u_curr_rpm.real = this->curr_rpm;
      *(outbuffer + offset + 0) = (u_curr_rpm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_curr_rpm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_curr_rpm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_curr_rpm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->curr_rpm);
      union {
        float real;
        uint32_t base;
      } u_prev_rpm;
      u_prev_rpm.real = this->prev_rpm;
      *(outbuffer + offset + 0) = (u_prev_rpm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_prev_rpm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_prev_rpm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_prev_rpm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->prev_rpm);
      union {
        float real;
        uint32_t base;
      } u_err;
      u_err.real = this->err;
      *(outbuffer + offset + 0) = (u_err.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_err.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_err.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_err.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->err);
      union {
        float real;
        uint32_t base;
      } u_prev_err;
      u_prev_err.real = this->prev_err;
      *(outbuffer + offset + 0) = (u_prev_err.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_prev_err.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_prev_err.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_prev_err.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->prev_err);
      union {
        float real;
        uint32_t base;
      } u_cum_err;
      u_cum_err.real = this->cum_err;
      *(outbuffer + offset + 0) = (u_cum_err.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cum_err.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cum_err.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cum_err.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cum_err);
      union {
        float real;
        uint32_t base;
      } u_pTerm;
      u_pTerm.real = this->pTerm;
      *(outbuffer + offset + 0) = (u_pTerm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pTerm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pTerm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pTerm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pTerm);
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
        float real;
        uint32_t base;
      } u_iTerm_limit;
      u_iTerm_limit.real = this->iTerm_limit;
      *(outbuffer + offset + 0) = (u_iTerm_limit.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_iTerm_limit.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_iTerm_limit.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_iTerm_limit.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->iTerm_limit);
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
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
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
      } u_prev_duty_cycle;
      u_prev_duty_cycle.base = 0;
      u_prev_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_prev_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_prev_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_prev_duty_cycle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->prev_duty_cycle = u_prev_duty_cycle.real;
      offset += sizeof(this->prev_duty_cycle);
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
        float real;
        uint32_t base;
      } u_desr_rpm;
      u_desr_rpm.base = 0;
      u_desr_rpm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_desr_rpm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_desr_rpm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_desr_rpm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->desr_rpm = u_desr_rpm.real;
      offset += sizeof(this->desr_rpm);
      union {
        float real;
        uint32_t base;
      } u_curr_rpm;
      u_curr_rpm.base = 0;
      u_curr_rpm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_curr_rpm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_curr_rpm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_curr_rpm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->curr_rpm = u_curr_rpm.real;
      offset += sizeof(this->curr_rpm);
      union {
        float real;
        uint32_t base;
      } u_prev_rpm;
      u_prev_rpm.base = 0;
      u_prev_rpm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_prev_rpm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_prev_rpm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_prev_rpm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->prev_rpm = u_prev_rpm.real;
      offset += sizeof(this->prev_rpm);
      union {
        float real;
        uint32_t base;
      } u_err;
      u_err.base = 0;
      u_err.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_err.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_err.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_err.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->err = u_err.real;
      offset += sizeof(this->err);
      union {
        float real;
        uint32_t base;
      } u_prev_err;
      u_prev_err.base = 0;
      u_prev_err.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_prev_err.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_prev_err.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_prev_err.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->prev_err = u_prev_err.real;
      offset += sizeof(this->prev_err);
      union {
        float real;
        uint32_t base;
      } u_cum_err;
      u_cum_err.base = 0;
      u_cum_err.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cum_err.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cum_err.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cum_err.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cum_err = u_cum_err.real;
      offset += sizeof(this->cum_err);
      union {
        float real;
        uint32_t base;
      } u_pTerm;
      u_pTerm.base = 0;
      u_pTerm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pTerm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pTerm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pTerm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pTerm = u_pTerm.real;
      offset += sizeof(this->pTerm);
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
     return offset;
    }

    const char * getType(){ return "auto_nav/pid_response"; };
    const char * getMD5(){ return "0adcd4aea359746f6bcca4fa6e8c81c5"; };

  };

}
#endif
