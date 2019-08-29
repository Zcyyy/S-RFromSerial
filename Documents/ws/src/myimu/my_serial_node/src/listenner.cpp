#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include <sstream>
//回调函数
/*void callback(const std_msgs::String::ConstPtr& msg)
{
 ROS_INFO("listener got: [%s]", msg->data.c_str());
}*/
void callback(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{
	std::stringstream ss_1;
	double angle[3]={0},acc[3]={0},angular_v[3]={0},q[4]={0};
	uint16_t Hex[msg->layout.data_offset];
	//ROS_INFO("listener got: %x",msg->data);
	if(msg->layout.data_offset == 48)
	{
		printf("Hex is:");
		for(int i=0; i<msg->layout.data_offset; i++)
             	{
			ss_1 << std::hex << (msg->data[i] & 0xff);
			ss_1 >> Hex[i];
			ss_1.str("");
			ss_1.clear();
			//printf("%x",Hex[i]);
             	}
		std::cout << std::endl;
	        if( Hex[4]/10 == 1 )
        	{
                	angle[0]=-((Hex[4]&0x0f)*100+(Hex[5]>>4)*10+(Hex[5]&0x0f)+(Hex[6]>>4)/10.0+(Hex[6]&0x0f)/100.0);
        	}
        	else
        	{
                	angle[0]=(Hex[4]&0x0f)*100+(Hex[5]>>4)*10+(Hex[5]&0x0f)+(Hex[6]>>4)/10.0+(Hex[6]&0x0f)/100.0;
        	}
        	//printf("angle[0] is:%f\n",angle[0]);
        	
		if( Hex[7]/10 == 1 )
        	{angle[1]=-((Hex[7]&0x0f)*100+(Hex[8]>>4)*10+(Hex[8]&0x0f)+(Hex[9]>>4)/10.0+(Hex[9]&0x0f)/100.0);}
        	else
        	{angle[1]=((Hex[7]&0x0f)*100+(Hex[8]>>4)*10+(Hex[8]&0x0f)+(Hex[9]>>4)/10.0+(Hex[9]&0x0f)/100.0);}
		
		if( Hex[10]/10 == 1 )
		{angle[2] =-((Hex[10]&0x0f)*100+(Hex[11]>>4)*10+(Hex[11]&0x0f)+(Hex[12]>>4)/10.0+(Hex[12]&0x0f)/100.0);}
		else
		{angle[2] =((Hex[10]&0x0f)*100+(Hex[11]>>4)*10+(Hex[11]&0x0f)+(Hex[12]>>4)/10.0+(Hex[12]&0x0f)/100.0);}
	
		if( Hex[13]/10 == 1 )
		{acc[0] =-((Hex[13]&0x0f)*100+(Hex[14]>>4)*10+(Hex[14]&0x0f)+(Hex[15]>>4)/10.0+(Hex[15]&0x0f)/100.0);}
		else
		{acc[0] =((Hex[13]&0x0f)*100+(Hex[14]>>4)*10+(Hex[14]&0x0f)+(Hex[15]>>4)/10.0+(Hex[15]&0x0f)/100.0);}

		if( Hex[16]/10 == 1 )
		{acc[1] =-((Hex[16]&0x0f)*100+(Hex[17]>>4)*10+(Hex[17]&0x0f)+(Hex[18]>>4)/10.0+(Hex[18]&0x0f)/100.0);}
		else
		{acc[1] =((Hex[16]&0x0f)*100+(Hex[17]>>4)*10+(Hex[17]&0x0f)+(Hex[18]>>4)/10.0+(Hex[18]&0x0f)/100.0);}
		
		if( Hex[19]/10 == 1 )
                {acc[2] =-((Hex[19]&0x0f)*100+(Hex[20]>>4)*10+(Hex[20]&0x0f)+(Hex[21]>>4)/10.0+(Hex[21]&0x0f)/100.0);}
                else
                {acc[2] =((Hex[19]&0x0f)*100+(Hex[20]>>4)*10+(Hex[20]&0x0f)+(Hex[21]>>4)/10.0+(Hex[21]&0x0f)/100.0);}	
	
		if( Hex[22]/10 == 1 )
                {angular_v[0] =-((Hex[22]&0x0f)*100+(Hex[23]>>4)*10+(Hex[23]&0x0f)+(Hex[24]>>4)/10.0+(Hex[24]&0x0f)/100.0);}
                else
                {angular_v[0] =((Hex[22]&0x0f)*100+(Hex[23]>>4)*10+(Hex[23]&0x0f)+(Hex[24]>>4)/10.0+(Hex[24]&0x0f)/100.0);}
	
		if( Hex[25]/10 == 1 )
                {angular_v[1] =-((Hex[25]&0x0f)*100+(Hex[26]>>4)*10+(Hex[26]&0x0f)+(Hex[27]>>4)/10.0+(Hex[27]&0x0f)/100.0);}
                else
                {angular_v[1] =((Hex[25]&0x0f)*100+(Hex[26]>>4)*10+(Hex[26]&0x0f)+(Hex[27]>>4)/10.0+(Hex[27]&0x0f)/100.0);}

		if( Hex[28]/10 == 1 )
                {angular_v[2] =-((Hex[28]&0x0f)*100+(Hex[29]>>4)*10+(Hex[29]&0x0f)+(Hex[30]>>4)/10.0+(Hex[30]&0x0f)/100.0);}
                else
                {angular_v[2] =((Hex[28]&0x0f)*100+(Hex[29]>>4)*10+(Hex[29]&0x0f)+(Hex[30]>>4)/10.0+(Hex[30]&0x0f)/100.0);}

		if( Hex[31]/10 == 1 )
		{q[0]=-((Hex[31]&0x0f)+(Hex[32]>>4)/10.0+(Hex[32]&0x0f)/100.0+(Hex[33]>>4)/1000.0+(Hex[33]&0x0f)/10000.0+(Hex[34]>>4)/100000.0+(Hex[34]&0x0f)/1000000.0);}
		else
		{q[0]=((Hex[31]&0x0f)+(Hex[32]>>4)/10.0+(Hex[32]&0x0f)/100.0+(Hex[33]>>4)/1000.0+(Hex[33]&0x0f)/10000.0+(Hex[34]>>4)/100000.0+(Hex[34]&0x0f)/1000000.0);}
	
		if( Hex[35]/10 == 1 )
                {q[1]=-((Hex[35]&0x0f)+(Hex[36]>>4)/10.0+(Hex[36]&0x0f)/100.0+(Hex[37]>>4)/1000.0+(Hex[37]&0x0f)/10000.0+(Hex[38]>>4)/100000.0+(Hex[38]&0x0f)/1000000.0);}
                else
                {q[1]=((Hex[35]&0x0f)+(Hex[36]>>4)/10.0+(Hex[36]&0x0f)/100.0+(Hex[37]>>4)/1000.0+(Hex[37]&0x0f)/10000.0+(Hex[38]>>4)/100000.0+(Hex[38]&0x0f)/1000000.0);}

		if( Hex[39]/10 == 1 )
                {q[2]=-((Hex[39]&0x0f)+(Hex[40]>>4)/10.0+(Hex[40]&0x0f)/100.0+(Hex[41]>>4)/1000.0+(Hex[41]&0x0f)/10000.0+(Hex[42]>>4)/100000.0+(Hex[42]&0x0f)/1000000.0);}
                else
                {q[2]=((Hex[39]&0x0f)+(Hex[40]>>4)/10.0+(Hex[40]&0x0f)/100.0+(Hex[41]>>4)/1000.0+(Hex[41]&0x0f)/10000.0+(Hex[42]>>4)/100000.0+(Hex[42]&0x0f)/1000000.0);}

		if( Hex[43]/10 == 1 )
                {q[3]=-((Hex[43]&0x0f)+(Hex[44]>>4)/10.0+(Hex[44]&0x0f)/100.0+(Hex[45]>>4)/1000.0+(Hex[45]&0x0f)/10000.0+(Hex[46]>>4)/100000.0+(Hex[46]&0x0f)/1000000.0);}
                else
                {q[3]=((Hex[43]&0x0f)+(Hex[44]>>4)/10.0+(Hex[44]&0x0f)/100.0+(Hex[45]>>4)/1000.0+(Hex[45]&0x0f)/10000.0+(Hex[46]>>4)/100000.0+(Hex[46]&0x0f)/1000000.0);}
	printf(" angle[0] is:%f\n angle[1] is:%f\n angle[2] is:%f\n",angle[0],angle[1],angle[2]);
	printf(" acc[0] is:%f\n acc[1] is:%f\n acc[2] is:%f\n",acc[0],acc[1],acc[2]);
	printf(" angular[0] is:%f\n angular[1] is:%f\n angular_v[2] is:%f\n",angular_v[0],angular_v[1],angular_v[2]);
	printf(" q[0] is:%f\n q[1] is:%f\n q[2] is:%f\n q[3] is:%f\n",q[0],q[1],q[2],q[3]);
	printf("===================================================================================\n");
	}
}

int main(int argc, char **argv)
{
 ros::init(argc, argv, "listener");
 ros::NodeHandle n;
 //订阅主题
 ros::Subscriber sub = n.subscribe("talker", 1000, callback);
 ros::spin();
 return 0;
}
