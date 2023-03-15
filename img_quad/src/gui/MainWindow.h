#ifndef PHILLIB_IMG_QUAD_MAINWINDOW_H_
#define PHILLIB_IMG_QUAD_MAINWINDOW_H_


#include <QtWidgets/QMainWindow>
#include <memory>
#include "ui_main.h"
#include "SceneImgQuad.h"
#include <vector>
#include <memory>

namespace phillib
{
namespace img_quad
{
  class MainWindow : public QMainWindow
  {
    Q_OBJECT
    public:
    enum class Scenes {SCENE_IN = 0,
    SCENE_E,
    SCENE_P,
    SCENE_FI
     };
    MainWindow();
    virtual ~MainWindow();
    private:
    std::unique_ptr<Ui::MainWindowImgQuad> _guiUi;
    std::vector<std::shared_ptr<SceneImgQuad> > _scenes;
};
}
}
#endif

