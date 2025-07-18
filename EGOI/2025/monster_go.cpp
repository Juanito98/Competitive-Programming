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

int min_positive(int a, int b) {
  if (a < 0) {
    return b;
  }
  if (b < 0) {
    return a;
  }
  return min(a, b);
}

int memoC[52][52];
int C(int n, int k) {
  if (k == 0 || n == k) {
    return 1;
  }
  if (!memoC[n][k]) {
    memoC[n][k] = C(n - 1, k - 1) + C(n - 1, k);
  }
  return memoC[n][k];
}

vector<vector<bool>> create_constant(int n, int m, bool v) {
  vector<vector<bool>> ans(n, vector<bool>(m, v));
  return ans;
}

void print_m(const vector<vector<bool>> &a) {
  for (auto row : a) {
    for (auto elem : row) {
      cout << elem;
    }
    cout << endl;
  }
}

vector<vector<bool>> vcat(const vector<vector<bool>> &a,
                          const vector<vector<bool>> &b) {
  vector<vector<bool>> ans;
  for (auto x : a) {
    ans.push_back(x);
  }
  for (auto y : b) {
    ans.push_back(y);
  }
  return ans;
}

vector<vector<bool>> hcat(const vector<vector<bool>> &a,
                          const vector<vector<bool>> &b) {
  vector<vector<bool>> ans;
  for (auto x : a) {
    ans.push_back(x);
  }
  for (int i = 0; i < b.size(); ++i) {
    ans[i].insert(ans[i].end(), b[i].begin(), b[i].end());
  }
  return ans;
}

// Square visualization of nCk
// returns a nCk \times n matrix
vector<vector<bool>> create_nCk_group(int n, int k) {
  if (k == 0) {
    return create_constant(1, n, false);
  }
  if (n == k) {
    return create_constant(1, n, true);
  }
  auto a = create_nCk_group(n - 1, k - 1);
  auto b = create_nCk_group(n - 1, k);
  auto aa = hcat(a, create_constant(a.size(), 1, true));
  auto bb = hcat(b, create_constant(b.size(), 1, false));
  return vcat(aa, bb);
}

int columns(const vector<vector<bool>> &mat) {
  if (mat.size() == 0)
    return 0;
  return mat[0].size();
}

int memo[52][15];
pii argmin[52][15];
// dp(n, m) gives you the minimum number of monsters needed
// to assign m monsters to n friends such that there is no tie.
int dp(int n, int m, int debug = false) {
  if (m == 0 || n == 0) {
    return 0;
  }

  if (!memo[n][m]) {
    memo[n][m] = -1;
    for (int i = 1; i <= m; ++i) {
      // Will assign i monsters to the nn = C(i+k, k) people,
      // using i+k monsters.
      // It remains to assign dp(n-nn, i)
      // and dp(n, m - i)
      if ((m % i) > 0) {
        continue;
      }

      for (int k = 0; C(i + k, k) <= n; ++k) {
        int nn = C(i + k, k);
        int cost = (i + k) * (m / i) + dp(n - nn, m, false);
        memo[n][m] = min_positive(memo[n][m], cost);
        if (cost == memo[n][m]) {
          argmin[n][m] = {i, k};
        }
      }
    }
  }
  if (debug) {
    cout << "n=" << n << ", m=" << m << " -> " << memo[n][m] << endl;
    int i = argmin[n][m].first, k = argmin[n][m].second;
    cout << " i=" << i << ", k=" << k << endl;
    int nn = C(i + k, k);
    cout << "   nn=" << nn << endl;
    dp(n - nn, i, true);
    dp(n, m - i, true);
  }
  return memo[n][m];
}

vector<vector<bool>> assign(int n, int m) {
  if (n == 0 || m == 0) {
    return create_constant(n, 0, false);
  }
  dp(n, m);
  int i = argmin[n][m].first, k = argmin[n][m].second;
  auto a = create_nCk_group(i + k, i);
  int nn = a.size(); // Should be size C (i + k, k);
  a = vcat(a, create_constant(n - nn, columns(a), false));

  auto ans = a;
  for (int j = 1; j < m / i; j++) {
    ans = hcat(ans, a);
  }

  auto b = assign(n - nn, m);
  b = vcat(create_constant(nn, columns(b), false), b);
  return hcat(ans, b);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  const bool debug = false;
  if (debug) {
    for (int n = 1; n <= 50; ++n) {
      cout << "n: " << n << " -> " << dp(n, 12, false) << endl;
      print_m(assign(n, 12));
    }
  }

  int n;
  cin >> n;
  vector<vector<bool>> ans = assign(n, 12);
  for (int i = 0; i < ans.size(); ++i) {
    for (int m = 0; m < ans[i].size(); ++m) {
      if (ans[i][m]) {
        cout << m << " ";
      }
    }
    cout << endl;
  }

  if (debug) {
    print_m(ans);
  }

  return 0;
}
