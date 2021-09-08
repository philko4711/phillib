#ifndef PHILLIB_GAME_OF_LIFE_OBJECTMAP_H_
#define PHILLIB_GAME_OF_LIFE_OBJECTMAP_H_


#include "IObjectMap.h"

#include <QtCore/QPoint>

namespace phillib
{
namespace game_of_life
{
  
  class ObjectMap : public IObjectMap
  {
    public:
    ObjectMap(const QPoint& pos);
    virtual ~ObjectMap(){}
    const QPoint& pos(void)const{return _pos;}
    protected:
     QPoint _pos;
};
}
}
#endif

