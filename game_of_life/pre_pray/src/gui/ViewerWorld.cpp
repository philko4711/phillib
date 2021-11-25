#include "ViewerWorld.h"
#include <QtGui/QMouseEvent>
namespace phillib
{
namespace game_of_life
{
ViewerWorld::ViewerWorld(QWidget* parent)
    : QGraphicsView(parent)
{
  this->setScene(new QGraphicsScene(0, 0, 600, 600));
  this->setStyleSheet("background-color:black");
}

// void ViewerWorld::mousePressEvent(QMouseEvent* event)
// {
//   // qDebug() << __PRETTY_FUNCTION__ << "entry";
//   auto scene = this->scene();
//   auto point = this->mapToScene(event->pos());
//   if((event->button() == Qt::LeftButton))
//   {
    
//   }
//   else
//     QGraphicsView::mouseMoveEvent(event);
//   this->update();
// }

} // namespace game_of_life
} // namespace phillib
