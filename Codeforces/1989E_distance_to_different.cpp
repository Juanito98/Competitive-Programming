/* First, we can map 1:1 a partition of n that does not include two (except
  at the beginning or the end). E.g n=7, a partition would be 2+1+3+1 that
  would map to the [2, 1 | 1 | 1, 2, 1 | 1].

  Now, it is pretty easy to see that there is always a valid A array that
  produces B. E.g. A = [1, 1 | 2 | 1, 1, 1 | 2] produces the B above.

  However, as we are required to put at least one element from 1 to k, a
  valid B should be mapped to a partition of n of k or more elements.

  Therefore, the response is the number of partitions of n into k or more
  elements that does not include two (except at the ends)
*/
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

lld MOD = 998244353;
const int MAXN = 200002;

lld sumMod(lld a, lld b) { return (a + b) % MOD; }
lld subMod(lld a, lld b) { return (a - b + MOD) % MOD; }

// h is the number of partitions of n, which happens to be 2^{n-1}
lld hM[MAXN];
bool hVis[MAXN];
lld h(int n) {
  if (n <= 1) {
    return 1;
  }
  if (!hVis[n]) {
    hVis[n] = true;
    hM[n] = (2ll * h(n - 1)) % MOD;
  }
  return hM[n];
}

lld g(int n);

// f is the number of partitions of n with no 2 as an element
lld f(int n) { return subMod(h(n), g(n)); }

// g is the number of partitions of n with at least one 2 as an element
lld gM[MAXN];
bool gVis[MAXN];
lld g(int n) {
  if (n <= 1) {
    return 0;
  }
  if (n == 2) {
    return 1;
  }
  if (!gVis[n]) {
    gVis[n] = true;
    gM[n] = sumMod(2 * g(n - 1), subMod(f(n - 2), f(n - 3)));
  }
  return gM[n];
}

// The number of partitions of n into exactly k elements
// with no 2 as an elements
lld memo[MAXN][12];
bool vis[MAXN][12];
lld dp(int n, int k) {
  if (n == k) {
    return 1;
  }
  if (n <= 0) {
    return 0;
  }
  if (k == 1) {
    return (n == 2 ? 0 : 1);
  }
  if (k == 0) {
    return 0;
  }

  if (!vis[n][k]) {
    vis[n][k] = true;
    memo[n][k] = sumMod(dp(n - 1, k), dp(n - 1, k - 1));
    memo[n][k] = sumMod(memo[n][k], dp(n - 3, k - 1));
    memo[n][k] = subMod(memo[n][k], dp(n - 2, k - 1));
  }
  return memo[n][k];
}

// The number of partitions of n into less than k elements
// with no 2 as an elements
lld fk(int n, int k) {
  lld ans = 0;
  for (int i = 0; i < k; ++i) {
    ans = sumMod(ans, dp(n, i));
  }
  return ans;
}

lld solve(int n, int k) {
  // the number of partitions of n into k or more
  // elements that does not include two(except at the ends)
  // That is, the total partitions of n that does not includes 2 in the middle
  // minus the number of partitions of n into less than k elements
  // that does not include 2 in the middle
  lld totalPartitions = f(n);
  // Place a 2 at the beginning
  totalPartitions = sumMod(totalPartitions, f(n - 2));
  if (n > 2) {
    // Place a 2 at the end
    totalPartitions = sumMod(totalPartitions, f(n - 2));
  }
  if (n >= 4) {
    // Place a 2 at both ends
    totalPartitions = sumMod(totalPartitions, f(n - 4));
  }
  lld invalidPartitions = fk(n, k);

  // Place a 2 at the beginning
  invalidPartitions = sumMod(invalidPartitions, fk(n - 2, k - 1));

  if (n > 2) {
    // Place a 2 at the end
    invalidPartitions = sumMod(invalidPartitions, fk(n - 2, k - 1));
  }
  if (n >= 4) {
    // Place a 2 at both ends
    invalidPartitions = sumMod(invalidPartitions, fk(n - 4, k - 2));
  }

  return subMod(totalPartitions, invalidPartitions);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, k;
  cin >> n >> k;

  cout << solve(n, k) << endl;

  return 0;
}
