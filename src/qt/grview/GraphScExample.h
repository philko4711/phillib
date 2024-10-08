#ifndef PHILLIB_QT_GRAPHSCEXAMPLE_H_
#define PHILLIB_QT_GRAPHSCEXAMPLE_H_


#include <QtWidgets/QGraphicsScene>
#include <memory>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
namespace phillib
{
namespace qt
{
  class GraphScExample : public QGraphicsScene
  {
    public:
    GraphScExample(QObject* parent = nullptr);
    virtual ~GraphScExample(){}
    void drawPoint(const QPointF &point);
    void setImage(const QImage& image);//{_qimage = image;}
    protected:
      virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
      virtual void drawBackground(QPainter *painter, const QRectF &rect)override;
    private:
      std::unique_ptr<QPixmap> _image;
      QGraphicsPixmapItem* _item;
      QVector<QPointF> _points;
      QImage _qimage;
};
}
}
#endif

