#ifndef PHILLIB_TREELIB_IDATAOBJECT_H_
#define PHILLIB_TREELIB_IDATAOBJECT_H_

#include <memory>

namespace phillib
{
namespace treelib
{
  class IDataObject
  {
    public:
    IDataObject();
    virtual ~IDataObject();
    virtual std::shared_ptr<IDataObject>&  addData(const std::shared_ptr<IDataObject>& data) = 0;
};
}
}
#endif

