#include "hexaglide_driver.h"
#include "exceptions.h"

HexaglideDriver::HexaglideDriver(void) :
hexa_id_ ("hexa") ,
hexaglide_(hexa_id_)
{
  //setDriverId(driver string id);
}

bool HexaglideDriver::openDriver(void)
{
  //setDriverId(driver string id);
  try{
    this->hexaglide_.load_config(this->config_.config_file);
  }catch(CException &e){
    return false;
}

  return true;
}

bool HexaglideDriver::closeDriver(void)
{
  return true;
}

bool HexaglideDriver::startDriver(void)
{
  return true;
}

bool HexaglideDriver::stopDriver(void)
{
  return true;
}

void HexaglideDriver::config_update(Config& new_cfg, uint32_t level)
{
  this->lock();
  
  // depending on current state
  // update driver with new_cfg data
  switch(this->getState())
  {
    case HexaglideDriver::CLOSED:
      break;

    case HexaglideDriver::OPENED:
      break;

    case HexaglideDriver::RUNNING:
      break;
  }

  // save the current configuration
  this->config_=new_cfg;

  this->unlock();
}

void HexaglideDriver::home(void)
{
  this->hexaglide_.home();
//  std::string config_filename="../src/xml/hexaglide_config.xml";
//  this->hexaglide_.load_config(config_filename);
}

void HexaglideDriver::shutdown(void)
{
  this->hexaglide_.shutdown();
}

void HexaglideDriver::get_joint_position(std::vector<double> &positions)
{
  this->hexaglide_.get_joint_position(positions);
}

HexaglideDriver::~HexaglideDriver(void)
{
}
