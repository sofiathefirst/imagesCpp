#include "ros/ros.h"
#include "geometry_msgs/Point.h"
   #include <rosbag/bag.h>
    #include <rosbag/view.h>
    #include <std_msgs/Int32.h>
    #include <sensor_msgs/Image.h>
    #include <sensor_msgs/Imu.h>
    #include <boost/foreach.hpp>
    #define foreach BOOST_FOREACH
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>                       //zliu7
#include <opencv2/video/background_segm.hpp>           //zliu7

  using namespace cv;
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

 
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point>("/point", 10);

  ros::Rate loop_rate(10);

  int count = 0;

 rosbag::Bag bag;
    bag.open("/home/a/rov2.bag", rosbag::bagmode::Read);

    std::vector<std::string> topics;
    topics.push_back(std::string("/camera/image_raw"));
    topics.push_back(std::string("/mavros/imu/data"));

    rosbag::View view(bag, rosbag::TopicQuery(topics));
   foreach(rosbag::MessageInstance const m, view)
    {
        sensor_msgs::Image::ConstPtr s = m.instantiate<sensor_msgs::Image>();

if (s != NULL)
{
   cv_bridge::CvImagePtr cv_ptr;									   
    try
    {
      cv_ptr = cv_bridge::toCvCopy(s, sensor_msgs::image_encodings::TYPE_8UC3);   
			//convert ROS image to CV image and make copy of it storing in cv_ptr(a pointer)
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }

    cv::imshow("wim", cv_ptr->image);
    cv::waitKey(3);
}
        sensor_msgs::Imu::ConstPtr i = m.instantiate<sensor_msgs::Imu>();
        if (i != NULL)
           {
		 std::cout << i->header.seq  << std::endl;
		 std::cout << i->angular_velocity.y  << std::endl;
		 std::cout << i->angular_velocity.z  << std::endl;
		}
    }

    bag.close();
 

  return 0;
}
