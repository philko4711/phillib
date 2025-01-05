#ifndef PHILLIP_SNAKEGUI_H_
#define PHILLIP_SNAKEGUI_H_

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsRectItem>
#include "ui_snake.h"
#include "ContentSnake.h"
#include <memory>
#include <vector>
#include <phillib_utils/Fifo.h>
namespace phillib
{
  class SnakeGui : public QMainWindow
  {
    Q_OBJECT
    public:
      SnakeGui();
      virtual ~SnakeGui(){}
      void updateDisplay(const utils::Fifo<ContentSnake>& content, const ContentSnake& food);
      bool rmPixel(const unsigned int col, const unsigned int row);
      void rmAllPixels();
    signals:
      void key(int key);  
    protected:
      void keyPressEvent(QKeyEvent* event)override;  
    private:
      bool addPixel(const unsigned int col, const unsigned int row);
      bool pixel(const unsigned int col, const unsigned int row);
      std::unique_ptr<Ui::MainWindow> _guiUi;
      std::vector<std::shared_ptr<QGraphicsRectItem> > _pixelsActive;
};
}
#endif

