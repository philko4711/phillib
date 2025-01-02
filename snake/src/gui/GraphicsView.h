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
    protected:

    private:
};
}
#endif

