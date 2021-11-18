#include "MainWindow.h"

namespace phillib
{
namespace qt
{
MainWindow::MainWindow():_view(new QGraphicsView(this)), _scene(new GraphScExample(this))
  {
    this->setCentralWidget(_view.get());
    _scene->setSceneRect(0,0,640,480);
    _view->setScene(_scene.get());
  }


}
}
