#ifndef PLUGIN_MOTOR_VELODYNE_H_
#define PLUGIN_MOTOR_VELODYNE_H_

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <thread>
#include <cmath>
namespace gazebo
{
/// \brief A plugin to control a Velodyne sensor.
class PluginMotorVelodyne : public ModelPlugin
{
  private:
  physics::ModelPtr _model;
  physics::JointPtr _joint;
  common::PID       _pid;
   std::thread _t;
    transport::NodePtr _node;
     gazebo::transport::PublisherPtr _pub;
       /// \brief Constructor
public:
  PluginMotorVelodyne() {}
  virtual ~PluginMotorVelodyne() {}
  void loop()
  {
    while(1)
    {
    double pos = _joint->Position();
    const double nTp = std::floor(pos / (2.0 * M_PI));
    pos = pos - nTp * (2.0 * M_PI);//std::floor(pos / (2.0 * M_PI));
    //std::cout << __PRETTY_FUNCTION__ << " pos " << pos << std::endl;
    gazebo::msgs::Vector3d msg;
    

  gazebo::msgs::Set(&msg, ignition::math::Vector3d(pos, 0, 0));
  _pub->Publish(msg);
    }
  }

  /// \brief The load function is called by Gazebo when the plugin is
  /// inserted into simulation
  /// \param[in] _model A pointer to the model that this plugin is
  /// attached to.
  /// \param[in] _sdf A pointer to the plugin's SDF element.
  virtual void Load(physics::ModelPtr model, sdf::ElementPtr sdf)
  {
    // Just output a message for now
    std::cerr << "\nThe velodyne plugin is attach to model[" << model->GetName() << "]\n";
    if(model->GetJointCount() == 0)
    {
      std::cerr << "Invalid joint count, Velodyne plugin not loaded\n";
      return;
    }

    // Store the model pointer for convenience.
    _model = model;

    // // Get the first joint. We are making an assumption about the model
    // // having one joint that is the rotational joint.
    _joint = model->GetJoints()[0];

    // // Setup a P-controller, with a gain of 0.1.
    _pid = common::PID(0.1, 0, 0);

    // // Apply the P-controller to the joint.
    _model->GetJointController()->SetVelocityPID(_joint->GetScopedName(), _pid);

    // // Set the joint's target velocity. This target velocity is just
    // // for demonstration purposes.
    _model->GetJointController()->SetVelocityTarget(_joint->GetScopedName(), 1.0);
    
    _node =  gazebo::transport::NodePtr(new gazebo::transport::Node());
  _node->Init();

    _pub = _node->Advertise<gazebo::msgs::Vector3d>("motor_angle");
    _pub->WaitForConnection();
    _t = std::thread(&PluginMotorVelodyne::loop, this);
  }
    
  /// \brief Pointer to the model.

};

// Tell Gazebo about this plugin, so that Gazebo can call Load on this plugin.
GZ_REGISTER_MODEL_PLUGIN(PluginMotorVelodyne)
} // namespace gazebo
#endif