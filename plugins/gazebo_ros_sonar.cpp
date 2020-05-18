#include <plugins/gazebo_ros_sonar.h>

namespace gazebo
{
// Register this plugin with the simulator
GZ_REGISTER_SENSOR_PLUGIN(GazeboRosSonar);

// Constructor
GazeboRosSonar::GazeboRosSonar()
{
    this->seed_ = 0;
}

// Destructor
GazeboRosSonar::~GazeboRosSonar(){
    this->rosnode_->shutdown();
    delete this->rosnode_;
}

// Loading model
void GazeboRosSonar::Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf)
{
    // load plugin
    SonarPlugin::Load(_parent, _sdf);


    this->robot_namespace_ = GetRobotNamespace(_parent, _sdf, "Sonar");

    if(!_sdf->HasElement("frameName"))
    {
        ROS_INFO_NAMED("sonar", "Sonar plugin missing <frameName>, defaults to /world");
        this->frame_name_ = "/world";
    }
    else
        this->frame_name_ = _sdf->Get<std::string>("frameName");


    if(!_sdf->HasElement("topicName"))
    {
        ROS_INFO_STREAM_NAMED("sonar", "Sonar plugin missing <topicName>, defaults to " << this->robot_namespace_ << "/sonar");
        this->topic_name_ = this->robot_namespace_ + "/sonar";
    }
    else
        this->topic_name_ = _sdf->Get<std::string>("topicName");


    if(!_sdf->HasElement("gaussianNoise"))
    {
        ROS_INFO_NAMED("sonar", "Sonar pluggin missing <gaussianNoise>, defaults to noise-free");
        this->gaussian_noise_ = 0.;
    }
    else
        this->gaussian_noise_ = _sdf->Get<double>("gaussianNoise");


    if(!_sdf->HasElement("bias"))
    {
        ROS_INFO_NAMED("sonar", "Sonar pluggin missing <bias>, defaults to bias-free");
        this->bias_ = 0.;
    }
    else
        this->bias_ = _sdf->Get<double>("bias");

    
    // Make sure the ROS node for Gazebo has already been initialized
    if(!ros::isInitialized())
    {
        ROS_FATAL_STREAM_NAMED("sonar", "A ROS node for Gazebo has not been initialized, unable to load plugin. "
            << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
        return;
    }

    ROS_INFO_NAMED("sonar", "Starting Sonar Plugin (ns = %s)", this->robot_namespace_.c_str());

    this->rosnode_ = new ros::NodeHandle(this->robot_namespace_);
    this->rospub_ = this->rosnode_->advertise<sensor_msgs::Range>(this->topic_name_, 1);

    // this->parentSensor comes from parent
    this->parentSensor->SetActive(true);
}

// Update callback
void GazeboRosSonar::OnUpdate(msgs::SonarStamped _msg)
{
    if(this->rospub_.getNumSubscribers() > 0)
    {
        this->sonar_msg_.header.frame_id = this->frame_name_;
        this->sonar_msg_.header.stamp.sec = _msg.time().sec();
        this->sonar_msg_.header.stamp.nsec = _msg.time().nsec();

        this->sonar_msg_.min_range = _msg.sonar().range_min();
        this->sonar_msg_.max_range = _msg.sonar().range_max();
        this->sonar_msg_.range = _msg.sonar().range() 
            + this->GaussianKernel(this->bias_, this->gaussian_noise_);
        
        this->rospub_.publish(this->sonar_msg_);
    }
}

// Utility for adding noise
double GazeboRosSonar::GaussianKernel(double mu, double sigma)
{
    double U = static_cast<double>(rand_r(&this->seed_)) /
        static_cast<double>(RAND_MAX);

    double V = static_cast<double>(rand_r(&this->seed_)) /
        static_cast<double>(RAND_MAX);
    
    double X = sqrt(-2.0 * log(U)) * cos(2.0*M_PI * V);
    X = sigma * X + mu;
    return X;
}
}