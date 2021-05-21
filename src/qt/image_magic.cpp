#include <QtWidgets/QApplication>
#include "ImageMagic.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    phillib::qt::ImageMagic widget;
    

  return app.exec();
}
