#ifndef PHILLIB_TREELIB_REGIONQ_H_
#define PHILLIB_TREELIB_REGIONQ_H_

#include "Index.h"

namespace phillib
{
namespace treelib
{
  class RegionQ
  {
    public:
    RegionQ(const Index& tl, const unsigned int lengthEdge);
    virtual ~RegionQ(){}
    const Index& tl()const{return _tl;}
    const unsigned int lengthEdge()const{return _lengthEdge;}
    private:
    const Index _tl;
    const unsigned int _lengthEdge;
};
}
}
#endif

