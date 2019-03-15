#include "ros/ros.h"
#include "std_msgs/String.h"
#include "mini_multi_agent/task_srv.h"
#include "mini_multi_agent/rob_status.h"

struct ROBOT {
	int id ;
	std::string status;
};

ROBOT rob1 = {1,""};
ROBOT rob2 = {2,""};
class TaskDespatcher {
public:
	TaskDespatcher();
	~TaskDespatcher();
	bool task1_processer(int seq);
	bool task2_processer(int seq);
	void messageCallback(const mini_multi_agent::rob_status::ConstPtr& msg);
private:
	ros::NodeHandle nh;
	ros::Subscriber listener;
	ros::ServiceClient client1;
	ros::ServiceClient client2;

};
TaskDespatcher::TaskDespatcher() {
	listener = nh.subscribe("agent_feedback", 10,
			&TaskDespatcher::messageCallback, this);
	client1 = nh.serviceClient<mini_multi_agent::task_srv>("agent_task_1");
	client2 = nh.serviceClient<mini_multi_agent::task_srv>("agent_task_2");
}
TaskDespatcher::~TaskDespatcher() {

}

void TaskDespatcher::messageCallback(
		const mini_multi_agent::rob_status::ConstPtr& msg) {
	if(msg->robot_id == 1){
		rob1.status = msg->status;
	}else{
		rob2.status = msg->status;
	}
//	ROS_INFO("robot[%d] : [%s]", msg->robot_id, msg->status.c_str());
}

bool TaskDespatcher::task1_processer(int seq) {
	mini_multi_agent::task_srv srv1;
	srv1.request.seq = seq;
	if (client1.call(srv1)) {
//		ROS_INFO("status: %s", srv1.response.status.c_str());
	} else {
		ROS_ERROR("SORRY , robot 1 task id [%d] FAILED!",seq);
		return false;
	}
	return true;

}

bool TaskDespatcher::task2_processer(int seq) {
	mini_multi_agent::task_srv srv1;
	srv1.request.seq = seq;
	if (client2.call(srv1)) {
//		ROS_INFO("status: %s", srv1.response.status.c_str());
	} else {
		ROS_ERROR("SORRY , robot 2 task id [%d] FAILED!",seq);
		return false;
	}
	return true;

}


int main(int argc, char **argv) {
	ros::init(argc, argv, "node_mini_factory_server");
	TaskDespatcher td;
	ros::Rate loop_rate(10);
	int limit_rob1 =0;   // make task servers in "ready" status and keep it 5 seconds
	int count_rob1 =0;
	int count_rob2 =0;
	int limit_rob2 =0;
	while ( ros::ok() && (limit_rob1 <=6 || limit_rob2<=6) ) {
		count_rob1 ++;
		count_rob2 ++;
		if(count_rob1 >50 && limit_rob1<=6){
			if(limit_rob1>1){
				ROS_INFO("Robot 1 - task id : [%d] DONE !" , limit_rob1-1 );
			}
			if(limit_rob1<=5 && rob1.status=="ready"){
				td.task1_processer(limit_rob1 );
			}
			limit_rob1++;
			count_rob1 = 0;
		}
		if(count_rob2 >30 && limit_rob2<=6 ){
			if(limit_rob2>1){
				ROS_INFO("Robot 2 - task id : [%d] DONE !" , limit_rob2-1 );
			}
			if(limit_rob2<=5 && rob2.status=="ready"){
				td.task2_processer(limit_rob2);
			}
			limit_rob2++;
			count_rob2 = 0;
		}
		loop_rate.sleep();
		ros::spinOnce();
	}
	ROS_INFO("Well Down ,robots! all tasks finised. ");
	ros::shutdown();

	return 0;
}
