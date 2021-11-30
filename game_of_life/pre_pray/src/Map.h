#ifndef PHILLIB_GAME_OF_LIFE_MAP_H_
#define PHILLIB_GAME_OF_LIFE_MAP_H_

#include "IObjectMap.h"
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtCore/QDebug>
#include <QtGui/QImage>
#include <memory>
#include <vector>
#include <cmath>

namespace phillib
{
namespace game_of_life
{
class Map
{
public:
  static Map& instance(void);
  void initialize(const QSize& size);
  virtual ~Map() {qDebug() << __PRETTY_FUNCTION__ << "";}
  bool                        set(const QPointF& crds, std::shared_ptr<IObjectMap> ptr);
  bool                        set(const QPoint& idcs, std::shared_ptr<IObjectMap> ptr);
  std::shared_ptr<IObjectMap> get(const QPoint& idcs);
  const QRect&                sizeMap(void) const { return _sizeMap; }
  const QRectF sizeMap(void);
  unsigned int adjacent(std::vector<std::weak_ptr<IObjectMap> >& adjacent, const QPoint& idx);
  const std::weak_ptr<IObjectMap>& idx(QPoint& idx)const{return _map[idx.y() * _sizeMap.width() + idx.x()];}
  //    unsigned int getAllMapObjects(std::vector<std::shared_ptr<IObjectMap> >& objects);
  // std::shared_ptr<QImage> imageMap();
  QPoint toGrid(const QPointF& crds){return QPoint(static_cast<int>(std::floor(static_cast<float>(crds.x()) / _sizeCell)),
                     static_cast<int>(std::floor(static_cast<float>(crds.y()) / _sizeCell)));}
  QPointF toWorld(const QPoint& idcs){return static_cast<QPointF>(idcs) * _sizeCell;}
  const bool initialized(void)const{return _map.size();}
private:
  Map(){qDebug() << __PRETTY_FUNCTION__ << "";}
 static  std::unique_ptr<Map> _instance;
  QRect                                   _sizeMap;
  std::vector<std::weak_ptr<IObjectMap> > _map;
  const float                             _sizeCell = 10.0f;
};
} // namespace game_of_life
} // namespace phillib
#endif
