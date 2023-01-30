#ifndef PHILLIB_TREELIB_REGIONQ_H_
#define PHILLIB_TREELIB_REGIONQ_H_



namespace phillib
{
namespace treelib
{
  class RegionQ
  {
    public:
    RegionQ(const unsigned int lengthEdge);
    virtual ~RegionQ(){}
    private:
    const unsigned int _lengthEdge;
};
}
}
#endif

