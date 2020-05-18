cmake_minimum_required(VERSION 3.0.2)
project(diff_drive)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  gazebo_ros
  roslaunch
)

# Find gazebo
find_package(gazebo REQUIRED)

IF(gazebo_FOUND)
  MESSAGE("Gazebo found. Include dir at ${GAZEBO_LIBRARY_DIRS}")
ENDIF(gazebo_FOUND)

## Check all *.launch files in launch directory
roslaunch_add_file_check(launch)

catkin_package(
  DEPENDS
    roscpp
    sensor_msgs
    gazebo_ros
)

include_directories(
  include
  ${GAZEBO_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

link_directories(
  ${GAZEBO_LIBRARY_DIRS}
)

add_library(gazebo_ros_sonar SHARED plugins/gazebo_ros_sonar.cpp)
target_link_libraries(gazebo_ros_sonar ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} SonarPlugin)