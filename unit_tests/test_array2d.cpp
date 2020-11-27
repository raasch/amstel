#include <iostream>
#include <utils/array2d.h>

using std::cout;
using std::endl;
using namespace AMSTeL;

int main()
{
 cout << "Testing the Array2D class..." << endl;
  
  Array2D<double> a(3);
  a(0,1) = 1; 
  a(1,0) = 2.5;
  a(1,1) = 1;
  a(2,1) = 1;
  a(2,2) = 1.5;
  cout << "  (size of Array2D(3): " << a.size() << ")"<< endl;
  cout << " number of rows: " << a.row_dimension() << endl;
  cout << " number of columns: " << a.column_dimension() << endl;
  
  cout << "-an Array2D<double>(3) a: "<< endl << a << endl;

  Array2D<double> b(a);
  cout << "- copy constructor b(a): "<< endl << b << endl;
  a(0,0) = 5;
  a(1,2) = 5;
  a(2,2) = 5;
  a(1,0) = 5;
  cout << "- change some values of a: "<< endl << a <<endl;
  b.swap(a);
  cout << "-  b.swap(a): "<< endl << b << endl;
  cout << "- a: " << endl << a << endl;

  a=b;
  cout << "- a=b: "<< endl << a << endl;
  a.resize(1,3);

  cout << "  (size of Array2D(3): " << a.size() << ")"<< endl;
  cout << " number of rows: " << a.row_dimension() << endl;
  cout << " number of columns: " << a.column_dimension() << endl;
  cout << "- a.resize(1,3): "<< endl << a << endl;

}