#include "ros/ros.h"
#include "geometry_msgs/Point.h"
   #include <rosbag/bag.h>
    #include <std_msgs/Int32.h>
    #include <std_msgs/String.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "eyeInScreen");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

 
 // ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point>("/point", 10);

  ros::Rate loop_rate(10);
    rosbag::Bag bag;
    bag.open("test.bag", rosbag::bagmode::Write);
  int count = 0;

  while (ros::ok() && count<1000)
  {
    count++;
    std_msgs::String str;
    str.data = std::string("foo");

    std_msgs::Int32 i;
    i.data = count;
    bag.write("chatter", ros::Time::now(), str);
    bag.write("numbers", ros::Time::now(), i);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


    bag.close();
  return 0;
}
