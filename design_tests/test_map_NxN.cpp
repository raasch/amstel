#include<iostream>
#include<string>
#include<map>
#include<time.h>
using namespace std;


/*Reading from a filled map can become expensive for a more complex < operator.
It might be faster to use a map with integers together with a bijectiv function,
which image are nonnegativ integers.
In this test is the key a simple class of two integers and 
contains comparison-operaters and an output operator for testing purpurses.
The function nr() in this case is based on the idea cantors diagonal argument.
If (j,k) is in key, the diagonal lane is determined by j+k.
The number of all elements up to the lane is (j+k)(j+k+1)/2.
By adding j to the equation, every key is matched with a unique integer.
    
Simon Wardein, Januar 2020
*/


class Key{
    public:
    
    int j, k;

    Key(int x, int y)
    {j=x;k=y;}

    
    long int nr()
    {
        return (j+k)*(j+k+1)/2+j;
    }
    bool operator<(const Key& vgl)
    {
        return((j < vgl.j) || ((j == vgl.j) && (k < vgl.k))); 
    }    
    bool operator!=(const Key& vgl)
    {
        return (j!=vgl.j || k!=vgl.k);
    }
    friend ostream &operator<< (ostream &ostr, const Key &o);
    
};

ostream &operator<< (ostream &ostr,const Key& o)
    {
    ostr << '(' << o.j << "," << o.k << ')';
    return ostr;   
    }



//to sort the keys in the map, the following structs where made
//sorting Keys lexicografical
struct Key_Compare
{
   bool operator() (const Key& lhs, const Key& rhs) const
   {
       return((lhs.j < rhs.j) || ((lhs.j == rhs.j) && (lhs.k < rhs.k)));
   }
};

//sorting Keys with nr()
struct Key_Compare2
{
   bool operator() (const Key& lhs, const Key& rhs) const
   {
       return((lhs.j+lhs.k)*(lhs.j+lhs.k+1)/2+lhs.j<(rhs.j+rhs.k)*(rhs.j+rhs.k+1)/2+rhs.j);
   }
};



int main(){
//upper bound for N
int N=500;

map<Key,float,Key_Compare> map_Key; //lexicograffical sorting
map<Key,float,Key_Compare2> map_Key2;//sorting with nr()
map<long int, float> map_int;       //standard map with long int 

//filling map
//dur1: Key with Key_compare
//dur2: Key with Key_compare2
//dur3: Integer with nr()

double dur1, dur2, dur3;
clock_t start;
start=clock();

Key It(0,0);
for(int j=0;j<N;j++){
    for(int k=0;k<N;k++)
    {
        It.j=j;
        It.k=k;
        map_Key[It]=1;        
    }
}

dur1=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();

for(int j=0;j<N;j++){
    for(int k=0;k<N;k++)
    {
        It.j=j;
        It.k=k;
        
        map_Key2[It]=1;        
    }
}

dur2=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();

for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        It.j=j;
        It.k=k;
        
        map_int[It.nr()]=1;
    }
}

dur3=( clock() - start ) / (double) CLOCKS_PER_SEC;

//reading map

float r=0;

//dur4: Key with Key_compare
//dur5: Key with Key_compare2
//dur6: Integer with nr()

double dur4, dur5, dur6;
//clock_t start;
start=clock();


for(int j=1;j<N;j++){
    for(int k=1;k<N;k++)
    {
          It.j=j;
        It.k=k;
        r=map_Key[It];
    }
}

  dur4=( clock() - start ) / (double) CLOCKS_PER_SEC;
  start=clock();

for(int j=1;j<N;j++){
    for(int k=1;k<N;k++)
    {
        It.j=j;
        It.k=k;
        r=map_int[It.nr()];
    }
}

dur5=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();


for(int j=1;j<N;j++){
    for(int k=1;k<N;k++)
    {
        It.j=j;
        It.k=k;
        r=map_Key[It];
    }
}
dur6=( clock() - start ) / (double) CLOCKS_PER_SEC;



cout<<"\nwriting with Key and Key_compare: "<<dur1<<"s\n";
cout<<"writing with long int and nr():"<< dur2 <<"s\n";
cout<<"writing with Key and Key_compare2: "<<dur3<<"s\n";

cout<<"\nreading with Key and Key_compare: "<<dur4<<"s\n";
cout<<"reading with long int and nr():"<< dur5 <<"s\n";
cout<<"reading with Key and Key_compare2: "<<dur6<<"s\n";

return 0;
}
