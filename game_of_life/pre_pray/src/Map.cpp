#include "Map.h"
#include <cmath>
#include <QtCore/QDebug>
namespace phillib {
namespace game_of_life {
Map::Map(const unsigned int height, const unsigned int width)
    : _map(height * width), _sizeMap(QPoint(0, 0), QSize(height, width)) {}

bool Map::set(const QPoint &idcs, std::shared_ptr<IObjectMap> ptr) {
  qDebug() << __PRETTY_FUNCTION__ << "";
  const QPoint idcsR(static_cast<int>(std::floor(static_cast<float>(idcs.x()) / _sizeCell)),
  static_cast<int>(std::floor(static_cast<float>(idcs.y()) / _sizeCell)));
  if ((idcs.x() > _sizeMap.width()) || (idcs.y() > _sizeMap.height()) ||
      (idcs.x() < 0) || (idcs.y() < 0))
    return false; // Todo: Recalculate index
  const unsigned int idx = idcs.y() * _sizeMap.width() + idcs.x();
  _map[idx] = ptr;
  return true;
}

std::shared_ptr<IObjectMap> Map::get(const QPoint &idcs) {
  qDebug() << __PRETTY_FUNCTION__ << "";
  if ((idcs.x() > _sizeMap.width()) || (idcs.y() > _sizeMap.height()) ||
      (idcs.x() < 0) || (idcs.y() < 0))
    return nullptr; // Todo: Recalculate index
  const unsigned int idx = idcs.y() * _sizeMap.width() + idcs.x();
  return _map[idx].lock();
}

std::shared_ptr<QImage> Map::imageMap() {
  qDebug() << __PRETTY_FUNCTION__ << "";
  // auto qimage = std::make_shared<QImage>(
  //     QSize(_sizeMap.width(), _sizeMap.height()), QImage::Format_RGB888);
  std::vector<uchar> bufr(_sizeMap.width() * _sizeMap.height() * 3, 0);
  for (unsigned int i = 0; i < _sizeMap.height(); i++)
    for (unsigned int j = 0; j < _sizeMap.width(); j++) {
      const unsigned int idx = i * _sizeMap.width() + j;
           //bufr[idx * 3 + 0] = 255;
           bufr[idx * 3 + 1] = 255;
           //bufr[idx * 3 + 2] = 255;

      // std::shared_ptr<IObjectMap> ptr;
      // if (!(ptr = _map[idx].lock()))
      //   continue;
      // else {
      //   int health = ptr->health();
      //   int val = static_cast<int>(
      //       std::round((static_cast<double>(ptr->health()) / 100.0) * 255.0));
      //   switch (ptr->type()) {
      //   case IObjectMap::Type::FOOD: {
      //     bufr[idx * 3 + 1] = val;
      //     break;
      //   }
      //   case IObjectMap::Type::PREY: {
      //     bufr[idx * 3 + 1] = val;
      //     break;
      //   }
      //   default:
      //       qDebug() << __PRETTY_FUNCTION__ << " This should not happen...";
      //     break;
      //   }
      // }
    }
    return std::make_shared<QImage>(bufr.data(), _sizeMap.width(), _sizeMap.height(), QImage::Format_RGB888);
}

unsigned int Map::adjacent(std::vector<std::weak_ptr<IObjectMap> >& adjacent, const QPoint& idx)
{
  qDebug() << __PRETTY_FUNCTION__ << "";
  for(unsigned int i = idx.y() - 1; i <= idx.y() + 1; i++)
    for(unsigned int j = idx.x() - 1; j <= idx.x() + 1; j++)
    {
      if ((idx.x() > _sizeMap.width()) || (idx.y() > _sizeMap.height()) ||
      (idx.x() < 0) || (idx.y() < 0))
         continue; // Todo: Recalculate index 
         adjacent.push_back(_map[idx.y() * _sizeMap.width() + j]);
    }
    return adjacent.size();
}

} // namespace game_of_life
} // namespace phillib
