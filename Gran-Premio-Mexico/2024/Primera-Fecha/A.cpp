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

const int MAXN = 10002;
const int INF = 1e9;

int n;
int arr[MAXN];

bool vis[MAXN][MAXN];
int memo[MAXN][MAXN];

int dp(int i, int j) {
  if (i >= j) {
    return INF;
  }
  if (!vis[i][j]) {
    vis[i][j] = true;
    memo[i][j] = min(abs(arr[j] - arr[i]), min(dp(i + 1, j), dp(i, j - 1)));
  }
  return memo[i][j];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
  }
  int Q;
  for (cin >> Q; Q; --Q) {
    int a, b;
    cin >> a >> b;
    cout << dp(a, b) << endl;
  }

  return 0;
}
