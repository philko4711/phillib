#ifndef PHILLIB_GAME_OF_LIFE_MAINWINDOW_H_
#define PHILLIB_GAME_OF_LIFE_MAINWINDOW_H_


#include <QtWidgets/QMainWindow>
#include <phillib_qt/WidgetImage.h>
#include "IObjectMap.h"
namespace phillib
{
namespace game_of_life
{
  class MainWIndow : public QMainWindow
  {
    public:
    MainWIndow();
    virtual ~MainWIndow();
    void updateMapObjects(const std::vector<IObj)
    private:
      phillib::qt::WidgetImage _gui;
};
}
}
#endif

