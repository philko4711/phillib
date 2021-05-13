#ifndef PHILLIB_QT_WIDGETDISPLAY_H_
#define PHILLIB_QT_WIDGETDISPLAY_H_

#include <QtGui/QImage>
#include <QtWidgets/QWidget>

namespace phillib {
namespace qt {
class WidgetDisplay : public QWidget {
public:
  WidgetDisplay();
  virtual ~WidgetDisplay() {}
  bool loadImage(const std::string &path);

protected:
  void wheelEvent(QWheelEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  QPoint _mousePtr;
  float _scale = 1.0f;
  QImage _backGround;
};
} // namespace qt
} // namespace phillib
#endif
