#include "DataObjectPoint.h"
#include "Index.h"
#include <cmath>
namespace phillib
{
namespace treelib
{
DataObjectPoint::DataObjectPoint(const Point& point):DataObjectBase(this->index()),_point(point)
  {
    
  }

// const Index DataObjectPoint::index(void)const
// {
//   const unsigned int u = ;
//   const unsigned int v = ;
  
// }

}
}
