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

const lld MOD = 1e9l + 7l;

unordered_map<int, bool> visPairs;
unordered_map<int, int> memoPairs;
// S goes from -9 to 9
int pairs(int s) {
  if (!visPairs[s]) {
    visPairs[s] = true;
    memoPairs[s] = 0;
    for (int a = 0; a < 10; ++a) {
      for (int b = 0; b < 10; ++b) {
        if (a == b || a - b != s) {
          continue;
        }
        memoPairs[s]++;
      }
    }
  }
  return memoPairs[s];
}

const int MAXN = 802;
bool vis[MAXN][20 * MAXN];
lld memo[MAXN][20 * MAXN];
int offset = 10 * MAXN;
// Given I need to place n digits and I have a
// difference of diff, return the number of valid pairs
lld dp(int n, int diff) {
  if (n == 0) {
    // No more digits
    return diff == 0 ? 1 : 0;
  }
  if (abs(diff) > n * 9) {
    return 0;
  }
  if (!vis[n][diff + offset]) {
    vis[n][diff + offset] = true;
    memo[n][diff + offset] = 0;
    // Iterate over the possible difference of ai - bi
    for (int k = 10; k > -10; --k) {
      memo[n][diff + offset] += dp(n - 1, diff + k) * pairs(k);
      memo[n][diff + offset] %= MOD;
    }
  }
  return memo[n][diff + offset];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    lld ans = 0;
    for (int a = 1; a < 10; ++a) {
      for (int b = 1; b < 10; ++b) {
        if (a == b) {
          continue;
        }
        ans += dp(n - 1, a - b);
        ans %= MOD;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
