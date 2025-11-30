#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <complex>
#include <functional>
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

const lld MOD = 998244353;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
      cin >> b[i];
    }

    vector<vector<lld>> dp(n + 1, vector<lld>(2));
    dp[0][0] = dp[0][1] = 1;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < 2; ++j) {
        int a_next = a[i + 1];
        int b_next = b[i + 1];
        if (j == 1) {
          swap(a_next, b_next);
        }
        // No cambio en i
        if (a[i] <= a_next && b[i] <= b_next) {
          dp[i][j] += dp[i - 1][0];
          dp[i][j] %= MOD;
        }
        // Cambio en i
        if (b[i] <= a_next && a[i] <= a_next) {
          dp[i][j] += dp[i - 1][1];
          dp[i][j] %= MOD;
        }
      }
    }
    cout << (dp[n - 1][0] + dp[n - 1][1]) % MOD << endl;
  }
  return 0;
}
