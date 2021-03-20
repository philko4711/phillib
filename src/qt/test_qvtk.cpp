#include <QtWidgets/QApplication>
#include "WidgetQvtk.h"

int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    phillib::qt::WidgetQvtk viewer;
    viewer.show();
    return app.exec();
}