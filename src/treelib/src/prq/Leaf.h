#ifndef PHILLIB_TREELIB_LEAF_H_
#define PHILLIB_TREELIB_LEAF_H_


#include "TreeObjectBase.h"
#include <memory>

class RegionQ;
class IDataObject;

namespace phillib
{
namespace treelib
{
  class Leaf : public TreeObjectBase, public std::enable_shared_from_this<Leaf>
  {
    public:
    Leaf(const RegionQ& region);
    virtual ~Leaf(){}
    virtual const Type type()override{return ITreeObject::Type::LEAF;}
    const bool empty(void)const{return _data == nullptr;}
    virtual std::shared_ptr<ITreeObject> addData(std::shared_ptr<IDataObject>& data)override;
    private:
      std::shared_ptr<IDataObject> _data = nullptr;
};
}
}
#endif
