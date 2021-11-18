#ifndef PHILLIB_QT_MAINWINDOW_H_
#define PHILLIB_QT_MAINWINDOW_H_


#include <QtWidgets/QMainWindow>
#include "GrView.h"
#include "GraphScExample.h"
#include <memory>
namespace phillib
{
namespace qt
{
  class MainWindow : public QMainWindow
  {
    Q_OBJECT
    public:
    MainWindow();
    virtual ~MainWindow(){}
    protected:
//      virtual void wheelEvent(QWheelEvent *event)override;
    private:
      std::unique_ptr<GraphScExample> _scene;
    std::unique_ptr<GrView> _view;
  
};
}
}
#endif

