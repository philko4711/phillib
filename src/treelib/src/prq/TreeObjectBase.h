#ifndef PHILLIB_TREELIB_TREEOBJECTBASE_H_
#define PHILLIB_TREELIB_TREEOBJECTBASE_H_

#include "ITreeObject.h"
#include "RegionQ.h"
#include <memory>
namespace phillib
{
namespace treelib
{
  class Index;
  
  class TreeObjectBase : public ITreeObject
  {
    public:
    TreeObjectBase(const std::shared_ptr<RegionQ>& region);
    virtual ~TreeObjectBase(){}
    virtual const std::shared_ptr<RegionQ>& region()const override{return _region;}
    virtual bool inside(const Index& index)const;
    private:
     const std::shared_ptr<RegionQ> _region = nullptr;
     const std::shared_ptr<Index> _index = nullptr;
};
}
}
#endif

