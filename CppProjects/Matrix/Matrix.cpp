#include "Matrix.h"
#include <iostream>
Matrix &Matrix::transpose() {
  double temp;
  int tmpRaws;
  if(m > n)
    tmpRaws = n;
  else tmpRaws = m;


  for(int i=0;i<tmpRaws;++i)
    for(int j=0;j<i;++j) {
      temp = at(i,j);
      at(i,j) = at(j,i);
      at(j,i) = temp;
    }
   return *this;
  }

void Matrix::rowReduct() {
  int i = 0;
  int j = 0;
  while (i<m && j<n) {
    double maxEl = 1e-30;
    int indOfMaxEl = -1;
    for(int k=i; k<m;++k){
      if(maxEl < fabs(at(k,j))) {
        maxEl = fabs(at(k,j));
        indOfMaxEl = k;
      }
    }

  if(maxEl<=EPSILON) {
    for(int k=i;k<m;++k)
      at(k,j)=0.;
      ++j;
      continue;
  }
  if(indOfMaxEl != i) {
    for(int l=j;l<n;++l) {
      double temp = at(i,l);
      at(i,l) = -at(indOfMaxEl,l);
      at(indOfMaxEl,l) = temp;
    }
  }
  for(int k = i+1;k<m;++k) {
    double r = at(k,j)/at(i,j);
    at(k,j)=0.;
    for(int l = j+1;l<n;++l) {
      at(k,l) -= r*at(i,l);
    }
  }
  ++i;
  ++j;
}
}

Matrix Matrix::minorMtrx(int r, int c) const {
  Matrix tmpMtrx(m-1,n-1);
  int ki = 0;
  for (int i = 0; i < m; ++i){
      if(i != r){
          for (int j = 0, kj = 0; j < n; ++j){
              if (j != c){
                  tmpMtrx.at(ki,kj)=at(i,j);
                  kj++;
              }
          }
          ki++;
      }
  }
  return tmpMtrx;
}

Matrix Matrix::inverse() throw(MatrixException) {
  double det = Matrix::det();
  if(det==0) throw MatrixException("Division by zero");
  Matrix tmpMtrx(m,m);
  if(n==m) {
    for(int i=0;i<m;++i) {
      for(int j=0;j<m;++j) {
        tmpMtrx.at(i,j)= pow(-1,i+j)*minorMtrx(i,j).det();
      }
    }
  }
  tmpMtrx = tmpMtrx.transpose();
  tmpMtrx/=det;
  return tmpMtrx;
}

double Matrix::det() const throw (MatrixException){
  if(getRaws()!=getCols()) throw MatrixException("Number of columns and raws doesn't match");
  double det = 1;
  Matrix tmpMatrix =  *this;
  tmpMatrix.rowReduct();
  for(int i=0;i<n;++i)
      det*=tmpMatrix.at(i,i);
  return det;
}

void Matrix::fillRand() {
  for(int i =0;i<m;++i)
    for(int j=0;j<n;++j) {
      at(i,j)=rand()%9+1;
    }
}

void Matrix::printMtrx() {
  for(int i=0;i<m;i++){
    for(int j=0;j<n;j++) {
      if(fabs(at(i,j))>EPSILON)
      std::cout<<at(i,j)<<" ";
      else std::cout<<0<<" ";
    }
    std::cout<<std::endl;
  }
}

 static Matrix unitMtrx(int r, int c) {
    Matrix tmpMtrx = Matrix(r,c);
    for(int i =0;i<r;++i)
      for(int j=0;j<c;++j)
        tmpMtrx.at(i,j) = (i==j) ? 1.: 0.;
        return tmpMtrx;
  }
 static Matrix zeroMtrx(int r, int c) {
    Matrix tmpMtrx = Matrix(r,c);
    for(int i =0;i<r;++i)
      for(int j=0;j<c;++j)
        tmpMtrx.at(i,j) = 0.;
        return tmpMtrx;
  }
