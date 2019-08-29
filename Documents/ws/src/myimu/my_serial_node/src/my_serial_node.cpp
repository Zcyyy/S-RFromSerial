#include <ros/ros.h>
#include <std_msgs/UInt8MultiArray.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <sstream>
#include <string.h>
serial::Serial ros_ser;
//回调函数
void callback(const std_msgs::String::ConstPtr& msg){
     ROS_INFO_STREAM("Write to serial port" << msg->data);
     ros_ser.write(msg->data);
}
int main (int argc, char** argv){
     size_t p;
     ros::init(argc, argv, "my_serial_node");
     ros::NodeHandle n;
     //订阅主题command
     ros::Subscriber command_sub = n.subscribe("command", 1000, callback);
     //发布主题sensor
     ros::Publisher sensor_pub = n.advertise<std_msgs::UInt8MultiArray>("talker", 1000);
     try
     {
         ros_ser.setPort("/dev/ttyUSB0");
         ros_ser.setBaudrate(9600);
         serial::Timeout to = serial::Timeout::simpleTimeout(1000);
         ros_ser.setTimeout(to);
         ros_ser.open();
     }
     catch (serial::IOException& e)
     {
         ROS_ERROR_STREAM("Unable to open port ");
         return -1;
     }
     if(ros_ser.isOpen()){
         ROS_INFO_STREAM("Serial Port opened");
     }else{
         return -1;
     }
     ros::Rate loop_rate(10);
     std::stringstream ss;
     while(ros::ok()){
         ros::spinOnce();
         if(ros_ser.available()){
             ROS_INFO_STREAM("Reading from serial port");
             /*std_msgs::String serial_data;
             //获取串
	     serial_data.data = ros_ser.read(ros_ser.available());
	     ROS_INFO_STREAM("read data:" << serial_data);
	     sensor_pub.publish(serial_data);
		*/
		
	     p = ros_ser.available();
	     std_msgs::UInt8MultiArray buffer;
	     p = ros_ser.read(buffer.data, p);
	     buffer.layout.data_offset = p;
	     /*for(int i=0; i<p; i++)
	     {
		std::cout.width(2);
		std::cout.fill('0');
	     	std::cout << std::hex << (buffer.data[i] & 0xff);
		if( (buffer[i] & 0xff) == 0 )
		{
			ss << std::hex << 0;
                        ss << std::hex << 0;

		}
		else if( (buffer.data[i] & 0xff) <= 9)
		{
			ss << std::hex << 0;
			ss << std::hex << (buffer.data[i] & 0xff);
		}
		else
		{
			ss << std::hex << (buffer.data[i] & 0xff);
		}
	     }
	     std::cout << std::endl;
	     std::cout << ss.str() << std::endl;
	     for(int i=0; i<p; i++)
	     {
	     	sensor_pub.publish(buffer[i]);
	     }
	     ss.str("");
	     ss.clear();*/
	     sensor_pub.publish(buffer);
	     //for(int i=0; i<p; i++)
	     //{
	//	     buffer[i] = '0';
	     
	     //}
	 }
         loop_rate.sleep();
     }
 }
