#ifndef PHILLIB_GAME_OF_LIFE_FOOD_H_
#define PHILLIB_GAME_OF_LIFE_FOOD_H_


#include "IObjectMap.h"
#include <memory>

namespace phillib
{
namespace game_of_life
{
  class Food : public IObjectMap, std::enable_shared_from_this<Food>
  {
    public:
    Food();
    virtual ~Food();
    std::shared_ptr<Food> ptr(){return shared_from_this();}
    virtual uint8_t health(void)const;
    private:
      unsigned int _amount;
};
}
}
#endif

