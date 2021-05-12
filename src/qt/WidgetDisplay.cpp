#include "WidgetDisplay.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtGui/QWheelEvent>
namespace phillib {
namespace qt {
WidgetDisplay::WidgetDisplay() { this->resize(800, 800); }

void WidgetDisplay::wheelEvent(QWheelEvent *event) 
{
  int increment = 0;
  if(event->angleDelta().y() > 0)
    increment = 1;
  else if(event->angleDelta().y() < 0)  
    increment = -1;
  else  
    increment = 0;
  _scale += increment;  
  qDebug() << __PRETTY_FUNCTION__ << "  scale " << _scale;
  _mousePtr = event->pos();

}

void WidgetDisplay::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect viewPort = painter.viewport();
  QSize vpSize = viewPort.size();  
  vpSize.scale(vpSize * _scale, Qt::KeepAspectRatio);
  viewPort.setSize(vpSize);
  viewPort.moveCenter(_mousePtr);
  painter.setViewport(viewPort);
  QPen pen(Qt::SolidLine);
  pen.setWidth(10);
  pen.setColor(Qt::green);
  painter.setPen(pen);
  QRect rect = this->rect();
  QSize size = rect.size();
  size.scale(rect.size() / 2, Qt::KeepAspectRatio);
  rect.setSize(size);
  rect.moveCenter(this->rect().center());
  painter.drawRect(rect);
  this->update();
}
} // namespace qt
} // namespace phillib
