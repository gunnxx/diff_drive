# diff_drive
Differential Drive robot simulation using Gazebo.
Tested on `Ubuntu 18.04.4 LTS`, `ROS Melodic`, and `gazebo9`.

## How To (Quick Guide)
It is a ROS Package.
To use it, clone this inside `your_ros_workspace/src/` directory and then on `your_ros_workspace` directory, run `catkin_make`.
After that, just do `roslaunch diff_drive diff_drive.launch` to run the simulator.
Check available topics using `rostopic list`.
See **Environment Setup for Windows** below for a long-detailed guidance.

## Dependencies
- [`gazebo_ros_pkgs`](http://wiki.ros.org/gazebo_ros_pkgs) package

## Environment Setup for Windows
### 1. [Install Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/en-us/windows/wsl/install-win10)  
- Open PowerShell as Administrator and run  
`dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart`  
Note that `PowerShell != Command Prompt`. Just search for `PowerShell` on your computer.  
- Restart your computer.  
- Open Microsoft Store and search for 'Ubuntu'.  
In this case, I downloaded Ubuntu 18.04. Feel free to use other version, although 18.04 is recommended.  
- Launch WSL, do setup, and run `sudo apt-get update`, then `sudo apt-get upgrade`.  

### 2. [Install ROS](http://wiki.ros.org/melodic/Installation/Ubuntu)  
- **Launch WSL**  

- **Installation**  
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt update
sudo apt install ros-melodic-desktop-full
```  

- **Environment Setup**  
Open `.bashrc` using `nano` text editor by running `nano ~/.bashrc`.  
At the very bottom, add `source /opt/ros/melodic/setup.bash`.  
Quit `nano` by pressing `Ctrl + X` and hit `Y` to save the changes.  
Finally, run `source ~/.bashrc`.  

- **Dependencies for Building Packages**  
```
sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
sudo rosdep init
rosdep update
```  

- **Testing installation**  
Run `roscore`.  
If everything goes fine, the output at the very bottom should look similar to `started core service [/rosout]`.  

### 3. [Install VcXsrv](https://medium.com/fresnostatedx/ros-environment-setup-for-windows-without-virtualbox-8fc14faad59e)  
- **Installation**  
Download `VcXsrv` from [here](https://sourceforge.net/projects/vcxsrv/) and install.  

- **Usage**  
Everytime you use WSL that requires GUI (e.g. `gazebo`, `rqt_graph`), run `VcXsrv` as it is, except for the last part i.e. 'Extra settings' by unchecking 'Native opengl'.  

- **Environment setup**  
Launch WSL.  
Open `.bashrc` using `nano` text editor by running `nano ~/.bashrc`.  
At the very bottom, add `export DISPLAY=:0`.  
Quit `nano` by pressing `Ctrl + X` and hit `Y` to save the changes.  
Finally, run `source ~/.bashrc`.  

- **Testing installation**  
To test installation, run `rqt_graph` on WSL.  
A window should appear.  

### 4. [Install Gazebo](http://gazebosim.org/tutorials?cat=install&tut=install_ubuntu&ver=9.0)  
- **Launch WSL**  

- **Installation**  
```
sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
wget https://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
sudo apt-get update
sudo apt-get install gazebo9 libgazebo9-dev
sudo apt upgrade libignition-math2
```

- **Testing Installation**  
With VcXsrv on, run `gazebo` on WSL.  
Note that, if nothing happens, run `sudo -s` first (use root user). Then run `gazebo`.  

### 5. [Setup ROS Workspace](http://wiki.ros.org/melodic/Installation/Ubuntu)  
- **Launch WSL**  

- **Create ROS Workspace**  
Everything that is ROS-related should be inside ROS Workspace.  
To create ROS Workspace named `workspace` on `~/college` directory, run the following  
```
cd              # move to home directory (i.e. ~/ or equivalently /home/username/)
mkdir college   # create directory named college (check by running 'ls')
cd college      # move to college directory
mkdir workspace
cd workspace
mkdir src
catkin_make     # initialize workspace directory as ROS Workspace
```

- **Environment Setup**  
Now that ROS Workspace is setup.  
You can see `build` and `devel` directories inside `workspace` directory.  
Open `.bashrc` using `nano` text editor by running `nano ~/.bashrc`.  
At the very bottom, add `source /home/username/college/workspace/devel/setup.bash`.  
Change `username` with your username.  
Quit `nano` by pressing `Ctrl + X` and hit `Y` to save the changes.  
Finally, run `source ~/.bashrc`.  

### 6. Running The Simulation  
- **Cloning The Repository**  
Remember that ROS-related stuffs should be inside ROS Workspace.  
We already created ROS Workspace named `workspace` previously.  
Navigate to `src` directory inside `workspace` i.e. `cd ~/college/workspace/src`.  
Run `git clone https://github.com/gunnxx/diff_drive.git`.  
Move to `workspace` again i.e. `cd ..` (move to one outter (or parent) directory).  
Build `diff_drive` package by running `catkin_make`.  

- **Testing Installation**  
You can run the simulation by `roslaunch diff_drive diff_drive.launch`.  
Note that if you need `sudo -s` to run `gazebo`, you need to run `sudo -s` also to run the above `roslaunch`.  

## To Do
- [x] Test on Windows using WSL
- [x] Add Windows installation guide
- [ ] Add ROS (how to use) tutorials