#include "ros.h"
#include "auto_nav/ticks_msg.h"
#include "auto_nav/velocity_msg.h"
#include "rosserial_test.h"

ros::NodeHandle nh;

auto_nav::ticks_msg ticks;
auto_nav::velocity_msg velocity;
ros::Publisher espPub("ticks", &ticks);

void callback(const auto_nav::velocity_msg& msg){
  velocity.motor_L = msg.motor_L;
  velocity.motor_R = msg.motor_R;
}
ros::Subscriber<auto_nav::velocity_msg> espSub("teleop", &callback);

void rosserial_setup(){  // Initialize ROS
  nh.initNode();
  nh.advertise(espPub);
  nh.subscribe(espSub);
}

void rosserial_publish(long long unsigned int* ticks_L, long long unsigned int* ticks_R){
  ticks.motor_L = *ticks_L;
  ticks.motor_R = *ticks_R;
  espPub.publish(&ticks);  // publish the msg
}

void rosserial_subscribe(float* duty_L, float* duty_R){
  *duty_L = velocity.motor_L;
  *duty_R = velocity.motor_R;
  nh.spinOnce();
}

void rosserial_spinonce(){
  nh.spinOnce();
}
