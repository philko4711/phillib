#ifndef PHILLIB_TREELIB_POINT_H_
#define PHILLIB_TREELIB_POINT_H_



namespace phillib
{
namespace treelib
{
  class Point
  {
    public:
    Point(const float& x, const float& y);
    virtual ~Point(){}
    const float& x(void)const{return _x;}
    const float& y(void)const{return _y;}
    private:
      float _x;
      float _y;
};
}
}
#endif

