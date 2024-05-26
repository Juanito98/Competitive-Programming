#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <stack>
#include <utility>
#include <queue>
#include <set>
#include <iomanip>
#include <sstream>
#include <unordered_set>


using namespace std;

typedef int64_t ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;

#define MOD 1000000007
#define MINF -1000000000000

#define modula(a,b) (a%b + b)%b
#define loop(i,a,b) for(int i = a; i < b; ++i)
#define invl(i,a,b) for(int i = a; i > b; --i)

const int maxN = 1e6 + 5;
int n;

struct matrix{
    vector< vector<ld> > m;
    int sz1;
 
    matrix(int sz12){
        sz1 =sz12;
        m.resize(sz1);
        loop(i, 0, sz1) m[i].resize(sz1);
    }

    matrix operator*(matrix b)
    {
        matrix ans(sz1);
        for(int i=0;i<sz1;i++)
        for(int j=0;j<sz1;j++)
            for(int u=0;u<sz1;u++)
            {
                ans.m[i][j]+=m[i][u]*b.m[u][j];
            }
        return ans;
    }
 
    matrix pow(int e)
    {
        if(e==1)
            return *this;
        matrix x =pow(e/2);
        x=(x*x);
        if(e&1)
            x=(x*(*this));
        return x;
    }
};


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    cin>>n;
    int mm;
    cin>>mm;


    matrix mat(n);
    
    ld aux;
    loop(i, 0, n){
        loop(j, 0, n){
            cin>>aux;
            mat.m[i][j] = aux;
        }
    }


    mat = mat.pow(mm);
    loop(i, 0, n){
        cout<<fixed<<setprecision(5)<<mat.m[0][i]<<"\n";
    }

    return 0;    
}