#include <QtWidgets/QApplication>
#include "TestQvtk.h"

int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    phillib::qt::TestQvtk test;
    // WidgetNewQvtk viewer;
    // viewer.addAxes();
    // pcl::PointCloud<pcl::PointXYZ> cloud;
    // for(unsigned int i = 0; i < 1000; i++)
    //     for(unsigned int j = 0; j < 1000; j++)
    //         cloud.push_back(pcl::PointXYZ(static_cast<float>(i) * 0.01f, static_cast<float>(j) * 0.01f, 0.0f));
    // viewer.drawPoints(cloud);
    // viewer.show();
    return app.exec();
}