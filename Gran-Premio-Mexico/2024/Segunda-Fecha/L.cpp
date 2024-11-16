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

  int n;
  cin >> n;

  auto read = [n]() {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
      cin >> p[i];
      p[i]--;
    }
    return p;
  };

  auto solve = [n](const vector<int> &p) {
    vector<bool> vis(n, false);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (vis[i]) {
        continue;
      }
      int sz = 0;
      int j = i;
      do {
        sz++;
        vis[j] = true;
        j = p[j];
      } while (j != i);
      ans += sz - 1;
    }
    return ans;
  };

  int ans = solve(read()) + solve(read());

  cout << ans << endl;
  return 0;
}
