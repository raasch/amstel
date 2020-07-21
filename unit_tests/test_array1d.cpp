#include <iostream>
#include <utils/array1d.h>

using std::cout;
using std::endl;
using namespace AMSTeL;

int main()
{
  cout << "Testing the Array1D class..." << endl;
  Array1D<double> a(2);
  a[0] = 1; a[1] = 2.5;
  cout << "- an Array1D<double>(2): " << a << endl;

  return 0;
}
