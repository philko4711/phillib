#include "MainWindow.h"
#include <QtCore/QDebug>
#include <cmath>
//#include <phillib_qt/datatypes.h>
namespace phillib
{
namespace game_of_life
{
MainWindow::MainWindow():_guiUi(new Ui::MainWindowPredPray())
{
  _guiUi->setupUi(this);
  //this->setCentralWidget(_gui.get());
}

void MainWindow::addItem(std::shared_ptr<QGraphicsItem>& item)
{
  _guiUi->viewMain->scene()->addItem(item.get());
  _guiUi->viewMain->update();
  }
//     : _gui(this)
// {
//   _gui.resize(this->size());
//   _gui.setStyleSheet("background-color:black");
// }

// void MainWindow::updateMapObjects(

//     std::vector<std::shared_ptr<IObjectMap>> &mapObjects) {
//   std::vector<qt::QPointRGB> points;
//   std::vector<qt::QRectFilled> rectsFilled;
//   //std::abort();
//   for (auto &iter : mapObjects) {
//     //int health = iter->health();
//     QColor color;
//     int val = static_cast<int>(std::round((static_cast<double>(iter->health()) / 100.0) * 255.0));
//     color.setAlphaF(static_cast<double>(iter->health()) / 100.0);

//     if (iter->type() == IObjectMap::Type::FOOD)
//     {
//       color = Qt::green;//QColor(0, val, 0);
//     }
//     else if (iter->type() == IObjectMap::Type::PREY) // || todo: Predator
//     {
//       color = QColor(0, 0, val);//Qt::blue;
//     }
//     // else
//     // qDebug() << __PRETTY_FUNCTION__ << "hu?";
//     int health = iter->health();
//     color.setAlphaF(static_cast<double>(iter->health()) / 100.0);
//     if (iter->type() == IObjectMap::Type::FOOD)
//     {
//       qt::QRectFilled rectFood(QRect(iter->pos() - QPoint(5, 5), QSize(10, 10)), color);   //Todo: this is for testing. Make size variable or use a const
//       factor rectsFilled.push_back(rectFood);
//     }
//     else if (iter->type() == IObjectMap::Type::PREY) // || todo: Predator
//     {
//     qt::QPointRGB point(iter->pos(), color, 1);
//     //qDebug() << __PRETTY_FUNCTION__ << " point at " << iter->pos();
//     points.push_back(point);
//     }
//   }
//   //qDebug() << __PRETTY_FUNCTION__ << " draw " << points.size();
//   _gui.setPointsRGB(QVector<qt::QPointRGB>::fromStdVector(points));
//   _gui.setRectsFilled(QVector<qt::QRectFilled>::fromStdVector(rectsFilled));
//   _gui.update();
//   this->update();
// }

} // namespace game_of_life
} // namespace phillib
