#ifndef PHILLIB_PHILLI_TREELIB_DATAOBJECTPOINT_H_
#define PHILLIB_PHILLI_TREELIB_DATAOBJECTPOINT_H_


#include "DataObjectBase.h"
#include "Point.h"
#include <cmath>


namespace phillib
{

namespace treelib
{
  class Index;
  class DataObjectPoint : public DataObjectBase
  {
    public:
    DataObjectPoint(const Point& point);
    virtual ~DataObjectPoint(){}
    virtual const Index index(void)const{return Index(static_cast<unsigned int>(std::floor(_point.x() / _resolution)), static_cast<unsigned int>(std::floor(_point.y() / _resolution)));}    
    private:
      Point _point;
      const float _resolution = 0.10f;   //toDo: later, this parameter will be set in the main tree class

};
}
}
#endif

