#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
typedef int64_t ll;

const int maxN = 2*1e5 + 5;
ll fact[maxN], invFact[maxN];
ll comb(int num, int k){
    if (num < 0 || num < k) return 0;
    return (((fact[num]*invFact[k])%MOD)*invFact[num-k])%MOD;
}
ll binPow(ll b, ll e) {
    if (!e) return 1;
    ll x = binPow(b, e / 2);
    x *= x;
    x %= MOD;
    if (e & 1) {
        x *= b;
        x %= MOD;
    }
    return x;
}
void calcF(){
    fact[0] = invFact[0] = 1;
    for(int i = 1; i < maxN; ++i){
        fact[i] = (fact[i-1]*i)%MOD;
        invFact[i] = binPow(fact[i], MOD-2);
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, v;
    cin >> n;
    calcF();

    for(int i = 0; i <  n; i++){
        cin >> v;
        cout << comb(2*v-1, v) << '\n';
    }
    return 0;
}
