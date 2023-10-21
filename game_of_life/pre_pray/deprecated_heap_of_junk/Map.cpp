#include "Map.h"
#include <QtCore/QDebug>
#include <cmath>
namespace phillib
{
namespace game_of_life
{

std::unique_ptr<Map> Map::_instance(nullptr);

Map& Map::instance(void)
{
  if(!_instance)
    _instance = std::unique_ptr<Map>(new Map);
  return *_instance.get();
}

void Map::initialize(const QSize& size)
{
  // qDebug() << __PRETTY_FUNCTION__ << "";
  //  qDebug() << __PRETTY_FUNCTION__ << " map size " << _map.size();
       _map.resize(size.height() * size.width());
    //qDebug() << __PRETTY_FUNCTION__ << " map size " << _map.size();    
     _sizeMap = QRect(QPoint(0, 0), size);
}

bool Map::set(const QPointF& crds, std::shared_ptr<IObjectMap> ptr)
{
 // qDebug() << __PRETTY_FUNCTION__ << " in " << crds;
  if(!this->initialized())
  {
    // qDebug() << __PRETTY_FUNCTION__ << " naaa";
    // qDebug() << __PRETTY_FUNCTION__ << " map size " << _map.size();
    return false;
  }
  const QPoint idcs(static_cast<int>(std::floor(static_cast<float>(crds.x()) / _sizeCell)),
                     static_cast<int>(std::floor(static_cast<float>(crds.y()) / _sizeCell)));
  //                   qDebug() << __PRETTY_FUNCTION__ << " idcs " << idcs;
  if((idcs.x() > _sizeMap.width()) || (idcs.y() > _sizeMap.height()) || (idcs.x() < 0) || (idcs.y() < 0))
  {
    return false; // Todo: Recalculate index
  }
    
  const unsigned int idx = idcs.y() * _sizeMap.width() + idcs.x();
  if(_map[idx].lock())
  {
    //qDebug() << __PRETTY_FUNCTION__ << " idx " << idcs << " occppied";
    return false;
  }
  _map[idx]              = ptr;
  ptr->setIdx(idcs);
  return true;
}

bool Map::set(const QPoint& idcs, std::shared_ptr<IObjectMap> ptr)
{
if((idcs.x() > _sizeMap.width()) || (idcs.y() > _sizeMap.height()) || (idcs.x() < 0) || (idcs.y() < 0))
    return false; // Todo: Recalculate index
  const unsigned int idx = idcs.y() * _sizeMap.width() + idcs.x();
  _map[idx]              = ptr;
  ptr->setIdx(idcs);
  return true;
}

std::shared_ptr<IObjectMap> Map::get(const QPoint& idcs)
{
 // qDebug() << __PRETTY_FUNCTION__ << "";
  if((idcs.x() > _sizeMap.width()) || (idcs.y() > _sizeMap.height()) || (idcs.x() < 0) || (idcs.y() < 0))
    return nullptr; // Todo: Recalculate index
  const unsigned int idx = idcs.y() * _sizeMap.width() + idcs.x();
  return _map[idx].lock();
}

const QRectF Map::sizeMap(void)
{
  float width = static_cast<float>(_sizeMap.width()) * _sizeCell;
  float height = static_cast<float>(_sizeMap.height()) * _sizeCell;
  return QRectF(0.0, 0.0, width, height);
}

// std::shared_ptr<QImage> Map::imageMap() {
//   qDebug() << __PRETTY_FUNCTION__ << "";
//   // auto qimage = std::make_shared<QImage>(
//   //     QSize(_sizeMap.width(), _sizeMap.height()), QImage::Format_RGB888);
//   std::vector<uchar> bufr(_sizeMap.width() * _sizeMap.height() * 3, 0);
//   for (unsigned int i = 0; i < _sizeMap.height(); i++)
//     for (unsigned int j = 0; j < _sizeMap.width(); j++) {
//       const unsigned int idx = i * _sizeMap.width() + j;
//            //bufr[idx * 3 + 0] = 255;
//            bufr[idx * 3 + 1] = 255;
//            //bufr[idx * 3 + 2] = 255;

//       // std::shared_ptr<IObjectMap> ptr;
//       // if (!(ptr = _map[idx].lock()))
//       //   continue;
//       // else {
//       //   int health = ptr->health();
//       //   int val = static_cast<int>(
//       //       std::round((static_cast<double>(ptr->health()) / 100.0) * 255.0));
//       //   switch (ptr->type()) {
//       //   case IObjectMap::Type::FOOD: {
//       //     bufr[idx * 3 + 1] = val;
//       //     break;
//       //   }
//       //   case IObjectMap::Type::PREY: {
//       //     bufr[idx * 3 + 1] = val;
//       //     break;
//       //   }
//       //   default:
//       //       qDebug() << __PRETTY_FUNCTION__ << " This should not happen...";
//       //     break;
//       //   }
//       // }
//     }
//     return std::make_shared<QImage>(bufr.data(), _sizeMap.width(), _sizeMap.height(), QImage::Format_RGB888);
// }

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
