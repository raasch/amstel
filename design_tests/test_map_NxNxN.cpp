#include<iostream>
#include<string>
#include<map>
#include<time.h>
#include<math.h>
using namespace std;



/*This test measures the speed of filling and reading a map with a Key in NxNxN, in comparison to
to projecting a Key to an integer and using a map with long int.

Simon Wardein, Januar 2020
*/


class Key{
    public:
    
    int j, k, l;

    Key(int x, int y,int z)
    {j=x;k=y;l=z;}

    //funktion is using the NxN version on top of simplexes
    long int nr(){
        return (pow(j+k+l,3)-(j+k+l))/6+(j+k-1)*(j+k)/2+j;
    }

    bool operator<(const Key& vgl)
    {
        if(j<vgl.j){
            return true;    
        }
        else if((j=vgl.j)&&(k<vgl.j)){
            return true;
        }
        else if((j=vgl.j)&&(k=vgl.k)&&(l<vgl.l)){
            return true;
        }

        else{
            return false;
        }
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
      if(lhs.j<rhs.j){
            return true;    
        }
        else if((lhs.j==rhs.j)&&(lhs.k<rhs.j)){
            return true;
        }
        else if((lhs.j==rhs.j)&&(lhs.k==rhs.k)&&(lhs.l<rhs.l)){
            return true;
        }

        else{
            return false;
        }
   }
};


struct Key_Compare2
{
   bool operator() (const Key& lhs, const Key& rhs) const
   {       
       return((lhs.j<rhs.j)||((lhs.j==rhs.j)&&(lhs.k<rhs.j))||((lhs.j==rhs.j)&&(lhs.k==rhs.k)&&(lhs.l<rhs.l)));
   }
};



int main(){


map<Key,float,Key_Compare> map_Key;
map<long int, float> map_int;

double dur1, dur2;
clock_t start;
start=clock();

int N=150;
Key It(0,0,0);
for(int j=1;j<N;j++){
    for(int k=1;k<N;k++){
        for(int l=1;l<N;l++){
        It.j=j;
        It.k=k;
        It.l=l;
        map_Key[It]=1;
        
        }
    }


}
//filling map

//dur1: Key with Key_compare
//dur2: Integer with nr()

dur1=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();




for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++){
        It.j=j;
        It.k=k;
        
        map_int[It.nr()]=1;
        
        }
    }


}
dur2=( clock() - start ) / (double) CLOCKS_PER_SEC;


//reading map

//dur3: Key with Key_compare
//dur4: Integer with nr()

float r=0;

double dur3, dur4;

start=clock();



for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++){
        It.j=j;
        It.k=k;
        It.l=l;
        r=map_Key[It];
        }
        }
    }

dur3=( clock() - start ) / (double) CLOCKS_PER_SEC;
start=clock();


for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++){
        It.j=j;
        It.k=k;
        It.l=l;
        r=map_int[It.nr()];
        }
        }
    }
dur4=( clock() - start ) / (double) CLOCKS_PER_SEC;




cout<<"\nwriting with Key and Key_compare:  "<<dur1<<"s\n";
cout<<"writing with long int and nr(): "<< dur2 <<"s\n";
cout<<"\nreading with Key and Key_compare: "<<dur3<<"s\n";
cout<<"reading with long int and nr(): "<< dur2 <<"s\n";

return 0;
}