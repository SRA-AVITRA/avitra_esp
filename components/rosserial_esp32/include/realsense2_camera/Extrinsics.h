#ifndef _ROS_realsense2_camera_Extrinsics_h
#define _ROS_realsense2_camera_Extrinsics_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace realsense2_camera
{

  class Extrinsics : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      double rotation[9];
      double translation[3];

    Extrinsics():
      header(),
      rotation(),
      translation()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 9; i++){
      union {
        double real;
        uint32_t base;
      } u_rotationi;
      u_rotationi.real = this->rotation[i];
      *(outbuffer + offset + 0) = (u_rotationi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rotationi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rotationi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rotationi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rotation[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        double real;
        uint32_t base;
      } u_translationi;
      u_translationi.real = this->translation[i];
      *(outbuffer + offset + 0) = (u_translationi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_translationi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_translationi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_translationi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->translation[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 9; i++){
      union {
        double real;
        uint32_t base;
      } u_rotationi;
      u_rotationi.base = 0;
      u_rotationi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rotationi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rotationi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rotationi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rotation[i] = u_rotationi.real;
      offset += sizeof(this->rotation[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        double real;
        uint32_t base;
      } u_translationi;
      u_translationi.base = 0;
      u_translationi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_translationi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_translationi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_translationi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->translation[i] = u_translationi.real;
      offset += sizeof(this->translation[i]);
      }
     return offset;
    }

    const char * getType(){ return "realsense2_camera/Extrinsics"; };
    const char * getMD5(){ return "3627b43073f4cd5dd6dc179a49eda2ad"; };

  };

}
#endif
