#ifndef PHILLIB_GAME_OF_LIFE_IOBJECTMAP_H_
#define PHILLIB_GAME_OF_LIFE_IOBJECTMAP_H_

#include <cinttypes>
#include <QtCore/QPoint>

namespace phillib
{
namespace game_of_life
{
class IObjectMap
{
public:
enum class Type 
{
  FOOD = 0,
  PREY
};
  IObjectMap(){}
  virtual ~IObjectMap(){}
  virtual Type typeObjectMap(void)const=0;
  virtual const QPoint& idx(void)const=0;
  virtual void setIdx(const QPoint& idx)=0;
  
};
} // namespace game_of_life
} // namespace phillib
#endif
