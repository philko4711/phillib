#include "Node.h"
#include "Leaf.h"
#include "IDataObject.h"
#include "RegionQ.h"
#include "Index.h"
namespace phillib
{
namespace treelib
{
Node::Node(const std::shared_ptr<RegionQ>& region):TreeObjectBase(region) 
{
  //todo: this constructor should split the given region / 4 -> methd in RegionQ
  const unsigned int lengthEdge = region->lengthEdge() / 4;
  const Index tl = region->tl();
  const Index tr = region->tl() + Index(lengthEdge, 0);
  const Index bl = region->tl() + Index(0, lengthEdge);
  const Index br = region->tl() + Index(lengthEdge, lengthEdge);
  _successors[static_cast<unsigned int>(Node::Succ::TL)] = std::make_shared<Leaf>(RegionQ(tl, lengthEdge));
  _successors[static_cast<unsigned int>(Node::Succ::TR)] = std::make_shared<Leaf>(RegionQ(tr, lengthEdge));
  _successors[static_cast<unsigned int>(Node::Succ::BL)] = std::make_shared<Leaf>(RegionQ(bl, lengthEdge));
  _successors[static_cast<unsigned int>(Node::Succ::BR)] = std::make_shared<Leaf>(RegionQ(br, lengthEdge));
}

std::shared_ptr<ITreeObject> Node::addData(std::shared_ptr<IDataObject>& data)
{
  const Index& idx = data->index();
  for(unsigned int i = static_cast<unsigned int>(Node::Succ::TL); i <= static_cast<unsigned int>(Node::Succ::BR); i++)
    if(_successors[i]->inside(idx))
      _successors[i]->addData(data);
  return shared_from_this();    
}

} // namespace treelib
} // namespace phillib
