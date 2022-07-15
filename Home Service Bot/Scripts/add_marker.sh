#!/bin/sh
path = '/home/workspace/catkin_ws/src'
xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch" &

sleep 5

xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${path}/map/map.yaml" &

sleep 5

xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 5

xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && rosrun add_markers add_markers" 