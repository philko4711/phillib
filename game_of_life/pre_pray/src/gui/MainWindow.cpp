#include "MainWindow.h"
#include <phillib_qt/datatypes.h>
namespace phillib
{
namespace game_of_life
{
MainWIndow::MainWIndow() {}

void MainWIndow::updateMapObjects(const QPoint& pos, const std::vector<IObjectMap>& mapObjects)
{
  std::vector<qt::QPointRGB> points;
  for(auto& iter : mapObjects)
  {
    QColor color;
    if(iter.type() == IObjectMap::Type::FOOD)
    {
      color = Qt::green;
    }
    else if(iter.type() == IObjectMap::Type::PREY)
    {
      color = Qt::blue;
    }
    color.setAlphaF(static_cast<double>(iter.health()) / 100.0);
    qt::QPointRGB point(pos, color, 10);
    points.push_back(point);
  }
  _gui.setPointsRGB(QVector<qt::QPointRGB>::fromStdVector(points));
  this->update();
}

} // namespace game_of_life
} // namespace phillib
