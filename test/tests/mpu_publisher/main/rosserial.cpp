#include "ros.h"
#include "rosserial.h"
#include "std_msgs/Float32.h"

ros::NodeHandle nh;

std_msgs::Float32 angle;
ros::Publisher espPub("yaw", &angle);

void rosserial_setup(){  // Initialize ROS
  nh.initNode();
  nh.advertise(espPub);
  angle.data = 0;
}

void rosserial_publish(float* op){
  angle.data = *op;
  espPub.publish(&angle);  // publish the msg
  nh.spinOnce();
}
