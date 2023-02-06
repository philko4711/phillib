#ifndef PHILLIB_TREELIB_NODE_H_
#define PHILLIB_TREELIB_NODE_H_


#include "TreeObjectBase.h"
#include <vector>

namespace phillib
{
namespace treelib
{
  class Node : public TreeObjectBase, public std::enable_shared_from_this<Node>
  {
    public:
    enum class Succ
    {
      TL = 0,
      TR,
      BL,
      BR
    };
    Node(const std::shared_ptr<RegionQ>& region);
    virtual ~Node(){}
    virtual const Type type()override{return ITreeObject::Type::NODE;}
    virtual std::shared_ptr<ITreeObject> addData(std::shared_ptr<IDataObject>& data)override;
    virtual void print()override;
    private:
      std::shared_ptr<ITreeObject> _successors[4] = {nullptr};
};
}
}
#endif

