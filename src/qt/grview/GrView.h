#ifndef PHILLIB_QT_GRVIEW_H_
#define PHILLIB_QT_GRVIEW_H_


#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItem>
#include <QtCore/QDebug>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QAbstractVideoSurface>
namespace phillib
{
namespace qt
{
  class ColoredEllipse : public QGraphicsEllipseItem
  {
    public:
      ColoredEllipse(qreal x, qreal y, qreal width, qreal height, const QColor& color, QGraphicsItem *parent = nullptr):
      QGraphicsEllipseItem(x, y, width, height, parent), _color(color){}
      void setColor(const QColor color){_color = color;}  
      protected:
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override
        {
          qDebug() << __PRETTY_FUNCTION__ << " draw " << QGraphicsEllipseItem::rect().center() << 
          " " << QGraphicsEllipseItem::rect().width() << " " << QGraphicsEllipseItem::rect().height();
          QPen pen(Qt::SolidLine);
          pen.setColor(_color);
          QBrush brush(Qt::SolidPattern);
          brush.setColor(_color);
          painter->save();
          painter->setPen(pen);
          painter->setBrush(brush);
          painter->drawEllipse(QGraphicsEllipseItem::rect().center(), QGraphicsEllipseItem::rect().width(), QGraphicsEllipseItem::rect().height());
          painter->restore();
        }
      
    private:
      QColor _color;
  };

  class MyVideoSurface : public QAbstractVideoSurface
  {
    Q_OBJECT
    public:
    MyVideoSurface(){}
    virtual ~MyVideoSurface(){}
    protected:
     bool present(const QVideoFrame &frame)override
     {
       qDebug() << __PRETTY_FUNCTION__ << "";
       QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
                 //mode;
                //mode.
                QVideoFrame frameCurrent = frame;
                if(!frameCurrent.map(QAbstractVideoBuffer::MapMode::ReadOnly))
                  qDebug() << __PRETTY_FUNCTION__ << "hei";
       QImage image(frameCurrent.bits(), frameCurrent.width(), frameCurrent.height(), frameCurrent.bytesPerLine(), imageFormat);
       qDebug() << __PRETTY_FUNCTION__ << " w h " << frame.width() << " " << frame.height() << " " <<imageFormat;
      //  if(image.save("/tmp/image.jpg"))
      //   abort();
       emit this->newFrame(image);
       frameCurrent.unmap();
       return true;
     }
     QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
     {
if (handleType == QAbstractVideoBuffer::NoHandle) {
         return QList<QVideoFrame::PixelFormat>()
                 << QVideoFrame::Format_RGB32
                 << QVideoFrame::Format_ARGB32
                 << QVideoFrame::Format_ARGB32_Premultiplied
                 << QVideoFrame::Format_RGB565
                 << QVideoFrame::Format_RGB555;
     } else {
         return QList<QVideoFrame::PixelFormat>();
     }
     }
     signals:
     void newFrame(QImage image);
  };


  class GrView : public QGraphicsView
  {
    Q_OBJECT
    public:
    GrView(QGraphicsScene* scene, QWidget* parent = nullptr);
    virtual ~GrView(){}
    virtual void wheelEvent(QWheelEvent *event)override;//{}
    public slots:
      void newCameraFrame(QImage image);//{this->scene()->setImage}
    protected:
      void mousePressEvent(QMouseEvent* event)override;
      void mouseMoveEvent(QMouseEvent* event)override;
    private:
    QCamera _camera;
};
}
}
#endif

