#ifndef PHILLIB_GAME_OF_LIFE_MAP_H_
#define PHILLIB_GAME_OF_LIFE_MAP_H_

#include <vector>
#include <memory>
#include "IObjectMap.h"
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtGui/QImage>

namespace phillib
{
namespace game_of_life
{
  class Map
  {
    public:
    Map(const unsigned int height, const unsigned int width);
    virtual ~Map(){}
    bool set(const QPointF& crds, std::shared_ptr<IObjectMap> ptr);
    std::shared_ptr<IObjectMap> get(const QPoint& idcs);
    const QRect& sizeMap(void)const{return _sizeMap;}
    //unsigned int adjacent(std::vector<std::weak_ptr<IObjectMap> >& adjacent, const QPoint& idx); 
//    unsigned int getAllMapObjects(std::vector<std::shared_ptr<IObjectMap> >& objects);
    //std::shared_ptr<QImage> imageMap();
    private:
      QRect _sizeMap;
      std::vector<std::weak_ptr<IObjectMap> > _map;
      const float _sizeCell = 0.10f;
};
}
}
#endif

