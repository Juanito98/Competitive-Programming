
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

using namespace std;

typedef int64_t ll;
typedef long double ld;
typedef pair<int,int> pii;

#define INF 1000000000000
#define MOD 1000000007
#define loop(i,a,b) for(int i = a; i < b; ++i)

const int maxN = 1000005;
int n, m, q;
vector<int> adj[maxN];
ll mio[maxN], mio2[maxN], manag[maxN], rama[maxN];

void dfs1(int v, int fa){
    
    for(int son : adj[v]){
        if(son == fa) continue;
        dfs1(son, v);
    }
    mio2[v] += manag[v];
    
    mio2[fa] += mio2[v];

    mio2[v] += mio[v];
}

void dfs2(int v, int fa){

    for(int son : adj[v]){
        if(son == fa) continue;
        dfs2(son, v);
    }

    rama[v] += mio2[v];
    rama[fa] += rama[v];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>q;
    int indx;
    loop(i, 1, n+1){
        cin>>indx;
        adj[i].push_back(indx);
        adj[indx].push_back(i);
    }

    int tipo, v;
    loop(i, 0, m){
        cin>>tipo>>indx>>v;
        if(tipo == 1){
            mio[indx] += v;
        }
        else{
            manag[indx] += v;
        }
    }

    dfs1(0, -1);
    

    
    dfs2(0, -1);
    loop(i, 0, q){
        cin>>tipo>>indx;
        if(tipo == 1){
            cout<<mio2[indx]<<"\n";
        }  
        else{
            cout<<rama[indx]<<"\n";
        }
    }
    //cout<<rama[0]<<endl;
}
