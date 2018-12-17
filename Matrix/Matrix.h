#include <math.h>
#define EPSILON 1e-10

class MatrixException {
public:
  const char* reason;
  MatrixException():reason("MatrixError"){}
  MatrixException(const char* cause):reason(cause) {}
  const char* getReason() const {return reason;}
};

class Matrix
{
private:
  int m, n;
  double* a;

public:
  //default constructor
  Matrix(): m(1), n(1), a(new double [m*n]) {}

  Matrix(int r, int c): m(r), n(c), a(new double [m*n]) {}

  // copy constructor
  Matrix (const Matrix &b)throw (MatrixException) :m(b.m), n(b.n), a(new double [m*n])  {
    for(int i=0; i<m*n;++i)
      a[i]=b.a[i];
  }

  //move constructor
  Matrix (Matrix &&b):m(b.m), n(b.n), a(new double [m*n]) {
    b.a = 0;
    b.m = 0;
    b.n = 0;
  }

  ~Matrix () {}

  bool operator==(const Matrix & b) const {
    bool isEqual = true;
    if(b.getRaws() == getRaws() && b.getCols() == getCols()) {
      for(int i=0;i<m;++i)
        for(int j=0;j<n;++j)
          if(fabs(at(i,j) - b.at(i,j))>1e-12)
            isEqual = false;
    }
    return isEqual;
  }

  bool operator!=(const Matrix & b) const {
    return !operator==(b);
  }

  Matrix operator*(const Matrix &b) const throw(MatrixException) {
    if(b.getRaws() != getCols())
      throw MatrixException("Number of columns in the 2nd matrix doesn't match number of raws in the 1st");
    Matrix tmpMtrx(getRaws(), b.getCols());
    for(int i=0;i<getRaws();++i)
      for(int j=0;j<b.getCols();++j) {
        tmpMtrx.at(i,j)=0.;
        for(int k=0;k<n;++k){
          //std::cout<<"at("<<i<<","<<j<<")+="<<at(i,k)*b.at(k,j)<<std::endl;
          tmpMtrx.at(i,j) += at(i,k)*b.at(k,j);
        }
      }
    return tmpMtrx;
  }

  Matrix &operator*=(const Matrix &b) throw(MatrixException){
    *this = operator*(b);
    return *this;
  }

  Matrix operator+(const Matrix &b) const throw(MatrixException) {
    Matrix tmpMtrx(m, n);
    if(b.getRaws() == getRaws() && b.getCols() == getCols()) {
      for(int i=0;i<m;++i)
        for(int j=0;j<n;++j)
          tmpMtrx.at(i,j) = at(i,j)+b.at(i,j);
    }
    else throw MatrixException("Number of raws or columns doesn't match");
    return tmpMtrx;
  }

  Matrix &operator+=(const Matrix &b) throw(MatrixException) {
    if(b.getRaws() == getRaws() && b.getCols() == getCols()) {
      for(int i=0;i<m;++i)
        for(int j=0;j<n;++j)
          at(i,j) += b.at(i,j);
    }
    else throw MatrixException("Number of raws or columns doesn't match");
    return *this;
  }

  Matrix operator-(const Matrix &b) const throw(MatrixException) {
    Matrix tmpMtrx(m, n);
    if(b.getRaws() == getRaws() && b.getCols() == getCols()) {
      for(int i=0;i<m;++i)
        for(int j=0;j<n;++j)
          tmpMtrx.at(i,j) = at(i,j)-b.at(i,j);
    }
    else throw MatrixException("Number of raws or columns doesn't match");
    return tmpMtrx;
  }
  Matrix &operator-=(const Matrix &b) throw(MatrixException) {
    if(b.getRaws() == getRaws() && b.getCols() == getCols()) {
      for(int i=0;i<m;++i)
        for(int j=0;j<n;++j)
          at(i,j) -= b.at(i,j);
    }
    else throw MatrixException("Number of raws or columns doesn't match");
    return *this;
  }

 Matrix operator*(double a) const {
    Matrix tempMatrix(m, n);
    for(int i=0;i<m;++i)
      for(int j=0;j<n;++j)
        tempMatrix.at(i,j) = a*at(i,j);
    return tempMatrix;
  }
  Matrix &operator*=(double a) {
    for(int i=0;i<m;++i)
      for(int j=0;j<n;++j)
        at(i,j) *= a;
    return *this;
  }

  Matrix operator/(double a) const throw(MatrixException) {
    if(a==0)
      throw MatrixException("Division by zero");
    return operator*(1/a);
  }
  Matrix &operator/=(double a) throw(MatrixException) {
    if(a==0)
      throw MatrixException("Division by zero");
    return operator*=(1/a);
  }

  static Matrix unitMtrx(int r, int c);
  static Matrix zeroMtrx(int r, int c);

  Matrix &transpose();


  //copy operator
  Matrix &operator=(const Matrix &b) {
    if(m*n < b.m*b.n) {
      delete[] a;
      a = new double [b.m*b.n];
    }
    m = b.m;
    n = b.n;
    for (int i=0;i<m*n;++i)
      a[i] = b.a[i];
    return *this;
  }

  //move operator
  Matrix& operator=(Matrix&& b) {
    int temp = m;
    m = b.m;
    b.m = temp;
    temp = n;
    n = b.n;
    b.n = temp;
    double * tempPointer = a;
    a = b.a;
    b.a = tempPointer;
    return *this;
  }

  double& at(int i, int j) throw (MatrixException){
    if(i>=m || j>=n) throw MatrixException("INDEX OUT OF BOUNDS");
    return a[i*n + j];
  }

  double at(int i, int j) const throw (MatrixException){
    if(i>=m || j>=n) throw MatrixException("INDEX OUT OF BOUNDS");
    return a[i*n + j];
  }

  // indexer
  double *operator[](int i) {
    return a + i*n;
  }

  const double *operator[](int i) const {
    return a + i*n;
  }

  int getRaws() const {
    return m;
  }
  int getCols() const {
    return n;
  }

  void rowReduct();

  Matrix minorMtrx(int r, int c) const ;

  Matrix inverse() throw(MatrixException);
  double det() const throw(MatrixException);

  void fillRand();

  void printMtrx();
};
