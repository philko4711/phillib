#ifndef PHILLIB_TREELIB_ITREEOBJECT_H_
#define PHILLIB_TREELIB_ITREEOBJECT_H_

#include <memory>

namespace phillib
{
namespace treelib
{

  class Index;
class RegionQ;
class IDataObject;
class ITreeObject;
  class ITreeObject
  {
    public:
    enum class Type
    {
      NODE = 0,
      LEAF
    };
    ITreeObject(){}
    virtual ~ITreeObject(){}
    virtual const Type type() = 0;
    virtual std::shared_ptr<ITreeObject> addData(std::shared_ptr<IDataObject>& data) = 0;
    virtual bool inside(const Index& index)const = 0;
    virtual const std::shared_ptr<RegionQ>& region()const = 0;
    virtual void print()=0;
};
}
}
#endif

