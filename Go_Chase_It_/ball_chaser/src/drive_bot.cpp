#include"ros/ros.h"
#include"ball_chaser/DriveToTarget.h"
#include<std_msgs/Float64.h>
#include<geometry_msgs/Twist.h>

ros::Publisher motor_command_publisher;



bool handle_drive_request(ball_chaser::DriveToTarget::Request& res, ball_chaser::DriveToTarget::Response& req)
{
	geometry_msgs::Twist motor_command;
	
	motor_command.linear.x = res.linear_x;
	motor_command.angular.z = res.angular_z;
	
	motor_command_publisher.publish(motor_command);
	
	//Returning a feedback message
	req.msg_feedback = "Velocities set - linear_x: " + std::to_string(res.linear_x) + ", angular_z " + std::to_string(res.angular_z);
	ROS_INFO_STREAM(req.msg_feedback);
	return true;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "drive_bot");
	ros::NodeHandle nh;
	
	motor_command_publisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
	
	ros::ServiceServer service = nh.advertiseService("/ball_chaser/command_robot", handle_drive_request);

	ros::spin();
	
	return 0;
}
