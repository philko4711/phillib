#include "MainWindow.h"
#include <QtCore/QDebug>

namespace phillib
{
namespace qt
{
MainWindow::MainWindow():_scene(new GraphScExample(this)), _view(new GrView(_scene.get()))
  {
    QPixmap pixmap("/home/phil/Pictures/hass.jpg");
    this->setCentralWidget(_view.get());
    _scene->setSceneRect(0,0,640,480);
   // _view->setScene(_scene.get());
  }

// void MainWindow::wheelEvent(QWheelEvent *event)
// {
//   event->accept();
//   //qDebug() << __PRETTY_FUNCTION__ << "";
//   //_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//   _view->centerOn(event->pos());
//     qreal delta = 1 + (event->delta() > 0 ? 0.1 : -0.1);
//     _view->scale(delta, delta);
  
// }
}
}
