#ifndef PHILLIB_GRAPHICSVIEW_H_
#define PHILLIB_GRAPHICSVIEW_H_


#include <QtWidgets/QGraphicsView>

namespace phillib
{
  class GraphicsView : public QGraphicsView
  {
    Q_OBJECT
    public:
    GraphicsView(QWidget* parent = nullptr);
    virtual ~GraphicsView(){}
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    protected:

    private:
};
}
#endif

