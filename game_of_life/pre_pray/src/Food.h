#ifndef PHILLIB_GAME_OF_LIFE_FOOD_H_
#define PHILLIB_GAME_OF_LIFE_FOOD_H_


#include "ObjectMap.h"
#include <memory>

namespace phillib
{
namespace game_of_life
{
  class Food : public ObjectMap, std::enable_shared_from_this<Food>
  {
    public:
    Food(const QPoint& pos);
    virtual ~Food(){}
    std::shared_ptr<Food> ptr(){return shared_from_this();}
    virtual uint8_t health(void)const{return 100;}
    virtual Type type(void)const{return IObjectMap::Type::FOOD;}
    void wither();
    private:
      unsigned int _amount;
};
}
}
#endif

