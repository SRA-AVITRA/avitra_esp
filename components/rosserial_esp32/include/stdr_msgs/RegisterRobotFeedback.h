#ifndef _ROS_stdr_msgs_RegisterRobotFeedback_h
#define _ROS_stdr_msgs_RegisterRobotFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace stdr_msgs
{

  class RegisterRobotFeedback : public ros::Msg
  {
    public:

    RegisterRobotFeedback()
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

    const char * getType(){ return "stdr_msgs/RegisterRobotFeedback"; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

}
#endif
