#include "WidgetImage.h"
#include <QDebug>
#include <QtGui/QPainter>

namespace phillib
{
namespace qt
{

WidgetImage::WidgetImage(QWidget* parent)
    : QWidget(parent)
{
}

void WidgetImage::drawPoints(QPainter& painter)
{
  painter.save();
  QPen   pen(Qt::SolidLine);
  QBrush brush(Qt::SolidPattern);
  pen.setColor(Qt::black);
  brush.setColor(Qt::black);
  painter.setPen(pen);
  painter.setBrush(brush);
  // qDebug() << __PRETTY_FUNCTION__ << " will draw " << _points.size() << " points";
  for(auto& iter : _points)
    painter.drawEllipse(iter, 5, 5);
  painter.restore();
}

void WidgetImage::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  this->drawPoints(painter);
  this->drawRects(painter);
  this->drawRectsCustom(painter);
  this->drawRectsFilled(painter);
}

void WidgetImage::drawRects(QPainter& painter)
{
  painter.save();
  QPen pen(Qt::SolidLine);
  pen.setColor(Qt::black);
  pen.setWidth(5);
  painter.setPen(pen);
  // qDebug() << __PRETTY_FUNCTION__ << " will draw " << _rects.size() << " rects";
  for(auto& iter : _rects)
    painter.drawRect(iter);
  painter.restore();
}

void WidgetImage::drawRectsFilled(QPainter& painter)
{
  //qDebug() << __PRETTY_FUNCTION__ << " will draw " << _rectsFilled.size() << " rectsfilled ";
  for(auto& iter : _rectsFilled)
  {
    painter.save();
    QPen pen(Qt::SolidLine);
    pen.setColor(Qt::black);
    pen.setWidth(5);
    painter.setPen(pen);
    QBrush brush(iter.patternFilling());
    brush.setColor(iter.rgbFilling());
    painter.setBrush(brush);
    painter.drawRect(iter.rect());
    painter.restore();
  }
}

void WidgetImage::drawRectsCustom(QPainter& painter)
{
  //qDebug() << __PRETTY_FUNCTION__ << " will draw " << _rectsCustom.size() << " rectsCustom ";
  for(auto& iter : _rectsCustom)
  {
    painter.save();
    QPen pen(iter.styleLine());
    pen.setColor(iter.rgbLine());
    pen.setWidth(iter.thickNessLine());
    painter.setPen(pen);
    painter.drawRect(iter.rect());
    painter.restore();
  }
}

}

}