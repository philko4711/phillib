#include "Snake.h"
#include <QtCore/QDebug>
#include <iostream>
#include <random>

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
    this->createFood();   
  }

  void Snake::callBackTimerMain()
  {
    //qDebug() << __PRETTY_FUNCTION__ << "(line 13, Snake.cpp)";
    this->move(_dir);
    _gui.updateDisplay(_content, _food);
  }

  bool Snake::move(const MoveEn& dir)
  {
    const ContentSnake tip = _content[0];
    const ContentSnake bot = _content[_content.size() - 1];
    // for(unsigned int i = 0; i < _content.size(); i++)
    //    qDebug() << __PRETTY_FUNCTION__ << "El " << i << " (c/r) " << _content[i].col() << "/" << _content[i].row();   
    //abort();
    //_gui.rmPixel(bot.col(), bot.row());
    // qDebug() << __PRETTY_FUNCTION__ << "Tip (c/r) " << tip.col() << "/" << tip.row();
    // qDebug() << __PRETTY_FUNCTION__ << "Bot (c/r) " << bot.col() << "/" << bot.row();
    // unsigned int botLastCol = bot.col();
    // unsigned int botLastRow = bot.row();
    unsigned int botNewCol = 0;
    unsigned int botNewRow= 0;
    switch(dir)
    {
      case MoveEn::RIGHT:
        if(bot.col() + 1 > 15)
          botNewCol = 0;
        else
          botNewCol = bot.col() + 1;  
        //_content.add(ContentSnake(bot.col() + 1, bot.row()));
        botNewRow = bot.row();
        break;
      case MoveEn::LEFT:
        if(bot.col() - 1 == 0)
          botNewCol = 15;
        else
          botNewCol = bot.col() - 1;
        botNewRow = bot.row();  
        //_content.add(ContentSnake(bot.col() - 1, bot.row()));
        break;
      case MoveEn::TOP:
        if(bot.row() - 1 == 0)
          botNewRow = 15;
        else
          botNewRow = bot.row() - 1;
        botNewCol = bot.col();  
        //_content.add(ContentSnake(bot.col(), bot.row()  - 1));
        break;
      case MoveEn::DOWN:
        if(bot.row() + 1 > 15)
          botNewRow = 0;
        else
          botNewRow = bot.row() + 1;
        //_content.add(ContentSnake(bot.col(), bot.row()  + 1));
        botNewCol = bot.col();  
        break;      
      default:
        qDebug() << __PRETTY_FUNCTION__ << "unknkown movement should not happen (line 28, Snake.cpp)";  
        break;
    }
    ContentSnake posNew(botNewCol, botNewRow);
    if(this->collision(posNew))
    {
      std::cout << __PRETTY_FUNCTION__ << "too bad " << std::endl;
      std::abort();
    }
    else if(posNew == _food)
    {
      std::cout << __PRETTY_FUNCTION__ << "eat bitch! " << std::endl;
      this->eat();
    }
    _content.add(posNew);
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

  const bool Snake::collision(ContentSnake& posNew)const
  {
    for(unsigned int i = 0; i < _content.size(); i++)
    {
      if(posNew == _content[i])
        return true;
    }
    return false;
  }

  void Snake::createFood()
  {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist(0,15); 
    while(1)
    {
      ContentSnake food(static_cast<unsigned int>(dist(rng)), static_cast<unsigned int>(dist(rng)));
      if(!this->collision(food))
      {
        _food = food;
        return;
      }
    }
  }

  void Snake::eat()
  {
    // unsigned int sizeOld = _content.size();
    // std::cout << __PRETTY_FUNCTION__ << "sizeOld" << sizeOld <<std::endl;
    // sizeOld++;
    // std::cout << __PRETTY_FUNCTION__ << "size new " << sizeOld << std::endl;
    _content.setSize(_content.sizeMax() + 1); 
    _content.add(_food);
    this->createFood();
    std::cout << __PRETTY_FUNCTION__ << "snake size " << _content.size() << std::endl;
  }
}
