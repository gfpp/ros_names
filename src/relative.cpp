#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Byte.h>

const int DEFAULT_VAR = 10;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "relative");
  ros::NodeHandle nh;

  ROS_INFO("Testing relative names.");

  ros::Publisher pub_bool = nh.advertise<std_msgs::Bool>("bool", 1);
  ros::Publisher pub_byte = nh.advertise<std_msgs::Byte>("bytes/byte0", 1);

  int var;
  nh.param<int>("var", var, DEFAULT_VAR);
  nh.setParam("var", var);
  ROS_INFO_STREAM("Parameter: 'var'. Default: "<< DEFAULT_VAR
      << " - current: " << var);

  std_msgs::Bool b;
  b.data = true;
  std_msgs::Byte b0;
  b0.data = 0x00;
  ros::Rate loop_rate(1);
  while(ros::ok())
  {
    pub_bool.publish(b);
    pub_byte.publish(b0);

    nh.getParam("var", var);
    ROS_INFO_STREAM("Parameter 'var': " << var);

    b.data = !b.data;
    loop_rate.sleep();
  }
  return 0;
}

