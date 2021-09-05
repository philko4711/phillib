#ifndef PHILLIB_GAME_OF_LIFE_PREY_H_
#define PHILLIB_GAME_OF_LIFE_PREY_H_


#include "IObjectMap.h"
#include "IAgent.h"
#include <memory>

namespace phillib
{
namespace game_of_life
{
  class Prey : public IObjectMap, IAgent, std::enable_shared_from_this<Prey>
  {
    public:
    Prey();
    virtual ~Prey(){}
    std::shared_ptr<Prey> ptr(){return shared_from_this();}
    virtual uint8_t health(void)const{return 100;}
    virtual void iterate(){}
    virtual Type type(void)const{return IObjectMap::Type::PREY;}
    private:
      float _health;
};
}
}
#endif

