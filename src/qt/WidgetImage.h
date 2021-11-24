#ifndef PHILLIB_QT_WIDGET_IMAGE_H_
#define PHILLIB_QT_WIDGET_IMAGE_H_

#include "datatypes.h"
#include <QtWidgets/QWidget>
#include <memory>

namespace phillib
{
namespace qt
{

class WidgetImage : public QWidget
{
  Q_OBJECT
public:
  WidgetImage(QWidget* parent = nullptr);
  virtual ~WidgetImage() {}
  virtual void paintEvent(QPaintEvent* event) override;
  void         setPoints(const QVector<QPoint>& points) { _points = points; }
  void         addPoint(const QPoint& point) { _points.push_back(point); }
  void         setPointsRGB(const QVector<QPointRGB>& pointsRGB) { _pointsRGB = pointsRGB; }
  void         addPointRGB(const QPointRGB& pointRGB) { _pointsRGB.push_back(pointRGB); }
  void         setRects(const QVector<QRect>& rects) { _rects = rects; }
  void         setRectsFilled(const QVector<QRectFilled>& rectsFilled) { _rectsFilled = rectsFilled; }
  void         setRectsCustom(const QVector<QRectCustom>& rectsCustom) { _rectsCustom = rectsCustom; }
  void setImageBackground(const QImage& image);
  void reset();
  // void         addRect(const QRect& var) { _rects.push_back(var); }
  // void         addLine(const QLine& var) { _lines.push_back(var); }
  // void addLineRGB(const QLineRGB& var){_linesRGB.push_back(var);}
  // void         addPoint(const QPoint& var) { _points.push_back(var); }
  // void         addPointRGB(const QPointRGB& var) { _pointsRGB.push_back(var); }
protected:
  void mousePressEvent(QMouseEvent* event)override;
 signals:
   void mousePressed(QPoint& pos);    
private:
  void                 drawPoints(QPainter& painter, const int sizePoint = 2);
  void                 drawPointsRGB(QPainter& painter);
  void                 drawRects(QPainter& painter, const int sizeLine = 2);
  void                 drawRectsFilled(QPainter& painter);
  void                 drawRectsCustom(QPainter& painter);
  QVector<QRect>       _rects;
  QVector<QRectFilled> _rectsFilled;
  QVector<QRectCustom> _rectsCustom;
  QVector<QLine>       _lines;
  QVector<QLineRGB>    _linesRGB;
  QVector<QPoint>      _points;
  QVector<QPointRGB>   _pointsRGB;
  std::unique_ptr<QImage> _imageBackGround = nullptr;
};

} // namespace qt

} // namespace phillib
#endif
