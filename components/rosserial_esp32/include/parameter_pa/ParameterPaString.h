#ifndef _ROS_SERVICE_ParameterPaString_h
#define _ROS_SERVICE_ParameterPaString_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace parameter_pa
{

static const char PARAMETERPASTRING[] = "parameter_pa/ParameterPaString";

  class ParameterPaStringRequest : public ros::Msg
  {
    public:
      typedef const char* _in_string_type;
      _in_string_type in_string;

    ParameterPaStringRequest():
      in_string("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_in_string = strlen(this->in_string);
      varToArr(outbuffer + offset, length_in_string);
      offset += 4;
      memcpy(outbuffer + offset, this->in_string, length_in_string);
      offset += length_in_string;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_in_string;
      arrToVar(length_in_string, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_in_string; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_in_string-1]=0;
      this->in_string = (char *)(inbuffer + offset-1);
      offset += length_in_string;
     return offset;
    }

    const char * getType(){ return PARAMETERPASTRING; };
    const char * getMD5(){ return "9ef22cc46b822f1370d23254a2ce6b89"; };

  };

  class ParameterPaStringResponse : public ros::Msg
  {
    public:
      typedef bool _ok_type;
      _ok_type ok;
      typedef const char* _out_string_type;
      _out_string_type out_string;

    ParameterPaStringResponse():
      ok(0),
      out_string("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ok;
      u_ok.real = this->ok;
      *(outbuffer + offset + 0) = (u_ok.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ok);
      uint32_t length_out_string = strlen(this->out_string);
      varToArr(outbuffer + offset, length_out_string);
      offset += 4;
      memcpy(outbuffer + offset, this->out_string, length_out_string);
      offset += length_out_string;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ok;
      u_ok.base = 0;
      u_ok.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ok = u_ok.real;
      offset += sizeof(this->ok);
      uint32_t length_out_string;
      arrToVar(length_out_string, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_out_string; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_out_string-1]=0;
      this->out_string = (char *)(inbuffer + offset-1);
      offset += length_out_string;
     return offset;
    }

    const char * getType(){ return PARAMETERPASTRING; };
    const char * getMD5(){ return "fef263ad9bcf75b3e4e7503e34492adc"; };

  };

  class ParameterPaString {
    public:
    typedef ParameterPaStringRequest Request;
    typedef ParameterPaStringResponse Response;
  };

}
#endif
