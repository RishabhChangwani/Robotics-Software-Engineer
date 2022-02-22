#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include<iostream>
using namespace std;
// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    
    // Call the command_robot service and pass the requested joint angles
    if (!client.call(srv))
    {
        ROS_ERROR("Failed to call service command_robot");
    }
}

void process_image_callback(const sensor_msgs::Image img)
{
    int ball = 255;
    int left = 0;
    int forward = 0;
    int right = 0;
	
    // TODO: 
    // Loop through each pixel in the image and check if there's a bright white one
    
    for (int i = 0; i < img.height * img.step; i += 3) {
        int j = i % (img.width * 3) / 3;
	
        if (img.data[i] == ball && img.data[i + 1] == ball && img.data[i + 2] == ball) 
        {
            if(j <= 265) {
		left += 1;                
            }
            if(j > 265 && j <= 533) {
		forward += 1;               
            }
            if(j > 533) {
		right += 1;                
            }
	}
	
   }
   vector<int> to_go{left, forward, right};
   int drive_to = *max_element(to_go.begin(), to_go.end());


    if (drive_to == 0)
    {
        drive_robot(0.0, 0.0); 
    }
    else if (drive_to == left) 
    {
	drive_robot(0.0, 0.5); 
    }
    else if (drive_to == forward) 
    {
        drive_robot(0.5, 0.0);  
    }
    else if (drive_to == right) 
    {
        drive_robot(0.0, -0.5); 
    }
}


int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
