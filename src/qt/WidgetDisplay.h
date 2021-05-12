#ifndef PHILLIB_QT_WIDGETDISPLAY_H_
#define PHILLIB_QT_WIDGETDISPLAY_H_


#include <QtWidgets/QWidget>

namespace phillib
{
namespace qt
{
  class WidgetDisplay : public QWidget
  {
    public:
    WidgetDisplay();
    virtual ~WidgetDisplay(){}
    protected:
      void wheelEvent(QWheelEvent* event)override;
      void paintEvent(QPaintEvent* event)override;
      private:
      QPoint _mousePtr;
      float _scale = 1.0f;
};
}
}
#endif

