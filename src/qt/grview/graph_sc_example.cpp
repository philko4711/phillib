#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "GrView.h"
#include "GraphScExample.h"



int main(int argc, char** argv)
{
  QApplication app(argc, argv);

phillib::qt::GraphScExample scene;//(0.0, 0.0, 1000.0, 1000.0);
QPixmap pixmap("/home/phil/Pictures/hass.jpg");

// scene.addPixmap(pixmap);
// scene.addText("Hello, world!");

phillib::qt::GrView view(&scene);
scene.addPixmap(pixmap);
view.show();


  // phillib::qt::MainWindow gui;
  // gui.show();
  return app.exec();
}
