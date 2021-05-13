#include <QtWidgets/QApplication>
//#include <QtWidgets/QScrollArea>
//#include <phillib_qt/WidgetImage.h>
#include "WidgetDisplay.h"

int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    phillib::qt::WidgetDisplay display;
    display.loadImage("/home/phil/Pictures/dicpr.jpeg");
    display.show();
    // phillib::qt::WidgetImage widget;
    // widget.resize(500, 500);
    // QVector<QRect> rects;
    // rects.push_back(QRect(250, 250, 200, 200));
    // widget.setRects(rects);
    // widget.update();
    // //widget.show();
    // QScrollArea scrollArea;
    // scrollArea.setBackgroundRole(QPalette::Dark);
    // scrollArea.setWidget(&widget);
    //scrollArea.show();

    return app.exec();
}