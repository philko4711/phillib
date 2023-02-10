#ifndef PHILLIB_IMG_QUAD_MAINWINDOW_H_
#define PHILLIB_IMG_QUAD_MAINWINDOW_H_


#include <QtWidgets/QMainWindow>
#include <memory>
#include "ui_main.h"

namespace phillib
{
namespace img_quad
{
  class MainWindow : public QMainWindow
  {
    Q_OBJECT
    public:
    MainWindow();
    virtual ~MainWindow();
    private:
    std::unique_ptr<Ui::MainWindowImgQuad> _guiUi;
};
}
}
#endif

