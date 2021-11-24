#ifndef PHILLIB_GAME_OF_LIFE_MAINWINDOW_H_
#define PHILLIB_GAME_OF_LIFE_MAINWINDOW_H_


#include <QtWidgets/QMainWindow>
//#include <phillib_qt/WidgetImage.h>
#include "IObjectMap.h"
namespace phillib
{
namespace game_of_life
{
  class MainWindow : public QMainWindow
  {
    public:
    
    MainWindow();
    virtual ~MainWindow(){}
    // void updateMapObjects(std::vector<std::shared_ptr<IObjectMap> >& mapObjects);
    // void setImageBackground(std::shared_ptr<QImage> image){_gui.setImageBackground(*image);}
    private:
  //    phillib::qt::WidgetImage _gui;

};
}
}
#endif

