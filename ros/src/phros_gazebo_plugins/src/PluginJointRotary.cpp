#include "PluginJointRotary.h"

namespace gazebo
{

PluginJointRotary::PluginJointRotary() {}

PluginJointRotary::~PluginJointRotary(void)
{

  _threadCommunication.join();
}

void PluginJointRotary::Load(physics::ModelPtr model, sdf::ElementPtr sdf)
{
  // Just output a message for now
  std::cout << "\nRotary joint plugin is attached to [" << model->GetName() << "]\n";
  if(model->GetJointCount() == 0)
  {
    std::cout << "Model contains no joints, malformed sdf\n";
    return;
  }
  _model = model;
  _sdf   = sdf;

  std::string jointName;
  if(!sdf->HasElement("joint_name"))
  {
    std::cout << __PRETTY_FUNCTION__ << "Sdf does not contain the joint name, using first one" << std::endl;
    // jointName = "/world";
  }
  else
    jointName = _sdf->Get<std::string>("joint_name");
  std::string topicGazeboName;
  if(!sdf->HasElement("topic_gazebo_name"))
  {
    std::cout << __PRETTY_FUNCTION__ << "Sdf does not contain the topic gazebo name, using jointName/angle" << std::endl;
    // jointName = "/world";
  }
  else
    topicGazeboName = _sdf->Get<std::string>("topic_gazebo_name");
  std::cout << __PRETTY_FUNCTION__ << " will send on the gazebo topic " << topicGazeboName << std::endl;

  double velocity = 0.0;
  if(!sdf->HasElement("velocity"))
  {
    std::cout << __PRETTY_FUNCTION__ << "Sdf does not contain the desired velocity, setting 5" << std::endl;
    // jointName = "/world";
  }
  else
    velocity = _sdf->Get<double>("velocity");

  bool flagFound = false; // toDO: maybe we dont need this..just check the joint smart pointer for nullptr
  for(auto& iter : model->GetJoints())
  {
    std::cout << __PRETTY_FUNCTION__ << " joint " << iter->GetScopedName() << std::endl;
    if(iter->GetScopedName() == jointName)
    {
      _joint    = iter;
      flagFound = true;
      break;
    }
  }
  if(!flagFound)
  {
    std::cout << __PRETTY_FUNCTION__ << " error. Joint " << jointName << " not found. Using first" << std::endl;
    _joint = model->GetJoints()[0];
  }
  std::cout << __PRETTY_FUNCTION__ << " parent " <<_joint->GetParent()->GetScopedName()  << std::endl;
  std::cout << __PRETTY_FUNCTION__ << " child " <<_joint->GetChild()->GetScopedName() << std::endl;
  //std::cout << __PRETTY_FUNCTION__ << " setting pid itinial " << _config.p_gain << " " <<  _config.i_gain << " " <<  _config.d_gain << std::endl;
  _pid = common::PID(0.1, 0.0, 0.0);

  // // Apply the P-controller to the joint.
  _model->GetJointController()->SetVelocityPID(_joint->GetScopedName(), _pid);

  // // Set the joint's target velocity. This target velocity is just
  // // for demonstration purposes.
  _model->GetJointController()->SetVelocityTarget(_joint->GetScopedName(), velocity);

  _node = gazebo::transport::NodePtr(new gazebo::transport::Node());
  _node->Init();

  _pub = _node->Advertise<gazebo::msgs::Vector3d>(topicGazeboName, 1); // TODO: why do we need a vector3? Check the msg types in gazebo

  if(!_pub->WaitForConnection(common::Time(1.0)))
    std::cout << __PRETTY_FUNCTION__ << " timeout establishing connection to receiving gazebo node on topic " << topicGazeboName << std::endl;
  // std::cout << __PRETTY_FUNCTION__ << " na guutttt ich sag ja gar nix " << std::endl;
  _threadCommunication = std::thread(&PluginJointRotary::eventLoop, this);

  // _callBackConfig = boost::bind(&PluginJointRotary::callBackDynamicReconfigure, this, _1, _2);
  // _serverReconf.setCallback(_callBackConfig);  //toDO: dynamic reconfigure currently produces strange results. Check and remove completely or put back in
  _tf.frame_id_ = _joint->GetParent()->GetScopedName();
  _tf.child_frame_id_ = _joint->GetChild()->GetScopedName();
  _tf.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
}

// void PluginJointRotary::callBackDynamicReconfigure(phros_gazebo_plugins::PluginJointRotaryConfig& config, const uint32_t level)
// {
//   _config = config;
//   //_model->GetJointController()->SetVelocityTarget(_joint->GetScopedName(), _config.velocity);
//   // _pid = common::PID(_config.p_gain, _config.i_gain, _config.d_gain);
//   // _model->GetJointController()->SetVelocityPID(_joint->GetScopedName(), _pid);
// }

void PluginJointRotary::eventLoop()
{
  std::cout << __PRETTY_FUNCTION__ << " huh " << std::endl;
  while(1)
  {
    //ros::spinOnce();

    double       pos = _joint->Position();
    const double nTp = std::floor(pos / (2.0 * M_PI));
    pos              = pos - nTp * (2.0 * M_PI); 
    gazebo::msgs::Vector3d msg;

    gazebo::msgs::Set(&msg, ignition::math::Vector3d(pos, 0, 0));
    _pub->Publish(msg);
    tf::Quaternion quat;
    quat.setRPY(0.0, 0.0, pos);
    _tf.setRotation(quat);
    _tf.stamp_          = ros::Time::now();
    _bc.sendTransform(_tf);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
GZ_REGISTER_MODEL_PLUGIN(PluginJointRotary)
} // namespace gazebo