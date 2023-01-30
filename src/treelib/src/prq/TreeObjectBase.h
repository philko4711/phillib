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
    TreeObjectBase(const RegionQ& region);
    virtual ~TreeObjectBase();
    private:
     RegionQ _region;
};
}
}
#endif

