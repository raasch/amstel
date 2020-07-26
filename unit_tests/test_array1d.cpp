#include <iostream>
#include <utils/array1d.h>
#include <complex.h>

using std::cout;
using std::endl;
using namespace AMSTeL;

int main()
{
  cout << "Testing the Array1D class..." << endl;
  
  Array1D<double> a(5);
  a[0] = 1; a[1] = 2.5;
  cout << "  (size of Array1D(5): " << a.size() << ")" << endl;
  
  a[2]=0;
  a[3]=1;
  a[4]=1.5;
  cout << "-an Array1D<double>(5) a: "  << a << endl;

  Array1D<double> b(a);
  cout << "- copy constructor b(a): " << b << endl;

  b.swap(3,4);
  b.swap(a);
  cout << "- b.swap(3,4) and b.swap(a): " << a << endl;
  
  a.resize(3);
  cout << "- a.resize(3): "  << a << endl;
  
  a=b;
  cout << "- a=b: "  << a << endl;

  typedef std::complex<double> C;
  Array1D<C> c(5);
  c[0]=(3+2);
  c[1]=(1,1);
  c[4]=(0.2,0.5);
  cout << "- an Array1D<complex<double>>(5) c: " << c << endl;
  
  Array1D<C> d(c);
  cout << "- copy constructor d(c): " << d << endl;

  d.swap(3,4);
  d.swap(c);
  cout << "- d.swap(3,4) and d.swap(c): " << c << endl;
  
  c.resize(3);
  cout << "- c.resize(3): "  << c << endl;
  
  return 0;
}
