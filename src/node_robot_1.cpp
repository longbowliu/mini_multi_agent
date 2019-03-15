#include "ros/ros.h"
#include "std_msgs/String.h"
#include "mini_multi_agent/task_srv.h"
#include "mini_multi_agent/rob_status.h"
using namespace std;

#define time_precision  0.1; // seconds



class Example {
public:
	Example(int seconds);
	~Example();
private:
	ros::NodeHandle nh;
	ros::ServiceClient client;
	ros::Subscriber listener;
	ros::Publisher pub;
	int time_counter_limit;
	int stas ;
	int time_counter;
    int seconds;
	std_msgs::String msg;
	std::stringstream ss;

	bool add(mini_multi_agent::task_srv::Request &req,
			mini_multi_agent::task_srv::Response &res);
	void time_callback(const ros::TimerEvent&);

};

bool Example::add(mini_multi_agent::task_srv::Request &req,
		mini_multi_agent::task_srv::Response &res) {

	if (req.seq==0){
		ROS_INFO("Robot 1 , just have a rest , we will going to work in 5 seconds . good luck!");
		return true;
	}
	stas = 1;
	if(stas==0)
		res.status = "ready";
	else
		res.status = "executing";

	ROS_INFO("Robot 1 - task id : [%d] comming , status change to [%s]" , req.seq, res.status.c_str());
	return true;
}

//implementation of construct function.
Example::Example(int seconds):seconds(seconds) {
	stas = 0;
	time_counter = 0;
	time_counter_limit = (int) seconds/time_precision;
	ros::ServiceServer service = nh.advertiseService("agent_task_1" ,&Example::add,this);
	ros::Timer  robot_timer = nh.createTimer(ros::Duration(0.1) ,&Example::time_callback,this);
	pub = nh.advertise<mini_multi_agent::rob_status>("agent_feedback", 5);
	ros::Rate loop_rate(10);
		while (ros::ok()) {
				loop_rate.sleep();
				ros::spinOnce();
			}
}
Example::~Example(){

}

//implementation of one of the Example class memeber.


void Example::time_callback(const ros::TimerEvent&)
{
	if(stas == 1){
		time_counter++;
		if(time_counter >= time_counter_limit){
			stas = 0;
			time_counter = 0;
		}
	}
	else{
		time_counter = 0;
	}

	mini_multi_agent::rob_status msg;
	msg.robot_id = 1;
	if(stas==0)
		msg.status = "ready";
	else
		msg.status = "executing";

	pub.publish(msg);
//	ROS_INFO("status : [%d]", stas);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "node_robot_1");
	Example exp(5);
	return 0;
}
