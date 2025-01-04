#ifndef PHILLIB_SNAKE_H_
#define PHILLIB_SNAKE_H_

#include "gui/SnakeGui.h"
#include "ContentSnake.h"
#include <phillib_utils/Fifo.h>
#include <QtCore/QObject>
#include <QtCore/QTimer>

namespace phillib
{
  
  class Snake : public QObject
  {
    Q_OBJECT
    public:
      enum class MoveEn
      {
        RIGHT = 0,
        LEFT,
        TOP,
        DOWN
      };
      Snake();
      virtual ~Snake(){}
      bool move(const MoveEn& dir);
      void eat(const unsigned int col, const unsigned int row);
      const bool collision(ContentSnake& posNew)const;
     private slots:
        void callBackTimerMain();
        void key(int key);
    private:
      utils::Fifo<ContentSnake> _content;
      SnakeGui _gui;
      QTimer _timerMain;
      MoveEn _dir = MoveEn::RIGHT;
};
}
#endif

