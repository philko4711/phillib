#include "MainWindow.h"
#include <QtCore/QDebug>
#include <phillib_qt/datatypes.h>
#include <cmath>
namespace phillib {
namespace game_of_life {
MainWindow::MainWindow() : _gui(this) {
  _gui.resize(this->size());
  _gui.setStyleSheet("background-color:black");
}

void MainWindow::updateMapObjects(
  
    std::vector<std::shared_ptr<IObjectMap>> &mapObjects) {
  std::vector<qt::QPointRGB> points;
  std::abort();
  for (auto &iter : mapObjects) {
    //int health = iter->health();
    QColor color;
    int val = static_cast<int>(std::round((static_cast<double>(iter->health()) / 100.0) * 255.0));
    color.setAlphaF(static_cast<double>(iter->health()) / 100.0);
    
    if (iter->type() == IObjectMap::Type::FOOD) {
      color = Qt::green;//QColor(0, val, 0);
    } else if (iter->type() == IObjectMap::Type::PREY) {
      color = QColor(0, 0, val);//Qt::blue;
    }
    // else
    // qDebug() << __PRETTY_FUNCTION__ << "hu?";
    int health = iter->health();
    color.setAlphaF(static_cast<double>(iter->health()) / 100.0);
    qt::QPointRGB point(iter->pos(), color, 1);
    //qDebug() << __PRETTY_FUNCTION__ << " point at " << iter->pos();
    points.push_back(point);
  }
  //qDebug() << __PRETTY_FUNCTION__ << " draw " << points.size();
  _gui.setPointsRGB(QVector<qt::QPointRGB>::fromStdVector(points));
  _gui.update();
  this->update();
}

} // namespace game_of_life
} // namespace phillib
