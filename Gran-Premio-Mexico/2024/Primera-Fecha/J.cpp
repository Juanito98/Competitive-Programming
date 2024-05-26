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

const int MAXN = 502;
const int INF = 1e9;

string s;

int memo[MAXN][MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN];
int dp(int i, int j, int k) {
  // cout << i << " " << j << " " << k << endl;
  if (k <= 0) {
    return 0;
  }
  if (k == 1) {
    return i <= j ? 0 : INF;
  }
  if (i == j) {
    return k <= 1 ? 0 : INF;
  }
  if (i > j) {
    return INF;
  }

  if (!vis[i][j][k]) {
    vis[i][j][k] = true;
    memo[i][j][k] = min(min(dp(i + 1, j, k), dp(i, j - 1, k)),
                        dp(i + 1, j - 1, k - 2) + (s[i] == s[j] ? 0 : 1));
  }
  return memo[i][j][k];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  cin >> s;

  cout << dp(0, n - 1, k);

  return 0;
}
