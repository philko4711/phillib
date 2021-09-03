#ifndef PHILLIB_GAME_OF_LIFE_MAP_H_
#define PHILLIB_GAME_OF_LIFE_MAP_H_

#include <vector>
#include <memory>
#include "IObjectMap.h"
#include <QtCore/QPoint>
#include <QtCore/QRect>

namespace phillib
{
namespace game_of_life
{
  class Map
  {
    public:
    Map(const unsigned int height, const unsigned int width);
    virtual ~Map();
    bool set(const QPoint& idcs);
    std::shared_ptr<IObjectMap> get(const QPoint& idcs);
    const QRect& sizeMap(void)const{return _sizeMap;}
    private:
      QRect _sizeMap;
      std::vector<std::weak_ptr<IObjectMap> > _map;
};
}
}
#endif

