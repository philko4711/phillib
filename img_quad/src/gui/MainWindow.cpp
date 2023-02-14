#include "MainWindow.h"

#include <memory>
#include <QtGui/QImage>

#include <iostream>
namespace phillib
{
namespace img_quad
{
MainWindow::MainWindow()
    : _guiUi(std::make_unique<Ui::MainWindowImgQuad>()),_scenes(4, nullptr)
{
  _guiUi->setupUi(this);
  
  auto img = std::make_shared<QImage>("/home/phil/Pictures/.hin.jpg");
  auto img2 = std::make_shared<QImage>("/home/phil/Pictures/.puss.jpg");
  auto img3 = std::make_shared<QImage>("/home/phil/Pictures/.mast.jpg");
  auto img4 = std::make_shared<QImage>("/home/phil/Pictures/.ass.png");
  std::cout << __PRETTY_FUNCTION__ << " instanciate scenes" << std::endl;
  for(unsigned int i = 0; i < 4; i++)
    _scenes[i] = std::make_shared<SceneImgQuad>(this);

  
  _scenes[static_cast<unsigned int>(Scenes::SCENE_IN)]->setImage(img);
  _scenes[static_cast<unsigned int>(Scenes::SCENE_E)]->setImage(img2);
  _scenes[static_cast<unsigned int>(Scenes::SCENE_P)]->setImage(img3);
  _scenes[static_cast<unsigned int>(Scenes::SCENE_FI)]->setImage(img4);
  
  _guiUi->graphicsView_in->setScene(_scenes[static_cast<unsigned int>(Scenes::SCENE_IN)].get());
  _guiUi->graphicsView_fil->setScene(_scenes[static_cast<unsigned int>(Scenes::SCENE_E)].get());
  _guiUi->graphicsView_pcl->setScene(_scenes[static_cast<unsigned int>(Scenes::SCENE_P)].get());
  _guiUi->graphicsView_fin->setScene(_scenes[static_cast<unsigned int>(Scenes::SCENE_FI)].get());
  
  this->update();
}
MainWindow::~MainWindow() {}

} // namespace img_quad
} // namespace phillib
