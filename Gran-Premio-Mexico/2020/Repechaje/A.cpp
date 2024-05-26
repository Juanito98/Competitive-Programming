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
typedef pair<ll, ll> pll;

#define INF 1000000000000
#define MOD 1000000007
#define loop(i,a,b) for(int i = a; i < b; ++i)

const int maxN = 1e5 + 5;   


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll n, m;
    cin>>n>>m;
    ll x = pow(2, n), y = pow(2, m);

    cout<<(x + y - 2)<<"\n";

}
