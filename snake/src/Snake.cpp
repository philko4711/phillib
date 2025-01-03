#include "Snake.h"
#include <QtCore/QDebug>

namespace phillib
{
  Snake::Snake():_content(4)
  {  
    _gui.show();
    connect(&_timerMain, SIGNAL(timeout()), this, SLOT(callBackTimerMain()));
    connect(&_gui, SIGNAL(key(int)), this, SLOT(key(int)));
    _timerMain.start(100);
    _content.add(ContentSnake(3, 3));
    _content.add(ContentSnake(4, 3));
    _content.add(ContentSnake(5, 3));    
  }

  void Snake::callBackTimerMain()
  {
    qDebug() << __PRETTY_FUNCTION__ << "(line 13, Snake.cpp)";
    this->move(_dir);
    _gui.updateDisplay(_content);
  }

  bool Snake::move(const MoveEn& dir)
  {
    const ContentSnake tip = _content[0];
    const ContentSnake bot = _content[_content.size() - 1];
    for(unsigned int i = 0; i < _content.size(); i++)
       qDebug() << __PRETTY_FUNCTION__ << "El " << i << " (c/r) " << _content[i].col() << "/" << _content[i].row();   
    //abort();
    //_gui.rmPixel(bot.col(), bot.row());
    qDebug() << __PRETTY_FUNCTION__ << "Tip (c/r) " << tip.col() << "/" << tip.row();
    qDebug() << __PRETTY_FUNCTION__ << "Bot (c/r) " << bot.col() << "/" << bot.row();
    switch(dir)
    {
      case MoveEn::RIGHT:
        _content.add(ContentSnake(bot.col() + 1, bot.row()));
        break;
      case MoveEn::LEFT:
        _content.add(ContentSnake(bot.col() - 1, bot.row()));
        break;
      case MoveEn::TOP:
        _content.add(ContentSnake(bot.col(), bot.row()  - 1));
        break;
      case MoveEn::DOWN:
        _content.add(ContentSnake(bot.col(), bot.row()  + 1));
        break;      
      default:
        qDebug() << __PRETTY_FUNCTION__ << "unknkown movement should not happen (line 28, Snake.cpp)";  
        break;
    }
    return true;
  }

  void Snake::key(int key)
  {
    switch(key)
    {
    case Qt::Key_W:
      _dir = MoveEn::TOP;
      break;
    case Qt::Key_A:
      _dir = MoveEn::LEFT;
      break;
    case Qt::Key_D:
      _dir = MoveEn::RIGHT;
      break;  
    case Qt::Key_S:
        _dir = MoveEn::DOWN;
      break;
    default:
      break;   //all other keys are ignored  
    }
    // this->move(_dir);
    // _gui.updateDisplay(_content);
  }
}
