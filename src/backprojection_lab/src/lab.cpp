#include <QApplication>
#include "gui/QvtkWidget.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  QvtkWidget widget;
  std::vector<QColor> colors;
  stdVecEig3d centers;
  const double size = 1.0;
  for(unsigned int i = 0; i < 10; i++)  
    for(unsigned int j = 0; j < 10; j++)  
      for(unsigned int k = 0; k < 10; k++)  
    {
      Eigen::Vector3d center(static_cast<double>(j) * size, static_cast<double>(i) * size, static_cast<double>(k) * size);
      centers.push_back(center);
      colors.push_back(Qt::red);
    }
    widget.drawAxissystem();
    widget.drawCubeArray(colors, centers, size);
    widget.clearCubeArray();
  widget.show();
  return app.exec();
}
