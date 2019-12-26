#include "ros.h"
#include "rosserial.h"
#include "auto_nav/tuning_msg.h"
#include "auto_nav/velocity_msg.h"

ros::NodeHandle nh;

auto_nav::velocity_msg velocity;
auto_nav::velocity_msg rpm;
ros::Publisher espPub("rpm", &rpm);

void callback(const auto_nav::velocity_msg& msg){

  velocity.motor_L = msg.motor_L;
  velocity.motor_R = msg.motor_R;

}
ros::Subscriber<auto_nav::velocity_msg> espSub("velocity", &callback);

void rosserial_setup(){  // Initialize ROS
  nh.initNode();
  nh.advertise(espPub);
  nh.subscribe(espSub);

 }

void rosserial_publish(encoder_t* encoder_L, encoder_t* encoder_R){
  rpm.motor_L = encoder_L->curr_rpm;
  rpm.motor_R = encoder_R->curr_rpm;
  espPub.publish(&rpm);  // publish the msg
}

void rosserial_subscribe(motor_t* motor_L, motor_t* motor_R){

  motor_L->duty_cycle = velocity.motor_L;
  motor_R->duty_cycle = velocity.motor_R;
  nh.spinOnce();
}

void rosserial_spinonce(){
  nh.spinOnce();
}
