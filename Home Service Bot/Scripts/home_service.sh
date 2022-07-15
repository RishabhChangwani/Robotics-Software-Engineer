#!/bin/sh

#xterm -e "export TURTLEBOT_GAZEBO_WORLD_FILE=home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/worlds/playground.world" &
#xterm -e "export TURTLEBOT_GAZEBO_MAP_FILE=home/workspace/catkin_ws/src/map/map.yaml" &
path="/home/workspace/catkin_ws"

xterm -e "cd ${path} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(find turtlebot_gazebo)/worlds/playground.world" &

sleep 5

xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${path}/src/map/map.yaml" &

sleep 5

xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && roslaunch add_markers view_home_service_navigation.launch rviz_path:=/home/workspace/catkin_ws/src/rvizConfig/home_service_rvizConfig.rviz" &

sleep 5

xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && rosrun add_markers add_markers" &

xterm -e "cd /home/workspace/catkin_ws && source devel/setup.bash && rosrun pick_objects pick_objects" 