cmake_minimum_required(VERSION 2.8.3)
project(mini_multi_agent)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
# dynamic_reconfigure
)

#generate_dynamic_reconfigure_options(
#  cfg/chapter2.cfg
#)





## Generate messages in the 'msg' folder
add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
	FILES
	rob_status.msg
)

## Generate services in the 'srv' folder
add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
	FILES
	task_srv.srv
)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES chapter2_tutorials
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(chapter2_tutorials
#   src/${PROJECT_NAME}/chapter2_tutorials.cpp
# )

## Declare a cpp executable
# add_executable(chapter2_tutorials_node src/chapter2_tutorials_node.cpp)
add_executable(node_mini_factory_server src/node_mini_factory_server.cpp)
add_executable(node_robot_1 src/node_robot_1.cpp)
add_executable(node_robot_2 src/node_robot_2.cpp)


## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(chapter2_tutorials_node chapter2_tutorials_generate_messages_cpp)

add_dependencies(node_mini_factory_server mini_multi_agent_generate_messages_cpp)
add_dependencies(node_robot_1 mini_multi_agent_generate_messages_cpp)
add_dependencies(node_robot_2 mini_multi_agent_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(chapter2_tutorials_node
#   ${catkin_LIBRARIES}
# )


target_link_libraries(node_mini_factory_server ${catkin_LIBRARIES})
target_link_libraries(node_robot_1 ${catkin_LIBRARIES})
target_link_libraries(node_robot_2 ${catkin_LIBRARIES})

