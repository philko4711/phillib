#include "GrView.h"
#include <QtCore/QDebug>
#include "GraphScExample.h"
namespace phillib
{
namespace qt
{
GrView::GrView(QGraphicsScene* scene, QWidget* parent):QGraphicsView(parent)
  {
    this->setScene(scene);
  }

void GrView::mousePressEvent(QMouseEvent* event)
{
  qDebug() << __PRETTY_FUNCTION__ << "entry";
  auto scene = this->scene();
  auto point = this->mapToScene(event->pos());
  dynamic_cast<GraphScExample*>(scene)->drawPoint(point);
  this->update();
}
}
}
