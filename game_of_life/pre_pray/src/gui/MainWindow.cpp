#include "MainWindow.h"
#include <QtCore/QDebug>
#include <phillib_qt/datatypes.h>
namespace phillib {
namespace game_of_life {
MainWindow::MainWindow() : _gui(this) {
  _gui.resize(this->size());
  _gui.setStyleSheet("background-color:black");
}

void MainWindow::updateMapObjects(
    std::vector<std::shared_ptr<IObjectMap>> &mapObjects) {
  std::vector<qt::QPointRGB> points;
  for (auto &iter : mapObjects) {
    QColor color;
    if (iter->type() == IObjectMap::Type::FOOD) {
      color = Qt::green;
    } else if (iter->type() == IObjectMap::Type::PREY) {
      color = Qt::blue;
    }
    int health = iter->health();
    color.setAlphaF(static_cast<double>(iter->health()) / 100.0);
    qt::QPointRGB point(iter->pos(), color, 1);
    // qDebug() << __PRETTY_FUNCTION__ << " point at " << iter->pos() << " with "
    //          << color;
    points.push_back(point);
  }
  _gui.setPointsRGB(QVector<qt::QPointRGB>::fromStdVector(points));
  _gui.update();
  this->update();
}

} // namespace game_of_life
} // namespace phillib
