#ifndef PHILLIB_TREELIB_IDATAOBJECT_H_
#define PHILLIB_TREELIB_IDATAOBJECT_H_

#include <memory>
#include "RegionQ.h"

class Index;

namespace phillib
{
namespace treelib
{
  class IDataObject
  {
    public:
    IDataObject(){}
    virtual ~IDataObject(){}
    //virtual std::shared_ptr<IDataObject>&  addData(const std::shared_ptr<IDataObject>& data) = 0;
    virtual bool in(const RegionQ& region)const=0;
    virtual const Index index(void)const=0;
};
}
}
#endif

