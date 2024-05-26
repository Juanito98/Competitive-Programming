#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <complex>
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
typedef long long int lld;
typedef long double llf;
typedef pair<int, int> pii;

const lld M = 1e9 + 7;

lld pmod(lld a, lld b) {
    return ((a % M) * (b % M)) % M;
}

lld exp(lld b, lld e) {
    if (!e) return 1;
    lld x = exp(b, e / 2);
    x *= x;
    x %= M;
    if (e & 1) {
        x *= b;
        x %= M;
    }
    return x;
}

lld inv(lld n) {
    return exp(n, M - 2);
}

lld inv2 = inv(2);
lld inv6 = inv(6);

lld triangular(lld n) {
    return pmod(pmod(n, n + 1), inv2);
}

lld cuadrangular(lld n) {
    lld ans = pmod(n, n + 1);
    ans = pmod(ans, pmod(2, n) + 1);
    ans = pmod(ans, inv6);
    return ans;
}

lld f1(lld n) {
    return pmod(inv2, (triangular(n - 1) + cuadrangular(n - 1)) % M);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // OJO: n  puede ser > MODULO
    lld n;
    while (cin >> n) {
        // Parte vertical

        // Verdes con verdes (YA ESTA BIEN)
        //lld ans = n * n * f1(n);
        lld ans = pmod(pmod(n, n), f1(n));

        // 3 de enmedio entre si (YA ESTA BIEN)
        //ans += 9 * n * n * f1(n);
        ans += pmod(pmod(9, n), pmod(n, f1(n)));
        ans %= M;

        // 3 de en medio al verde
        //ans += 3 * n * n * n * triangular(n - 1);
        ans += pmod(pmod(pmod(3, n), n), pmod(n, triangular(n-1)));
        ans %= M;
        //ans += 3 * n * n * n * triangular(n);
        ans += pmod(pmod(pmod(3, n), n), pmod(n, triangular(n)));
        ans %= M;

        // Morados a los tres (igual al de arriba)
        //ans += 3 * n * n * n * triangular(n - 1);
        ans += pmod(pmod(pmod(3, n), n), pmod(n, triangular(n-1)));
        ans %= M;
        //ans += 3 * n * n * n * triangular(n);
        ans += pmod(pmod(pmod(3, n), n), pmod(n, triangular(n)));
        ans %= M;

        // Morado a verde
        //ans += n * n * n * n * n;
        ans += pmod(pmod(pmod(n, n), n), pmod(n, n));
        ans %= M;
        //ans += n * n * n * triangular(n - 1);
        ans += pmod(pmod(n, n), pmod(n, triangular(n - 1)));
        ans %= M;
        //ans += n * n * n * triangular(n);
        ans += pmod(pmod(n, n), pmod(n, triangular(n)));
        ans %= M;

        // Morados entre si (igual a verde entre verde)
        //ans += n * n * f1(n);
        ans += pmod(pmod(n, n), f1(n));
        ans %= M;

        // Parte horizontal
        ans *= 2;
        ans %= M;

        cout << ans << "\n";
    }
    return 0;
}