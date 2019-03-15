How to use this package?

1, Environment : Utunbu16.04 , ROS kinetic version 
2, git clone https://github.com/longbowliu/mini_multi_agent.git into your catkin workspace . 
3, then , catkin_make your workspace, make sure that you already source your catkin_ws/buid/setup.bash or add it in the ~/.bashrc  
4, run the command "roslaunch mini_multi_agent mini_multi_agent.launch  " in the new terminal .
5, if you want to see the changing of  robots' status , you need run "roscore" and " rostopic info /agent_feedback " before step4 .

