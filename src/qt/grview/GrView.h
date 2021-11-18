#ifndef PHILLIB_QT_GRVIEW_H_
#define PHILLIB_QT_GRVIEW_H_


#include <QtWidgets/QGraphicsView>

namespace phillib
{
namespace qt
{
  class GrView : public QGraphicsView
  {
    public:
    GrView(QGraphicsScene* scene, QWidget* parent = nullptr);
    virtual ~GrView(){}
    virtual void wheelEvent(QWheelEvent *event)override;//{}
    protected:
      void mousePressEvent(QMouseEvent* event)override;
    private:
};
}
}
#endif

