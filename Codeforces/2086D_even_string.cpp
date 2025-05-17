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

const int MAXN = 5 * 1e5 + 2;
const lld MOD = 998244353;

lld expBin(lld n, lld e) {
  if (e == 0) {
    return 1;
  }
  if (e == 1) {
    return n;
  }
  lld ans = expBin(n, e / 2);
  ans = (ans * ans) % MOD;
  if (e & 1) {
    ans = (ans * n) % MOD;
  }
  return ans;
}

lld factMemo[MAXN];
lld fact(int n) {
  if (n <= 1)
    return 1;
  if (factMemo[0] == 0) {
    factMemo[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
      factMemo[i] = (i * factMemo[i - 1]) % MOD;
    }
  }
  return factMemo[n];
}

lld invMod(lld x) { return expBin(x, MOD - 2); }

lld invModFactMemo[MAXN];
lld invModFact(int n) {
  if (invModFactMemo[0] == 0) {
    invModFactMemo[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
      invModFactMemo[i] = invMod(fact(i));
    }
  }
  return invModFactMemo[n];
}

lld C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  if (k == 0 || k == n) {
    return 1;
  }
  return (fact(n) * (invModFact(k) * invModFact(n - k) % MOD)) % MOD;
}

lld dp[30][MAXN];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; T--) {
    int m = 26;
    vector<int> freq(m + 1);
    int n = 0;
    for (int i = 1; i <= m; ++i) {
      cin >> freq[i];
      n += freq[i];
    }
    dp[0][0] = 1;
    int missing = 0;
    for (int i = 1; i <= m; ++i) {
      missing += freq[i];
      fill(dp[i], dp[i] + n + 1, 0);
      for (int pares = 0; pares <= missing; pares++) {
        int impares = missing - pares;
        if (pares > ((n + 1) / 2) || impares > (n / 2)) {
          continue;
        }
        if (pares >= freq[i]) {
          // Suma el acomodarlos todos en una posición par.
          dp[i][pares] +=
              (C(pares, freq[i]) * dp[i - 1][pares - freq[i]]) % MOD;
          dp[i][pares] %= MOD;
        }
        if (impares >= freq[i] && freq[i] > 0) {
          // Suma el acomodarlos todos en una posición impar.
          dp[i][pares] += (C(impares, freq[i]) * dp[i - 1][pares]) % MOD;
          dp[i][pares] %= MOD;
        }
      }
    }
    cout << dp[m][(n + 1) / 2] << endl;
  }

  return 0;
}
