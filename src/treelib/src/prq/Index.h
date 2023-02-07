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
    virtual ~Index(){}
    const unsigned int u()const{return _u;}
    const unsigned int v()const{return _v;}
    const Index operator+(const Index& var)const{return Index(_u + var._u, _v + var._v);}
    const bool operator>(const Index& var)const{return (_u > var._u) && (_v > var._v);}
    const bool operator<(const Index& var)const{return (_u < var._u) && (_v < var._v);}
    const bool operator==(const Index& var)const{return (_u == var._u) && (_v == var._v);}
    private:
      const unsigned int _u;
      const unsigned int _v;
};
}
}
#endif

