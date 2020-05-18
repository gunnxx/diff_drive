# diff_drive
Differential Drive robot simulation using Gazebo.
Tested on `Ubuntu 18.04.4 LTS`, `ROS Melodic`, and `gazebo9`.

### How To
It is a ROS Package.
To use it, clone this inside `your_ros_workspace/src/` directory and then on `your_ros_workspace` directory, run `catkin_make`.
After that, just do `roslaunch diff_drive diff_drive.launch` to run the simulator.
Check available topics using `rostopic list`.

### Dependencies
- [`gazebo_ros_pkgs`](http://wiki.ros.org/gazebo_ros_pkgs) package

### To Do
- [ ] Test on Windows using WSL
- [ ] Add tutorials
