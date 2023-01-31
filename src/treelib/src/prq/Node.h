#ifndef PHILLIB_TREELIB_NODE_H_
#define PHILLIB_TREELIB_NODE_H_


#include "TreeObjectBase.h"

namespace phillib
{
namespace treelib
{
  class Node : public TreeObjectBase
  {
    public:
    Node(const RegionQ& region);
    virtual ~Node(){}
    virtual const Type type()override{return ITreeObject::Type::NODE;}
    virtual std::shared_ptr<ITreeObject> addData(std::shared_ptr<IDataObject>& data)override;
};
}
}
#endif

