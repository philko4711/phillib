#ifndef PHILLIB_QT_MAINWINDOW_H_
#define PHILLIB_QT_MAINWINDOW_H_


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>
#include "GraphScExample.h"
#include <memory>
namespace phillib
{
namespace qt
{
  class MainWindow : public QMainWindow
  {
    public:
    MainWindow();
    virtual ~MainWindow(){}
    private:
    std::unique_ptr<QGraphicsView> _view;
    std::unique_ptr<GraphScExample> _scene;
};
}
}
#endif

