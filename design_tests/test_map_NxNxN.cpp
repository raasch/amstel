#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include<time.h>
#include<math.h>
using namespace std;



/*
Reading from a filled map can become expensive for a more complex < operator.
It might be faster to use a unordered map with integers together with a bijectiv function,
which image are nonnegativ integers.
In this test is the key a simple class of three integers and 
contains comparison-operaters and an output operator for testing purpurses.
The function nr() in this case is based on the idea to expand the NxN version.
Let the top of a n-sized standard simplex be: S(n)={j+k+l=n | (j,k,l) in key}.
S(n) contains (n(n+1)/2) elements of key. 
Summing all elements of {S(m)|m<n} leads to ((j+k+l)^3+3*(j+k+l)^2+2*(j+k+l))/6.
To determine an unique integer, the NxN version was added with two entries.
    
Simon Wardein, May 2020
*/

class Key{
    public:
    
    int j, k, l;

    Key(int x, int y,int z)
    {
        j=x;k=y;l=z;
    }

    long int nr()
    {    
        return (pow(j+k+l,3)+pow(j+k+l,2)*3+(j+k+l)*2)/6+((j+k)*(j+k+1))/2+j;
    }

    bool operator<(const Key& vgl)
    {
        return((j<vgl.j)||((j==vgl.j)&&(k<vgl.k))||((j==vgl.j)&&(k==vgl.k)&&(l<vgl.l)));
    }
    bool operator==(const Key& vgl)
    {
        return (j==vgl.j && k==vgl.k && l==vgl.l);
    }
    bool operator!=(Key vgl)
    {
        return (j!=vgl.j || k!=vgl.k || l!=vgl.l);
    }
    friend ostream &operator<< (ostream &ostr, const Key &a);
    
    
};

ostream &operator<< (ostream &ostr,const Key& a)
    {
    ostr << '(' << a.j << "," << a.k << ","<< a.l <<')';
    return ostr;   
    }

struct Key_Compare
{
   bool operator() (const Key& lhs, const Key& rhs) const
   {       
       return((lhs.j<rhs.j)||((lhs.j==rhs.j)&&(lhs.k<rhs.k))||((lhs.j==rhs.j)&&(lhs.k==rhs.k)&&(lhs.l<rhs.l)));
   }
};




int main(){
//upper bound for N
int N=50;

map<Key,double,Key_Compare> map_Key; //lexicographical sorting
unordered_map<long int, double> unordered_map_int;

//filling map
Key It(0,0,0);
for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++)
        {
        It.j=j;
        It.k=k;
        It.l=l;
        map_Key[It]=0; 
        unordered_map_int[It.nr()]=0;   
        }
    }
}
//dur1: Key with Key_compare
//dur2: Integer with nr()
double dur1, dur2;
clock_t start;
start=clock();

for(int j=1;j<N;j++){
    for(int k=1;k<N;k++){
        for(int l=1;l<N;l++)
        {
        It.j=j;
        It.k=k;
        It.l=l;
        map_Key[It]=1; 
        }
    }
}

dur1=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();

for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++)
        {
        It.j=j;
        It.k=k;
        It.l=l;
        unordered_map_int[It.nr()]=1;       
        }
    }
}

dur2=( clock() - start ) / (double) CLOCKS_PER_SEC;

//reading map
//dur3: Key with Key_compare
//dur4: Integer with nr()
double dur3, dur4;
double r=0;
start=clock();
for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++)
        {
        It.j=j;
        It.k=k;
        It.l=l;
        r=map_Key.find(It)->second;
        }
    }
}

dur3=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();

for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++)
        {
        It.j=j;
        It.k=k;
        It.l=l;
        r= unordered_map_int.find(It.nr())->second;
        }
    }
}

dur4=( clock() - start ) / (double) CLOCKS_PER_SEC;

cout<<"\nwriting with Key and Key_compare in a filled map:  "<<dur1<<"s\n";
cout<<"writing with long int and nr() in a filled unordered map: "<< dur2 <<"s\n";

cout<<"\nreading with Key and Key_compare: "<<dur3<<"s\n";
cout<<"reading with long int and nr() from unordered map: "<< dur4 <<"s\n";

return 0;
}