#include "ros.h"
#include "rosserial.h"
#include "std_msgs/Float32.h"

ros::NodeHandle nh;

std_msgs::Float32 yaw;
ros::Publisher espPub("yaw", &yaw);


void rosserial_setup(){  // Initialize ROS
  nh.initNode();
  nh.advertise(espPub);
  yaw.data=0;
}

void rosserial_publish(float* op){
  yaw.data=*op;
  espPub.publish(&yaw);  // publish the msg
}

void rosserial_spinonce(){
  nh.spinOnce();
}
