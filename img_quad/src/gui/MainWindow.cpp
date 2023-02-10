#include "MainWindow.h"
#include "SceneImgQuad.h"
namespace phillib
{
namespace img_quad
{
MainWindow::MainWindow()
    : _guiUi(std::make_unique<Ui::MainWindowImgQuad>())
{
  _guiUi->setupUi(this);
  _guiUi->graphicsView->setScene(new SceneImgQuad(this));
}
MainWindow::~MainWindow() {}

} // namespace img_quad
} // namespace phillib
