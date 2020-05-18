#ifndef GAZEBO_ROS_SONAR_HH
#define GAZEBO_ROS_SONAR_HH

#include <ros/ros.h>
#include <sensor_msgs/Range.h>

#include <gazebo/plugins/SonarPlugin.hh>
#include <gazebo_plugins/gazebo_ros_utils.h>

namespace gazebo{
    class GazeboRosSonar : public SonarPlugin
    {
        /// \brief Constructor
        public: GazeboRosSonar();

        /// \brief Destructor
        public: ~GazeboRosSonar();

        /// \brief Load the plugin
        /// \param[in] _parent Pointer to the parent sensor
        /// \param[in] _sdf SDF root element for the plugin
        public: void Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf);

        /// \brief Pointer to ros node
        private: ros::NodeHandle* rosnode_;
        private: ros::Publisher rospub_;
        private: sensor_msgs::Range sonar_msg_;

        /// \brief Topic name
        private: std::string topic_name_;

        /// \brief Frame transform name, should match link name
        private: std::string frame_name_;

        /// \brief ROS name space
        private: std::string robot_namespace_;

        /// \brief Update callback
        /// \param[in] _msg The sonar ping message
        private: void OnUpdate(msgs::SonarStamped _msg);

        /// \brief Sensor spec
        private: unsigned int seed_;
        private: double gaussian_noise_;
        private: double bias_;

        /// \brief Gaussian noise generator
        private: double GaussianKernel(double mu, double sigma);
    };
}
#endif