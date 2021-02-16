
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

const int maxN = 100005;

ll gcd(ll a, ll b){
    if(a == 0)
        return b;
    else
        return gcd(b%a, a);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    ll tf, tb, m, res, c, s, f, b;
    ll ini, fin , mitad;
    loop(t, 0, T){
        cin>>c>>f>>b>>s;
        tf = 12/gcd(12, f);
        tb = 12/gcd(12, b);

        m = tf*tb/gcd(tf, tb);
        ini = 0, fin = 12000000000;
        while(ini != fin){
            mitad = (ini + fin)/2;
            if(c*m*mitad >= 12*s)
                fin = mitad;
            else
                ini = mitad+1;
        }
        cout<<ini*m<<"\n";
    }
}
