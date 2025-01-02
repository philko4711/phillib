#ifndef PHILLIB_CONTENTSNAKE_H_
#define PHILLIB_CONTENTSNAKE_H_



namespace phillib
{
class ContentSnake
  {
    public:
      ContentSnake(const unsigned int col, const unsigned int row):_col(col), _row(row){}
      virtual ~ContentSnake(){};
      const unsigned int col(void)const{return _col;}
      const unsigned int row(void)const{return _row;}
    private:
      const unsigned int _col;
      const unsigned int _row;
  };
}
#endif

