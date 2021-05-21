#include "WidgetDisplay.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtGui/QWheelEvent>
namespace phillib {
namespace qt {
WidgetDisplay::WidgetDisplay() { this->resize(800, 800); 
_mousePtr = this->rect().center();
}

void WidgetDisplay::wheelEvent(QWheelEvent *event) 
{
  float increment = 0.0f;
  if(event->angleDelta().y() > 0)
    increment = 0.1f;
  else if(event->angleDelta().y() < 0)  
    increment = -0.1f;
  else  
    increment = 0.0f;
  _scale += increment;  
  //qDebug() << __PRETTY_FUNCTION__ << "  scale " << _scale << " pos " << event->pos();
  _mousePtr = event->pos();
}

void WidgetDisplay::mouseMoveEvent(QMouseEvent* event)
{
  //qDebug() << __PRETTY_FUNCTION__ << " viewport pose " << event->pos() << " button " << event->buttons();
  event->accept();
  if(event->buttons() == Qt::MiddleButton)
  {
    //qDebug() << __PRETTY_FUNCTION__ << " viewport pose " << event->pos();
    _mousePtr = event->pos();
  }
}

void WidgetDisplay::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect viewPort = painter.viewport();
  QSize vpSize = viewPort.size();  
  vpSize.scale(vpSize * _scale, Qt::KeepAspectRatio);
  viewPort.setSize(vpSize);
  viewPort.moveCenter(_mousePtr);
  painter.setViewport(viewPort);
  // QPen pen(Qt::SolidLine);
  // pen.setWidth(10);
  // pen.setColor(Qt::green);
  // painter.setPen(pen);
  // QRect rect = this->rect();
  // QSize size = rect.size();
  // size.scale(rect.size() / 2, Qt::KeepAspectRatio);
  // rect.setSize(size);
  // rect.moveCenter(this->rect().center());
  // //painter.drawRect(rect);
  if((_backGround.height() > 0) && (_backGround.width() > 0))
    painter.drawImage(this->rect(), _backGround, _backGround.rect());
  this->update();
}

bool WidgetDisplay::loadImage(const std::string& path)
{
  return _backGround.load(QString(path.c_str()));
}
} // namespace qt
} // namespace phillib
