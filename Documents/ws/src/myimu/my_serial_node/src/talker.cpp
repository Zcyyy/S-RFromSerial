#include "ros/ros.h"
#include "std_msgs/String.h"
//#include "std_msgs/UInt8.h"
#include <sstream>
int main(int argc, char **argv)
{
 ros::init(argc, argv, "talker");
 ros::NodeHandle n;
 //发布主题command
 ros::Publisher command_pub = n.advertise<std_msgs::String>("command", 1000);
 ros::Rate loop_rate(10);
 while (ros::ok())
 {
   std_msgs::String msg;
//   std_msgs::UInt8 mess;
   std::stringstream ss;
  //ss_data << "talker publish command " << count;
  // ss_data << "770400595d";
  // msg.data = ss_data.str();
   uint8_t ss_data[5];
   //ss_data = 0x770400595d;
   ss_data[0] = 0x77;
   ss_data[1] = 0x04;
   ss_data[2] = 0x00;
   ss_data[3] = 0x59;
   ss_data[4] = 0x5d;
   for(int i = 0; i<5; i++)
   {
	   ss << ss_data[i];
	   //msg.data = ss.str();
   	   //ROS_INFO("%02x", msg.data/*.c_str()*/);
	   //printf("data is: %s\n ",msg.data.c_str());
   	   //command_pub.publish(msg);
	  // ss.clear();
   }
   msg.data = ss.str();
   printf("data is:%s\n",msg.data.c_str());
   command_pub.publish(msg);
   ss.clear();
   ss.str("");
   msg.data.clear();
   ros::spinOnce();
   loop_rate.sleep();
  }
  return 0;
}
