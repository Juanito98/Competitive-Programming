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

const lld MOD = 1e9 + 7;

lld n;

lld triangular(lld x) { return (x * (x + 1) / 2) % MOD; }

// Gives you the number of pairs x, y
// such that:
// 1 <= x <= y <= C
// x + y <= l
lld g(lld C, lld l) {
  lld ans = 0;
  // y = l - 1, 1 <= x <= 1
  // y = l - 2, 1 <= x <= 2
  // y = l - i, 1 <= x <= i

  // y <= C <=> l - i <= C <=> l - C <= i
  lld lo = max(1ll, l - C);
  // if x = i => i <= l - i => 2i <= l => i <= l / 2
  lld hi = l / 2;

  // cout << "lo: " << lo << ", hi: " << hi << endl;

  lld i = lo;
  // lo jump to hi
  // i = lo => += lo
  // i = lo + 1 => += lo + 1
  // ... i = hi => += lo + (hi - lo)
  //
  if (i <= hi) {
    ans += triangular(hi - lo) + ((lo * (hi - lo + 1)) % MOD);
    ans %= MOD;
    i = hi + 1;
  }
  // cout << "g1(C:" << C << ", l:" << l << ") = " << ans << endl;
  //  jump i to l - 1
  //  i => += l - i
  //  i + 1 => += l - i - 1
  //  i + 2 => += l - i - 2
  //  i + (l - i - 1) => += l - i - (l - i - 1)
  ans += ((((l - i) * (l - i)) % MOD) - triangular(l - i - 1) + MOD) % MOD;
  // cout << "g(C:" << C << ", l:" << l << ") = " << ans << endl;
  return ans;
}

// C = 9, l = 2
// lo = 1
// hi = 1

// Gives you the number of pairs A, B
// such that:
// 1 <= A <= B <= C
// A + B + C <= n
// C < A + B
lld f(lld C) {
  // C < A + B <=> 2C < A + B + C <= n
  // => 2C < n
  if (2 * C >= n) {
    return 0;
  }
  // C < A + B <= n - C
  // A <= B <= C
  // Esto es igual al numero de parejas
  // tal que
  //    A <= B <= C
  // y  A + B <= n - C
  // menos el numero de parejas
  // tal que
  //    A <= B <= C
  // y  A + B <= C
  return (g(C, n - C) - g(C, C) + MOD) % MOD;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;

  lld ans = 0;
  for (int c = 1; c <= n; ++c) {
    lld aux = f(c);
    // cout << "C: " << c << "; f(c) = " << aux << endl;
    ans += aux;
    ans %= MOD;
  }

  cout << ans << endl;

  return 0;
}
