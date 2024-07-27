#include "GraphicsView.h"
#include <QtGui/QWheelEvent>
#include <QtCore/QDebug>
#include "FractalLab.h"
namespace phillib
{
  GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView(parent)
  {
    QTransform transform;
    transform.rotate(180);
    this->setTransform(transform);
  }
  void GraphicsView::wheelEvent(QWheelEvent *event)
  {
    qDebug() << __PRETTY_FUNCTION__ << "";
    if (1)//event->modifiers() & Qt::ControlModifier)
    {
      qDebug() << __PRETTY_FUNCTION__ << "huhu";
      // zoom
      const ViewportAnchor anchor = transformationAnchor();
      setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
      int angle = event->angleDelta().y();
      qreal factor;
      if (angle > 0)
      {
        factor = 1.1;
      }
      else
      {
        factor = 0.9;
      }
      scale(factor, factor);
      setTransformationAnchor(anchor);
    }
    else
    {
      QGraphicsView::wheelEvent(event);
    }
  }

  void GraphicsView::mousePressEvent(QMouseEvent* event)
  {
    if(event->button() == Qt::LeftButton)
      FractalLab::instance().iterate();
  }

}
