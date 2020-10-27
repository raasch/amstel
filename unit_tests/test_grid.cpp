#include <iostream>
#include <utils/array1d.h>
#include <geometry/grid.h>

using std::cout;
using std::endl;
using namespace AMSTeL;

int main()
{
    cout << "Testing MathTL::Grid ..." << endl;

  cout << "- empty 1D grid:" << endl;
  Grid<1>().matlab_output(cout);
  
  cout << "- a non-empty Matlab-style 1D grid:" << endl;
  Array1D<double> points(3);
  points[0] = 1.0;
  points[1] = 2.4;
  points[2] = 3.0;
  Grid<1>(points).matlab_output(cout);

  cout << "- an equidistant 1D grid:" << endl;
  Grid<1>(0.0, 1.0, 5).matlab_output(cout);
}