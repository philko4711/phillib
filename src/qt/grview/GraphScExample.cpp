#include "GraphScExample.h"
#include <QGraphicsSceneMouseEvent>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtWidgets/QGraphicsPixmapItem>

namespace phillib
{
namespace qt
{
GraphScExample::GraphScExample(QObject* parent):QGraphicsScene(parent),_image(new QPixmap(800, 800)), _item(new QGraphicsPixmapItem())
  {
    //_item->addPixmap(*_image);
  }

void GraphScExample::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  qDebug() << __PRETTY_FUNCTION__ << event->pos();
  if (event->button() == Qt::LeftButton) {
        QPoint point(event->pos().x(), event->pos().y());
        this->drawPoint(point);
        event->accept();
    }
    else QGraphicsScene::mousePressEvent(event);

}

void GraphScExample::drawPoint(const QPointF &point)
{
  qDebug() << __PRETTY_FUNCTION__ << " draw " << point;
  _points.push_back(point);
    // QPainter painter(_image.get());
    // painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    // painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    // painter.drawEllipse(point, 100, 100);
    // _item->setPixmap(*_image);
    this->update();
}  

void GraphScExample::drawBackground(QPainter *painter, const QRectF &rect)
{
  painter->save();
   painter->setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
  for(auto& iter : _points)
  {
   
    painter->drawEllipse(iter, 100, 100);
  }
    painter->restore();
    
}

}
}
