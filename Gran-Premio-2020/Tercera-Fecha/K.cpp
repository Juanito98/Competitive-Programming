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

const int maxN = 2 * 1e5 + 5;

ll fact[maxN], invFact[maxN];

ll binPow(ll base, ll exp) {
    ll r = 1;
    while (exp > 0) {
        if (exp & 1)
            r = (r * base) % MOD;
        exp >>= 1;
        base = (base * base) % MOD;
    }
    return r;
}

ll comb(int num, int k) {
    if (num < 0 || num < k || k < 0) return 0;
    return (((fact[num] * invFact[k]) % MOD) * invFact[num - k]) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < 2 * 1e5 + 5; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = binPow(fact[i], MOD - 2);
    }
    int T;
    cin >> T;
    ll a, b, C, k, c;
    ll resp, resp1, resp2;
    loop(i, 0, T) {
        cin >> a >> b >> C >> k >> c;

        if (k - c < 2) {
            cout << "0\n";
        } else {
            resp1 = comb(C, c);
            resp2 = m(comb(a + b, k - c) - comb(a, k - c), MOD);
            resp2 = m(resp2 - comb(b, k - c), MOD);
            resp = (resp1 * resp2) % MOD;
            cout << resp << "\n";
        }
    }
}
