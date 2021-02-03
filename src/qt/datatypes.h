#ifndef PHILLIB_QT_DATATYPES_H_
#define PHILLIB_QT_DATATYPES_H_

#include <QtGui/QColor>
#include <QtCore/QPoint>
#include <QtCore/QLine>
#include <QtCore/QRect>

namespace phillib
{
namespace qt
{
struct QPointRGB
{
  QPointRGB(const QPoint& point, const QColor& rgb = Qt::black, const int size = 1, Qt::BrushStyle styleBrush = Qt::SolidPattern)
      : _point(point)
      , _rgb(rgb)
      , _size(size)
      , _styleBrush(styleBrush)
  {
  }
  QPointRGB(){}
  const QPoint&         point(void) const { return _point; }
  const QColor&         rgb(void) const { return _rgb; }
  const int&            size(void) const { return _size; }
  const Qt::BrushStyle& styleBrush(void) const { return _styleBrush; }
  QPoint                _point;
  QColor                _rgb;
  int                   _size;
  Qt::BrushStyle        _styleBrush;
};
struct QLineRGB
{
  QLineRGB(const QLine& line, const QColor& rgb = Qt::black, const int thickness = 1)
      : _line(line)
      , _rgb(rgb)
      , _thickness(thickness)
  {
  }
  const QLine&  line(void) const { return _line; }
  const QColor& rgb(void) const { return _rgb; }
  int           thickness(void) const { return _thickness; }
  QLine         _line;
  QColor        _rgb;
  int           _thickness;
};
struct QRectFilled
{
  QRectFilled(const QRect& rect, const QColor& rgbFilling, const Qt::BrushStyle& patternFilling = Qt::SolidPattern)
      : _rect(rect)
      , _rgbFilling(rgbFilling)
      , _patternFilling(patternFilling)
  {
  }
  QRectFilled()
      : _patternFilling(Qt::SolidPattern)
  {
  }
  bool                  operator==(const QRect& rect) { return _rect == rect; }
  const QRect&          rect(void) const { return _rect; }
  const QColor&         rgbFilling(void) const { return _rgbFilling; }
  const Qt::BrushStyle& patternFilling(void) const { return _patternFilling; }
  QRect                 _rect;
  QColor                _rgbFilling;
  Qt::BrushStyle        _patternFilling;
};
struct QRectCustom
{
  QRectCustom(QRect& rect, const QColor& rgbLine, int thicknessLine, const Qt::PenStyle& styleLine = Qt::SolidLine)
      : _rect(rect)
      , _rgbLine(rgbLine)
      , _thickNessLine(thicknessLine)
      , _styleLine(styleLine)
  {
    //_thickNessLine = thickNessLine;
  }
  QRectCustom() {}
  const QRect&        rect(void) const { return _rect; }
  const QColor&       rgbLine(void) const { return _rgbLine; }
  const Qt::PenStyle& styleLine(void) const { return _styleLine; }
  const int&          thickNessLine(void) const { return _thickNessLine; }
  QRect               _rect;
  QColor              _rgbLine;
  int                 _thickNessLine;
  Qt::PenStyle        _styleLine;
};
} // namespace qt
} // namespace phillib

#endif