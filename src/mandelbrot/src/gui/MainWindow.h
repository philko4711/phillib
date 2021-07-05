#ifndef PHILLIB_QT_MAINWINDOW_H_
#define PHILLIB_QT_MAINWINDOW_H_


#include <QtWidgets/QMainWindow>
#include "ui_main_window.h"
#include <memory>
#include <QtGui/QWheelEvent>
#include <QtCore/QPointF>
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
    void drawImage(const QImage& image){_guiUi->widget->setImageBackground(image);}
    void wheelEvent(QWheelEvent* event)override;
    signals:
      void magnify(const QPoint& deltaCenter, const QPoint& deltaMagnify);
    private:
      std::unique_ptr<Ui::MainWindow> _guiUi;
      QPointF _center = QPointF(0.0, 0.0);
};
}
}
#endif

