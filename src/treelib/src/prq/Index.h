#ifndef PHILLIB_TREELIB_INDEX_H_
#define PHILLIB_TREELIB_INDEX_H_



namespace phillib
{
namespace treelib
{
  class Index
  {
    public:
    Index(const unsigned int u, const unsigned int v);
    virtual ~Index();
    private:
      const unsigned int _u;
      const unsigned int _v;
};
}
}
#endif

