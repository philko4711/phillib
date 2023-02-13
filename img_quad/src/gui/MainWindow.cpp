#include "MainWindow.h"
#include "SceneImgQuad.h"
#include <memory>
#include <QtGui/QImage>
namespace phillib
{
namespace img_quad
{
MainWindow::MainWindow()
    : _guiUi(std::make_unique<Ui::MainWindowImgQuad>())
{
  _guiUi->setupUi(this);
  _guiUi->graphicsView->setScene(new SceneImgQuad(this));
  auto img = std::make_shared<QImage>("/home/phil/Pictures/.hin.jpg");
  auto scene0 = new SceneImgQuad(this);
  auto scene1 = new SceneImgQuad(this);
  auto scene2 = new SceneImgQuad(this);
  
  scene0->setImage(img);
  scene1->setImage(img);
  scene2->setImage(img);
  _guiUi->graphicsView->setScene(scene0);
  _guiUi->graphicsView_2->setScene(scene1);
  _guiUi->graphicsView_3->setScene(scene2);
  this->update();
}
MainWindow::~MainWindow() {}

} // namespace img_quad
} // namespace phillib
