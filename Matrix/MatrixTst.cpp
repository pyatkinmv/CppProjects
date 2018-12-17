#include "Matrix.h"
#include <iostream>
#include <cstdlib>
int main()
{
  try{
  Matrix a(5,5);
  Matrix b(5,6);

  a.fillRand();
  b.fillRand();

  std::cout<<"Matrix a:"<<std::endl;
  a.printMtrx();

  std::cout<<"Matrix b:"<<std::endl;
  b.printMtrx();

  std::cout<<"Transposed matrix a:"<<std::endl;
  a.transpose().printMtrx();

  int alpha=rand()%10+1;
  std::cout<<"Matrix a*"<<alpha<<": "<<std::endl;
  (a*alpha).printMtrx();

  std::cout<<"Matrix b/"<<alpha<<": "<<std::endl;
  (b/alpha).printMtrx();

  std::cout<<"Matrix a*b:"<<std::endl;
  (a*b).printMtrx();

  std::cout<<"Determinant a:"<<std::endl;
  std::cout<<a.det()<<std::endl;

  int row = rand()%5;
  int col = rand()%5;
  std::cout<<"a.minor("<<row<<","<<col<<")"<<std::endl;
  a.minorMtrx(row,col).printMtrx();

  std::cout<<"Inversed matrix a:"<<std::endl;
  a.inverse().printMtrx();

  Matrix tmpMtrx = a;
  std::cout<<"Row reducted matrix a:"<<std::endl;
  tmpMtrx.rowReduct();
  tmpMtrx.printMtrx();

  std::cout<<"Matrix a*a^(-1):"<<std::endl;
  tmpMtrx = a.inverse();
  (a*tmpMtrx).printMtrx();

} catch(MatrixException e) {
  std::cout<<"ERROR OCCURED: "<<e.getReason()<<std::endl;
}

return 0;
}
