#include <cstdlib>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <algebra/infinite_vector.h>

using std::cout;
using std::endl;
using namespace AMSTeL;

int main()
{
  cout << "Testing the InfiniteVector class ..." << endl;

  InfiniteVector<float,long int> s;
  cout << "- a zero vector:" << endl
       << s << endl;

  cout << "- write access on s:" << endl;
  s[1] = 2;
  cout << "  (size after writing the first element: " << s.size() << ")" << endl;
  s[3] = 42;
  cout << "  (size after writing the second element: " << s.size() << ")" << endl;
  cout << s;

  cout << "- copy constructor t(s):" << endl;
  InfiniteVector<float,long int> t(s);
  cout << t;
    
  cout << "- are the two vectors equal?" << endl;
  if (t == s)
    cout << "  ... yes!" << endl;
  else
    cout << "  ... no!" << endl;

  cout << "- are the two vectors inequal?" << endl;
  if (t != s)
    cout << "  ... yes!" << endl;
  else
    cout << "  ... no!" << endl;

  t[3] = 43;
  cout << "- after modifying t into..." << endl;
  cout << t << "..., are the two vectors equal?" << endl;
  if (t == s)
    cout << "  ... yes!" << endl;
  else
    cout << "  ... no!" << endl;

  cout << "- in place summation s+=t:" << endl;
  s += t;
  cout << s;

  cout << "- in place subtraction t-=s:" << endl;
  t -= s;
  cout << t;

  cout << "- in place multiplication s*=2:" << endl;
  s *= 2;
  cout << s;
  
  cout << "- in place division s/=3:" << endl;
  s /= 3;
  cout << s;
  
  // now testing different CONTAINER arguments
  InfiniteVector<double,long int,std::unordered_map<long int,double> > z;
  cout << "- a zero vector with hashed container:" << endl
       << z << endl;

  cout << "- read access on z with get_coefficient(2):" << endl
  << z.get_coefficient(2) << endl;

  cout << "- write access on z with set_coefficient(6):" << endl;
  z.set_coefficient(6, -10);
  cout << z << endl;

  cout << "- write access on z:" << endl;
  z[1] = 2;
  cout << "  (size after writing the first element: " << z.size() << ")" << endl;
  z[3] = 42;
  cout << "  (size after writing the second element: " << z.size() << ")" << endl;
  cout << z;

  cout << "- modifiy (delete) z[1] with add_coefficient():" << endl;
  z.add_coefficient(1, -2);
  cout << z << endl;

  cout << "- modifiy (update) z[3] with add_coefficient():" << endl;
  z.add_coefficient(3, 1.5);
  cout << z << endl;

  return 0;
}
