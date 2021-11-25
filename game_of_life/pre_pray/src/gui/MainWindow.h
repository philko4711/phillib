#ifndef PHILLIB_GAME_OF_LIFE_MAINWINDOW_H_
#define PHILLIB_GAME_OF_LIFE_MAINWINDOW_H_

#include "IObjectMap.h"
#include "ViewerWorld.h"
#include <QtWidgets/QMainWindow>
#include <memory>
namespace phillib
{
namespace game_of_life
{
class MainWindow : public QMainWindow
{
public:
  MainWindow();
  virtual ~MainWindow() {}
  void addItem(std::shared_ptr<QGraphicsItem>& item);//{_gui->scene()->addItem(item.get());}
  // void updateMapObjects(std::vector<std::shared_ptr<IObjectMap> >& mapObjects);
  // void setImageBackground(std::shared_ptr<QImage> image){_gui.setImageBackground(*image);}
private:
  std::unique_ptr<ViewerWorld> _gui;
};
} // namespace game_of_life
} // namespace phillib
#endif
