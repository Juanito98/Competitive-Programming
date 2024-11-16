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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  set<pii> s;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    if (a > b) {
      swap(a, b);
    }
    s.insert({a, b});
  }

  if (n == 1) {
    cout << "NO\n";
    return 0;
  }

  cout << "YES\n";

  vector<pii> ans;
  int med = (n + 1) / 2;
  for (int i = 1; i <= med; ++i) {
    for (int j = i + 1; j <= med; ++j) {
      if (s.count({i, j}) == 0) {
        ans.push_back({i, j});
      }
    }
  }

  for (int i = med + 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (s.count({i, j}) == 0) {
        ans.push_back({i, j});
      }
    }
  }

  cout << ans.size() << endl;
  for (auto p : ans) {
    cout << p.first << " " << p.second << endl;
  }

  return 0;
}
