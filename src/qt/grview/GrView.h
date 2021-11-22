#ifndef PHILLIB_QT_GRVIEW_H_
#define PHILLIB_QT_GRVIEW_H_


#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItem>

namespace phillib
{
namespace qt
{
  class ColoredEllipse : public QGraphicsEllipseItem
  {
    public:
      ColoredEllipse(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr):
      QGraphicsEllipseItem(x, y, width, height, parent){}
      protected:
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override
        {
          QPen pen(Qt::SolidLine);
          pen.setColor(_color);
          QBrush brush(Qt::SolidPattern);
          brush.setColor(_color);
          painter->save();
          painter->setPen(pen);
          painter->setBrush(brush);
          painter->drawEllipse(QGraphicsEllipseItem::x(), QGraphicsEllipseItem::y(), QGraphicsEllipseItem::rect().width(), QGraphicsEllipseItem::rect().height());
          painter->restore();
        }
      void setColor(const QColor color){_color = color;}  
    private:
      QColor _color;
  };



  class GrView : public QGraphicsView
  {
    public:
    GrView(QGraphicsScene* scene, QWidget* parent = nullptr);
    virtual ~GrView(){}
    virtual void wheelEvent(QWheelEvent *event)override;//{}
    protected:
      void mousePressEvent(QMouseEvent* event)override;
      void mouseMoveEvent(QMouseEvent* event)override;
    private:
};
}
}
#endif

