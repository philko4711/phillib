#include "GrView.h"
#include "GraphScExample.h"
#include <QtCore/QDebug>
#include <QtWidgets/QGraphicsItem>
#include <phillib_utils/random.h>
namespace phillib {
namespace qt {
GrView::GrView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(parent) {
  this->setScene(scene);
  this->setMouseTracking(true);
}

void GrView::mousePressEvent(QMouseEvent *event) {
  // qDebug() << __PRETTY_FUNCTION__ << "entry";
  auto scene = this->scene();
  auto point = this->mapToScene(event->pos());
  if ((event->button() == Qt::LeftButton)) {
    dynamic_cast<GraphScExample *>(scene)->drawPoint(point);
    scene->addEllipse(point.x(), point.y(), 2.0, 2.0, QPen(QBrush(Qt::green), 50), QBrush(Qt::green, Qt::SolidPattern));
  }
  auto items = scene->items();
  if(items.size())
  {
  std::vector<int> rd;
  phillib::utils::randomInts(1, rd, 1, items.size() - 1);
  //items[*rd.begin()]->
  }
  // for(auto& iter : scene->items())
  // {
  //   //qDebug() << __PRETTY_FUNCTION__ << " " << iter->type() == QGraphicsEllipseItem;
  //   auto ptr = qgraphicsitem_cast<QGraphicsEllipseItem*>(iter);
  //   if(ptr)
  //     qDebug() << __PRETTY_FUNCTION__ << " hehe";
  // } 
  // else if ((event->button() == Qt::MiddleButton))
  //   this->centerOn(this->mapToScene(event->pos()));
  this->update();
}

void GrView::mouseMoveEvent(QMouseEvent *event) {

  if (event->buttons() & Qt::MiddleButton) {
    event->accept();
    //qDebug() << __PRETTY_FUNCTION__ << " middle button active";
    this->centerOn(this->mapToScene(event->pos()));
    this->update();
  } else
    QGraphicsView::mouseMoveEvent(event);
}

void GrView::wheelEvent(QWheelEvent *event) {
  event->accept();
  // qDebug() << __PRETTY_FUNCTION__ << "";
  //_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  if (event->delta() > 0)
    this->centerOn(this->mapToScene(event->pos()));
  else
    this->centerOn(this->mapToScene(this->rect().center()));

  qreal delta = 1 + (event->delta() > 0 ? 0.1 : -0.1);
  this->scale(delta, delta);
}

} // namespace qt
} // namespace phillib
