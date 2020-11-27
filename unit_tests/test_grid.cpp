#include <iostream>
#include <utils/array1d.h>
#include <utils/array2d.h>
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

  cout << "- empty 2D grid:" << endl;
  Grid<2>().matlab_output(cout);

  cout << "- a non-empty Matlab-style 2D grid:" << endl;
  Array2D<double> gridx(2,2), gridy(2,2);
  gridx(0,0) = gridx(1,0) = 0.0;
  gridx(0,1) = gridx(1,1) = 1.0;
  gridy(0,0) = gridy(0,1) = 0.0;
  gridy(1,0) = gridy(1,1) = 1.0;
  Grid<2>(gridx, gridy).matlab_output(cout);

  cout << "- an equidistant 2D grid:" << endl;
  Grid<2> equi(0.0, 0.0, 1.0, 1.0, 2, 4);
  equi.matlab_output(cout);

  cout << "- a 2D tensor product grid from 2 1D grids:" << endl;
  Grid<1> gx(points);
  Grid<1> gy(0.0, 1.0, 4);
  Grid<2> tensor(gx, gy);
  tensor.matlab_output(cout);

  cout << "- test assignment operator:" << endl;
  equi = tensor;
  equi.matlab_output(cout);
  
  return 0;
}