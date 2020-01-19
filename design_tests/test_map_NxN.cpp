#include<iostream>
#include<string>
#include<map>
#include<time.h>
using namespace std;


/*This test measures the speed of filling and reading a map with a Key in NxN, in comparison to
to projecting a Key to an integer and using a map with long int.

Simon Wardein, Januar 2020
*/


class Key{
    public:
    
    int j, k;

    Key(int x, int y)
    {j=x;k=y;}

    // analogical function to Cantors diagonal argument
    long int nr(){
        return (j+k-2)*(j+k-1)/2+j;
    }

    bool operator<(const Key& vgl)
    {
        return((j < vgl.j) || ((j == vgl.j) && (k < vgl.k))); 
    }
    
    
    bool operator!=(Key vgl)
    {
        return (j!=vgl.j || k!=vgl.k);
    }
    friend ostream &operator<< (ostream &ostr, const Key &a);
    
    
};

ostream &operator<< (ostream &ostr,const Key& a)
    {
    ostr << '(' << a.j << "," << a.k << ')';
    return ostr;   
    }

//a class to sort Keys lexicografical in a map
struct Key_Compare
{
   bool operator() (const Key& lhs, const Key& rhs) const
   {
       return((lhs.j < rhs.j) || ((lhs.j == rhs.j) && (lhs.k < rhs.k)));
   }
};

//a class to sort Keys with nr() in a map
struct Key_Compare2
{
   bool operator() (const Key& lhs, const Key& rhs) const
   {
       return((lhs.j+lhs.k-2)*(lhs.j+lhs.k-1)/2+lhs.j<(rhs.j+rhs.k-2)*(rhs.j+rhs.k-1)/2+rhs.j);
   }
};



int main(){


map<Key,float,Key_Compare> map_Key;
map<Key,float,Key_Compare> map_Key2;
map<long int, float> map_int;

//dur1: Key with Key_compare
//dur2: Key with Key_compare2
//dur3: Integer with nr()


//filling map

double dur1, dur2, dur3;
clock_t start;
start=clock();

//upper bound for N
int N=500;

Key It(0,0);
for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        It.j=j;
        It.k=k;
        map_Key[It]=1;
        

    }


}
dur1=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();



for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
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
    for(int k=1;k<N;k++){
          It.j=j;
        It.k=k;
        r=map_Key[It];
    }
}

  dur4=( clock() - start ) / (double) CLOCKS_PER_SEC;
  start=clock();

for(int j=1;j<N;j++){
    for(int k=1;k<N;k++){
        It.j=j;
        It.k=k;
        r=map_int[It.nr()];
    }
}

dur5=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();


for(int j=1;j<N;j++){
    for(int k=1;k<N;k++){
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
