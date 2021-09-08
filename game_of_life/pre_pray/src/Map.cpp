#include "Map.h"

namespace phillib
{
namespace game_of_life
{
Map::Map(const unsigned int height, const unsigned int width)
    : _map(height * width)
    , _sizeMap(QPoint(0, 0), QSize(height, width))
{
}

bool Map::set(const QPoint& idcs, std::shared_ptr<IObjectMap> ptr)
{
  if((idcs.x() > _sizeMap.width()) || (idcs.y() > _sizeMap.height()) 
  || (idcs.x() < 0) || (idcs.y() < 0))
    return false; //Todo: Recalculate index
  const unsigned int idx = idcs.y() * _sizeMap.x() + idcs.x();     
  _map[idx] = ptr;
  return true;
}

std::shared_ptr<IObjectMap> Map::get(const QPoint& idcs)
{
if((idcs.x() > _sizeMap.width()) || (idcs.y() > _sizeMap.height()) 
  || (idcs.x() < 0) || (idcs.y() < 0))
    return nullptr; //Todo: Recalculate index
  const unsigned int idx = idcs.y() * _sizeMap.x() + idcs.x();     
  return _map[idx].lock();
}

} // namespace game_of_life
} // namespace phillib
