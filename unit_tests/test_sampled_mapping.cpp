#include <iostream>
#include<cmath>
#include <geometry/grid.h>
#include <geometry/sampled_mapping.h>
#include <algebra/infinite_vector.h>


using std::cout;
using std::endl;

using namespace AMSTeL;

int main()
{
  cout << "Testing SampledMapping<1> class ..." << endl;
  SampledMapping<1> f;
  cout << "- Matlab output of empty 1D mapping:" << endl;
  f.matlab_output(cout);

  cout << "- Matlab output of a sampled function on a 1D grid:" << endl;
  SampledMapping<1> g(Grid<1>(0.0, 1.0, 5));
  //Grid<1>(0.0, 1.0, 5).matlab_output(cout);
  g.matlab_output(cout);

  /*cout << "- Gnuplot output for the same parameters:" << endl;
  g.gnuplot_output(cout);*/
  Array1D<double> a(6);
  //a[0]=1.2; a[1]=2.1; a[4]=3.2;
  cout << "- testing SampledMapping<1>::add():" << endl;
  g.add(SampledMapping<1>(Grid<1>(0.0, 1.0, 5),a));
  g.matlab_output(cout);

  InfiniteVector<double, int> s;
   s[1] = 2; s[3] = 42;
  SampledMapping<1, double> si;
  si= SampledMapping<1, double> (0 , 4 , s , 1);

   cout << "- testing SampledMapping<1> constructed by infinitevector:" << endl;
  si.matlab_output(cout);   




  cout << "- Matlab output of a sampled function on a 2D grid:" << endl;
  //Grid<2> grid(Point<2>(0.0, 0.0), Point<2>(1.0, 1.0), 4, 4);
  Grid<2> grid(0.0, 0.0, 1.0, 1.0, 4, 4);
  SampledMapping<2,double> h(grid);
  h.matlab_output(cout);

  cout << "- testing SampledMapping<2>::add():" << endl;
  Array2D<double> b(5);
  for(int i=0;i<5;i++){
    b(0,i)=1; b(1,i)=1; b(2,i)=1; b(3,i)=1; b(4,i)=1;
  }
  h.add(2.0, b);
  h.octave_output(cout);
  //h.matlab_output(cout);

  return 0;
}