#include "hexaglide_driver_node.h"

HexaglideDriverNode::HexaglideDriverNode(ros::NodeHandle &nh) : 
  iri_base_driver::IriBaseNodeDriver<HexaglideDriver>(nh)
{
  //init class attributes if necessary
  //this->loop_rate_ = 2;//in [Hz]

  // [init publishers]
  this->joint_state_publisher_ = this->public_node_handle_.advertise<sensor_msgs::JointState>("joint_state", 100);
  this->joint_state_JointState_msg_.header.frame_id="";
  this->joint_state_JointState_msg_.position.resize(6);
  this->joint_state_JointState_msg_.name.resize(6);
  for (int it=0;it<6;it++)
    this->joint_state_JointState_msg_.name[it]=joint_names[it];

  // [init subscribers]
  
  // [init services]
  this->shutdown_server_ = this->public_node_handle_.advertiseService("shutdown", &HexaglideDriverNode::shutdownCallback, this);
  pthread_mutex_init(&this->shutdown_mutex_,NULL);

  this->home_server_ = this->public_node_handle_.advertiseService("home", &HexaglideDriverNode::homeCallback, this);
  pthread_mutex_init(&this->home_mutex_,NULL);

  
  // [init clients]
  
  // [init action servers]
  ROS_INFO("HexaglideDriverNode::Constructor");
  // [init action clients]
}

void HexaglideDriverNode::mainNodeThread(void)
{
  //lock access to driver if necessary
  this->driver_.lock();

  // [fill msg Header if necessary]

  // [fill msg structures]
//  this->joint_state_JointState_msg_.name =
//  ROS_INFO("HexaglideDriverNode::Filling publisher");
  this->joint_state_JointState_msg_.header.stamp = ros::Time::now(); 
  driver_.get_joint_position(this->joint_state_JointState_msg_.position);
//  this->joint_state_JointState_msg_.velocity=
//  this->joint_state_JointState_msg_.effort= 

  // Initialize the topic message structure
  //this->joint_state_JointState_msg_.data = my_var;

  
  // [fill srv structure and make request to the server]
  
  // [fill action structure and make request to the action server]

  // [publish messages]
  // Uncomment the following line to publish the topic message
  this->joint_state_publisher_.publish(this->joint_state_JointState_msg_);


  //unlock access to driver if previously blocked
  this->driver_.unlock();
}

/*  [subscriber callbacks] */

/*  [service callbacks] */
bool HexaglideDriverNode::shutdownCallback(roscpp::Empty::Request &req, roscpp::Empty::Response &res)
{
  ROS_INFO("HexaglideDriverNode::shutdownCallback: New Request Received!");

  this->driver_.shutdown();

  //use appropiate mutex to shared variables if necessary
  //this->driver_.lock();
  //this->shutdown_mutex_enter();

  //ROS_INFO("HexaglideDriverNode::shutdownCallback: Processing New Request!");
  //do operations with req and output on res
  //res.data2 = req.data1 + my_var;

  //unlock previously blocked shared variables
  //this->shutdown_mutex_exit();
  //this->driver_.unlock();

  return true;
}

void HexaglideDriverNode::shutdown_mutex_enter(void)
{
  pthread_mutex_lock(&this->shutdown_mutex_);
}

void HexaglideDriverNode::shutdown_mutex_exit(void)
{
  pthread_mutex_unlock(&this->shutdown_mutex_);
}

bool HexaglideDriverNode::homeCallback(roscpp::Empty::Request &req, roscpp::Empty::Response &res)
{
  ROS_INFO("HexaglideDriverNode::homeCallback: New Request Received!");

  this->driver_.home();
  //use appropiate mutex to shared variables if necessary
  //this->driver_.lock();
  //this->home_mutex_enter();

  //ROS_INFO("HexaglideDriverNode::homeCallback: Processing New Request!");
  //do operations with req and output on res
  //res.data2 = req.data1 + my_var;

  //unlock previously blocked shared variables
  //this->home_mutex_exit();
  //this->driver_.unlock();

  return true;
}

void HexaglideDriverNode::home_mutex_enter(void)
{
  pthread_mutex_lock(&this->home_mutex_);
}

void HexaglideDriverNode::home_mutex_exit(void)
{
  pthread_mutex_unlock(&this->home_mutex_);
}


/*  [action callbacks] */

/*  [action requests] */

void HexaglideDriverNode::postNodeOpenHook(void)
{
}

void HexaglideDriverNode::addNodeDiagnostics(void)
{
}

void HexaglideDriverNode::addNodeOpenedTests(void)
{
}

void HexaglideDriverNode::addNodeStoppedTests(void)
{
}

void HexaglideDriverNode::addNodeRunningTests(void)
{
}

void HexaglideDriverNode::reconfigureNodeHook(int level)
{
}

HexaglideDriverNode::~HexaglideDriverNode(void)
{
  // [free dynamic memory]
  pthread_mutex_destroy(&this->shutdown_mutex_);
  pthread_mutex_destroy(&this->home_mutex_);
}

/* main function */
int main(int argc,char *argv[])
{
  return driver_base::main<HexaglideDriverNode>(argc, argv, "hexaglide_driver_node");
}
