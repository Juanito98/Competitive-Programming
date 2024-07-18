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

const int MAXN = 1000002;

int n, m;
pii arr[MAXN]; // first --> tope, second -> resta

int strat[MAXN];
int dp[MAXN];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  // Read input
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> arr[i].first;
  }
  for (int i = 0; i < n; ++i) {
    int bi;
    cin >> bi;
    arr[i].second = arr[i].first - bi;
  }

  sort(arr, arr + n,
       [](const pii &a, const pii &b) { return a.second < b.second; });

  // Fill the strategy
  {
    int j = 0;
    for (int i = MAXN - 1; i >= 0; i--) {
      strat[i] = -1;
      for (; j < n && arr[j].first > i; j++) {
      }
      if (j < n) {
        strat[i] = arr[j].second;
      }
    }
  }

  // Fill the dp
  for (int i = 0; i < MAXN; ++i) {
    if (strat[i] == -1)
      continue;
    dp[i] = 1ll + dp[i - strat[i]];
  }

  // Answer the queries and calculate the answer
  lld ans = 0;
  for (int i = 0; i < m; ++i) {
    int x;
    cin >> x;
    if (x > arr[0].first) {
      int y = x - arr[0].first;
      lld k = (y + arr[0].second - 1) / arr[0].second;
      ans += k;
      x -= k * arr[0].second;
    }
    ans += dp[x];
  }

  cout << ans * 2ll << endl;

  return 0;
}
