#include <QApplication>
#include "gui/MainWindowLab.h"

int main(int argc, char**argv)
{
QApplication app(argc, argv);
MainWindowLab lab;
lab.show();

  return app.exec();
}
