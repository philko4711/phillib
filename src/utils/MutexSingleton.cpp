#include "MutexSingleton.h"

std::unique_ptr<MutexSingleton> MutexSingleton::_instance;

MutexSingleton& MutexSingleton::getInstance(void)
{
  if(!_instance)
    _instance = std::unique_ptr<MutexSingleton>(new MutexSingleton);
  return *_instance;
}