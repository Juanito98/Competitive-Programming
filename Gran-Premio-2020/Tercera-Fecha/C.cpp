#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef int64_t ll;
typedef long double ld;

typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;

#define MINF -1000000000000
#define MOD 1000000007

#define m(a, b) (a % b + b) % b
#define loop(i, a, b) for (int i = a; i < b; ++i)
#define invl(i, a, b) for (int i = a; i > b; --i)

const int maxN = 1e5;

ll binPow(ll base, ll exp) {
    ll r = 1;
    while (exp > 0) {
        if (exp & 1)
            r = (r * base) % MOD;
        exp >>= 1;
        base = (base * base) % MOD;
    }
    return r % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    int T;
    cin >> T;
    ll n, k, resp;
    ll inv2 = binPow(2, MOD - 2);
    loop(i, 0, T) {
        cin >> n >> k;
        resp = (k + 1) * (n + 1);
        resp %= MOD;
        resp = (resp * (n + 2)) % MOD;
        resp = (resp * inv2) % MOD;
        cout << resp << "\n";
    }
}
