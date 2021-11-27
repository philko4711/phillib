#include "PredPray.h"
#include <QtCore/QDebug>
#include <phillib_utils/random.h>
#include "IObjectMap.h"
#include "Food.h"

namespace phillib
{
namespace game_of_life
{
PredPray::PredPray():_map(100, 100)
{ 
  _gui.resize(1000, 1000);
  _gui.show();
  for(unsigned int i = 0; i < 10; i++)
    this->seedFoodRandom();
    _timerMain.start(1000);
  connect(&_timerMain, SIGNAL(timeout()), this, SLOT(loopMain()));
  // auto food = std::shared_ptr<IObjectMap>( new Food);
  // if(_map.set(QPointF(100, 100), food))
  // {
  //   auto ptr = food->item();
  //    _gui.addItem(ptr);
  //     _food.push_back(food);
  // }
  // else
  //   qDebug() << __PRETTY_FUNCTION__ << "putting food failed";
 
  // _gui.update();
 
  //_timerMain.start(20);
  //_gui.updateMapObjects();
  this->loopMain();
}

void PredPray::seedFoodRandom()
{
   const QRect &sizeMap = _map.sizeMap();
   std::vector<float> valsX;
   phillib::utils::randomReal(1, valsX, 0.0f, static_cast<float>(sizeMap.width()));
   std::vector<float> valsY;
   phillib::utils::randomReal(1, valsY, 0.0f, static_cast<float>(sizeMap.height()));
   const QPointF pos(*valsX.begin(), *valsY.begin());
   auto food = std::shared_ptr<IObjectMap>(new Food);
   if(_map.set(pos, food))
   {
    auto ptr = food->item();
     _gui.addItem(ptr);
      _food.push_back(food);
   }
  // qDebug() << __PRETTY_FUNCTION__ << " creating food at " << pos;
}

void PredPray::loopMain()
{

  // qDebug() << __PRETTY_FUNCTION__ << "";
  // std::vector<std::shared_ptr<IObjectMap>> mapObjects;
  // std::vector<std::vector<std::shared_ptr<Food>>::iterator> toDelete;
  // std::vector<QPoint> seed;
  // // qDebug() << __PRETTY_FUNCTION__ << "foood size " << _food.size();
  // auto iter = _food.begin();
   for (auto iter = _food.begin(); iter < _food.end(); iter++) 
   {
     auto food = std::dynamic_pointer_cast<Food>(*iter);
     const unsigned int amount = food->wither();
     if (amount <= 1)
      _food.erase(iter);
   }
  //   std::vector<std::weak_ptr<IObjectMap>> adj;
  //   _map.adjacent(adj, (*iter)->pos());
  //   unsigned int ctr = 0;
  //   for (auto &oter : adj)
  //     if (oter.lock())
  //       ctr++;
  //   unsigned int amount = (*iter)->wither(ctr);
  //   if (amount <= 1) {
  //     // qDebug() << __PRETTY_FUNCTION__ << "todelete";
  //     // toDelete.push_back(iter);
  //     seed.push_back((*iter)->pos());
  //     _food.erase(iter);

  //   } else
  //     mapObjects.push_back(*iter);
  // }
  // qDebug() << __PRETTY_FUNCTION__ << " 2";
  // if (toDelete.size()) {
  //   qDebug() << __PRETTY_FUNCTION__ << toDelete.size() <<" to clear ";
  //   //for (auto& iter : toDelete)
  //   for(unsigned int i = 0;  i< toDelete.size(); i++)
  //   {
  //     auto iter = toDelete[i];
  //     //qDebug() << __PRETTY_FUNCTION__ << "spawning & deleteing  for  " << ;
  //     auto pos = (*iter)->pos();
  //     qDebug() << __PRETTY_FUNCTION__ << " spawning & deleteing  for pos " <<
  //     pos; for (int i = pos.y() - 1; i <= pos.y() + 1; i++) {
  //       for (int j = pos.x() - 1; j <= pos.x() + 1; j++) {
  //         auto mapSize = _map.sizeMap();
  //         if (((i == pos.y()) && j == pos.x()) || i < 0 ||
  //             j < 0 || i >= _map.sizeMap().height() ||
  //             j >= _map.sizeMap().width())
  //           continue;
  //         auto ptr = std::make_shared<Food>(QPoint(j, i));
  //         _map.set(QPoint(j, i), ptr);
  //         mapObjects.push_back(ptr);
  //         _food.push_back(ptr);
  //       }

  //     }
  //   //  qDebug() << __PRETTY_FUNCTION__ << " to erase : " << (*iter)->pos();
  //     _food.erase(toDelete[i]);
  //   }
  // qDebug() << __PRETTY_FUNCTION__ << "3";
  // for (auto &iter : seed) {
  //   auto pos = iter;
  //   // qDebug() << __PRETTY_FUNCTION__ << " spawning for pos " << pos;
  //   for (int i = pos.y() - 1; i <= pos.y() + 1; i++) {
  //     for (int j = pos.x() - 1; j <= pos.x() + 1; j++) {
  //       auto mapSize = _map.sizeMap();
  //       if (((i == pos.y()) && j == pos.x()) || i < 0 || j < 0 ||
  //           i >= _map.sizeMap().height() || j >= _map.sizeMap().width())
  //         continue;
  //       if (_map.get(QPoint(j, i)))
  //         continue;
  //       auto ptr = std::make_shared<Food>(QPoint(j, i));
  //       _map.set(QPoint(j, i), ptr);
  //       mapObjects.push_back(ptr);
  //       _food.push_back(ptr);
  //     }
  //   }
  // }
  // qDebug() << __PRETTY_FUNCTION__ << "4";
  // for (auto &iter : _agents) {
  //   iter->iterate();
  //   mapObjects.push_back(std::dynamic_pointer_cast<IObjectMap>(iter));
  // }
  // // qDebug() << __PRETTY_FUNCTION__ << " update gui iwth " <<
  // // mapObjects.size();
  // _gui.updateMapObjects(mapObjects);
  //_gui.setImageBackground(_map.imageMap());
  _gui.update();
} // namespace game_of_life
} // namespace game_of_life
} // namespace phillib
