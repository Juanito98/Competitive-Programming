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

void solve() {
    string s;
    ll k;
    cin >> s >> k;
    string resp;
    ll sizeResp = 0;
    bool band = true;
    int size = s.size();
    int dig;
    for (int i = 0; i < size && band; ++i) {
        if ('0' <= s.at(i) && s.at(i) <= '9') {
            dig = s.at(i) - '0';
            ++i;
            while (i < size && dig <= k && '0' <= s.at(i) && s.at(i) <= '9') {
                dig = 10 * dig + (s.at(i) - '0');
            }
            if (sizeResp + dig <= k) {
                sizeResp += dig;
                loop(j, 0, dig) resp += s.at(i);
            } else {
                band = false;
            }
        } else {
            if (sizeResp + 1 <= k) {
                ++sizeResp;
                resp += s.at(i);
            } else {
                band = false;
            }
        }
    }
    if (band) {
        cout << resp << "\n";
    } else {
        cout << "unfeasible\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    int T;
    cin >> T;
    loop(i, 0, T) {
        solve();
    }
}
