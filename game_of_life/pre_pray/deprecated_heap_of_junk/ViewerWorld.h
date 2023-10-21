#ifndef PHILLIB_GAME_OF_LIFE_VIEWERWORLD_H_
#define PHILLIB_GAME_OF_LIFE_VIEWERWORLD_H_

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QWidget>


namespace phillib
{
namespace game_of_life
{
  class ViewerWorld : public QGraphicsView
  {
    Q_OBJECT
    public:
    ViewerWorld(QWidget* parent = nullptr);
    virtual ~ViewerWorld(){delete this->scene();}
    protected:
      // virtual void wheelEvent(QWheelEvent *event)override;//{}
      // virtual void mousePressEvent(QMouseEvent* event)override;
      // virtual void mouseMoveEvent(QMouseEvent* event)override;
    private:
};
}
}
#endif

