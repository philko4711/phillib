#ifndef PHILLIB_CONTENTSNAKE_H_
#define PHILLIB_CONTENTSNAKE_H_



namespace phillib
{
class ContentSnake
  {
    public:
      ContentSnake(const unsigned int col, const unsigned int row):_col(col), _row(row){}
      ContentSnake(void):_col(0), _row(0){}
      virtual ~ContentSnake(){};
      const unsigned int col(void)const{return _col;}
      const unsigned int row(void)const{return _row;}
      const bool operator==(const ContentSnake& var){return var.col() == this->col() && var.row() == this->row();}
    private:
      unsigned int _col;
      unsigned int _row;
  };
}
#endif

