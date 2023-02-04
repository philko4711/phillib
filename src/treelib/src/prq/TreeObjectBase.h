#ifndef PHILLIB_TREELIB_TREEOBJECTBASE_H_
#define PHILLIB_TREELIB_TREEOBJECTBASE_H_

#include "ITreeObject.h"
#include "RegionQ.h"
namespace phillib
{
namespace treelib
{
  class TreeObjectBase : public ITreeObject
  {
    public:
    TreeObjectBase(const std::shared_ptr<RegionQ>& region);
    virtual ~TreeObjectBase(){}
    virtual const std::shared_ptr<RegionQ>& region()const{return _region;}
    private:
     const std::shared_ptr<RegionQ> _region = nullptr;
};
}
}
#endif

