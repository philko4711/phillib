#ifndef PHILLIB_FRACTALLAB_H_
#define PHILLIB_FRACTALLAB_H_

#include <QtWidgets/QMainWindow>
#include "ui_main.h"
#include <memory>
#include "../fractals/FractalTree.h"
namespace phillib
{
  
  class FractalLab : public QMainWindow
  {
  public:
    
    virtual ~FractalLab(){}
    static FractalLab& instance();
    void addItem(std::shared_ptr<QGraphicsItem>& item);
    void setTree(FractalTree* tree){_tree = tree;}
    void iterate(){_tree->iterate();}
  private:
  FractalLab();
  
  std::unique_ptr<Ui::MainWindow> _guiUi;
  static std::unique_ptr<FractalLab> _instance;
  std::vector<std::shared_ptr<QGraphicsItem> > _items;
  FractalTree* _tree;
  };
}
#endif
