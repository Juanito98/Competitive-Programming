#include <limits.h>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
typedef int64_t ll;
vector<ll> cajas;

ll comb(int n, int r) {
    if (r == 0) return 1;
    if (r > n / 2) return comb(n, n - r);

    ll res = 1;

    for (int k = 1; k <= r; ++k) {
        res *= n - k + 1;
        res /= k;
    }

    return res;
}
ll f(int n, int k, ll b) {
    ll ans = 0;
    for (int i = n - 1; i >= 0 && k > 0; i--) {
        if (cajas[i] <= b) {
            if (k <= i) ans += comb(i, k);
            b -= cajas[i];
            //cout << "ans " << ans <<" comb " << i << "C" << k << " " << comb(i,k) << " b: " << b << '\n';
            k--;
            if (k == 0) return ans + 1;
        }
    }
    return ans;
}
int main() {
    int n, k;
    ll a, b;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        ll aux;
        cin >> aux;
        cajas.push_back(aux);
    }
    sort(cajas.begin(), cajas.end());
    cin >> a >> b;
    ///cout << "f(b)\n";
    cout << f(n, k, b) - f(n, k, a - 1) << '\n';

    return 0;
}