#ifndef _ROS_SERVICE_tuning_h
#define _ROS_SERVICE_tuning_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace beginner_tutorials
{

static const char TUNING[] = "beginner_tutorials/tuning";

  class tuningRequest : public ros::Msg
  {
    public:
      typedef double _Kp_type;
      _Kp_type Kp;
      typedef double _Kd_type;
      _Kd_type Kd;
      typedef double _Ki_type;
      _Ki_type Ki;

    tuningRequest():
      Kp(0),
      Kd(0),
      Ki(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        double real;
        uint32_t base;
      } u_Kp;
      u_Kp.real = this->Kp;
      *(outbuffer + offset + 0) = (u_Kp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Kp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Kp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Kp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Kp);
      union {
        double real;
        uint32_t base;
      } u_Kd;
      u_Kd.real = this->Kd;
      *(outbuffer + offset + 0) = (u_Kd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Kd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Kd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Kd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Kd);
      union {
        double real;
        uint32_t base;
      } u_Ki;
      u_Ki.real = this->Ki;
      *(outbuffer + offset + 0) = (u_Ki.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Ki.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Ki.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Ki.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Ki);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        double real;
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
        double real;
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
        double real;
        uint32_t base;
      } u_Ki;
      u_Ki.base = 0;
      u_Ki.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Ki.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Ki.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Ki.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Ki = u_Ki.real;
      offset += sizeof(this->Ki);
     return offset;
    }

    const char * getType(){ return TUNING; };
    const char * getMD5(){ return "d83c434fd3f20c665855c125c1379b29"; };

  };

  class tuningResponse : public ros::Msg
  {
    public:
      typedef bool _response_type;
      _response_type response;
      typedef bool _obj_type;
      _obj_type obj;

    tuningResponse():
      response(0),
      obj(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_response;
      u_response.real = this->response;
      *(outbuffer + offset + 0) = (u_response.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->response);
      union {
        bool real;
        uint8_t base;
      } u_obj;
      u_obj.real = this->obj;
      *(outbuffer + offset + 0) = (u_obj.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->obj);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_response;
      u_response.base = 0;
      u_response.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->response = u_response.real;
      offset += sizeof(this->response);
      union {
        bool real;
        uint8_t base;
      } u_obj;
      u_obj.base = 0;
      u_obj.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->obj = u_obj.real;
      offset += sizeof(this->obj);
     return offset;
    }

    const char * getType(){ return TUNING; };
    const char * getMD5(){ return "0f4258a7aa9b5b7bd0a215d10c7773c8"; };

  };

  class tuning {
    public:
    typedef tuningRequest Request;
    typedef tuningResponse Response;
  };

}
#endif
