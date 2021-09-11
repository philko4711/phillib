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
  const unsigned int idx = idcs.y() * _sizeMap.width() + idcs.x();     
  _map[idx] = ptr;
  return true;
}

std::shared_ptr<IObjectMap> Map::get(const QPoint& idcs)
{
if((idcs.x() > _sizeMap.width()) || (idcs.y() > _sizeMap.height()) 
  || (idcs.x() < 0) || (idcs.y() < 0))
    return nullptr; //Todo: Recalculate index
  const unsigned int idx = idcs.y() * _sizeMap.width() + idcs.x();     
  return _map[idx].lock();
}

std::shared_ptr<QImage> Map::imageMap()
{
  auto qimage = std::make_shared<QImage>(QSize(_sizeMap.width(), _sizeMap.height()), QImage::Format_ARGB32);
  for(unsigned int i = 0; i < _sizeMap.height(); i++)
    for(unsigned int j = 0; j < _sizeMap.width(); j++)
    {

    }
}

} // namespace game_of_life
} // namespace phillib
