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

int letter_value(char c) { return c - 'a'; }

vector<vector<int>> distance(const string &s, int k) {
  int n = s.size();
  vector<vector<int>> ans(s.size(), vector<int>(k, n));
  for (int i = n - 2; i >= 0; i--) {
    for (int j = 0; j < k; ++j) {
      ans[i][j] = ans[i + 1][j];
    }
    ans[i][letter_value(s[i + 1])] = i + 1;
  }
  return ans;
}

vector<int> dp(const vector<vector<int>> &d) {
  int n = d.size();
  int k = d[0].size();
  vector<int> memo(n, 0);
  for (int i = n - 1; i >= 0; --i) {
    int furthest = d[i][0];
    for (int j = 1; j < k; j++) {
      furthest = max(furthest, d[i][j]);
    }
    memo[i] = 1 + (furthest == n ? 0 : memo[furthest]);
  }
  return memo;
}

int solution(const string &s, const string &t, const vector<vector<int>> &d,
             const vector<int> &f) {
  int n = d.size();
  int k = d[0].size();

  int pos = (s[0] == t[0] ? 0 : d[0][letter_value(t[0])]);
  for (int i = 1; i < t.size(); ++i) {
    pos = (pos < n ? d[pos][letter_value(t[i])] : pos);
  }

  return (pos < s.size() ? f[pos] : 0);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;

  vector<vector<int>> d = distance(s, k);
  vector<int> memo = dp(d);

  int m;
  for (cin >> m; m; --m) {
    string t;
    cin >> t;

    cout << solution(s, t, d, memo) << endl;
  }

  return 0;
}
