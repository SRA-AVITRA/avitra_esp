#ifndef _ROS_SERVICE_OctomapPaGetSize_h
#define _ROS_SERVICE_OctomapPaGetSize_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace octomap_pa
{

static const char OCTOMAPPAGETSIZE[] = "octomap_pa/OctomapPaGetSize";

  class OctomapPaGetSizeRequest : public ros::Msg
  {
    public:

    OctomapPaGetSizeRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return OCTOMAPPAGETSIZE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class OctomapPaGetSizeResponse : public ros::Msg
  {
    public:
      typedef int32_t _size_type;
      _size_type size;
      typedef int64_t _memoryusage_type;
      _memoryusage_type memoryusage;
      typedef int32_t _count_cloud_type;
      _count_cloud_type count_cloud;
      typedef int32_t _count_cloud_old_type;
      _count_cloud_old_type count_cloud_old;
      typedef int32_t _count_laser_type;
      _count_laser_type count_laser;

    OctomapPaGetSizeResponse():
      size(0),
      memoryusage(0),
      count_cloud(0),
      count_cloud_old(0),
      count_laser(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_size;
      u_size.real = this->size;
      *(outbuffer + offset + 0) = (u_size.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_size.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_size.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_size.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->size);
      union {
        int64_t real;
        uint64_t base;
      } u_memoryusage;
      u_memoryusage.real = this->memoryusage;
      *(outbuffer + offset + 0) = (u_memoryusage.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_memoryusage.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_memoryusage.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_memoryusage.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_memoryusage.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_memoryusage.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_memoryusage.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_memoryusage.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->memoryusage);
      union {
        int32_t real;
        uint32_t base;
      } u_count_cloud;
      u_count_cloud.real = this->count_cloud;
      *(outbuffer + offset + 0) = (u_count_cloud.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_count_cloud.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_count_cloud.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_count_cloud.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->count_cloud);
      union {
        int32_t real;
        uint32_t base;
      } u_count_cloud_old;
      u_count_cloud_old.real = this->count_cloud_old;
      *(outbuffer + offset + 0) = (u_count_cloud_old.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_count_cloud_old.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_count_cloud_old.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_count_cloud_old.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->count_cloud_old);
      union {
        int32_t real;
        uint32_t base;
      } u_count_laser;
      u_count_laser.real = this->count_laser;
      *(outbuffer + offset + 0) = (u_count_laser.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_count_laser.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_count_laser.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_count_laser.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->count_laser);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_size;
      u_size.base = 0;
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->size = u_size.real;
      offset += sizeof(this->size);
      union {
        int64_t real;
        uint64_t base;
      } u_memoryusage;
      u_memoryusage.base = 0;
      u_memoryusage.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_memoryusage.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_memoryusage.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_memoryusage.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_memoryusage.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_memoryusage.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_memoryusage.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_memoryusage.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->memoryusage = u_memoryusage.real;
      offset += sizeof(this->memoryusage);
      union {
        int32_t real;
        uint32_t base;
      } u_count_cloud;
      u_count_cloud.base = 0;
      u_count_cloud.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_count_cloud.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_count_cloud.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_count_cloud.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->count_cloud = u_count_cloud.real;
      offset += sizeof(this->count_cloud);
      union {
        int32_t real;
        uint32_t base;
      } u_count_cloud_old;
      u_count_cloud_old.base = 0;
      u_count_cloud_old.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_count_cloud_old.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_count_cloud_old.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_count_cloud_old.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->count_cloud_old = u_count_cloud_old.real;
      offset += sizeof(this->count_cloud_old);
      union {
        int32_t real;
        uint32_t base;
      } u_count_laser;
      u_count_laser.base = 0;
      u_count_laser.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_count_laser.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_count_laser.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_count_laser.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->count_laser = u_count_laser.real;
      offset += sizeof(this->count_laser);
     return offset;
    }

    const char * getType(){ return OCTOMAPPAGETSIZE; };
    const char * getMD5(){ return "ea0be6a58e7e49697448514d237b5c26"; };

  };

  class OctomapPaGetSize {
    public:
    typedef OctomapPaGetSizeRequest Request;
    typedef OctomapPaGetSizeResponse Response;
  };

}
#endif
