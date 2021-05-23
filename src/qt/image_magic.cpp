#include <QtWidgets/QApplication>
#include "ImageMagic.h"
#include <string>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::string str1(argv[1]);
    std::string str2(argv[2]);
    phillib::qt::ImageMagic widget(str1, str2);
    

  return app.exec();
}
