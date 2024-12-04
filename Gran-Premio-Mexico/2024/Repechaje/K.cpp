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

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> ingredientes(n + 1, 0);
  vector<vector<pii>> platillos(m + 1);

  for (int i = 1; i <= n; ++i) {
    cin >> ingredientes[i];
  }

  for (int i = 1; i <= m; ++i) {
    int j;
    for (cin >> j; j; --j) {
      int x, y;
      cin >> x >> y;
      platillos[i].push_back({x, y});
    }
  }

  int ans = 0;
  for (int o = 1; o <= k; ++o) {
    bool fullfilled = true;
    int j;
    for (cin >> j; j; --j) {
      int p;
      cin >> p;
      for (auto ingrediente : platillos[p]) {
        if (ingrediente.second > ingredientes[ingrediente.first]) {
          fullfilled = false;
          break;
        }
        ingredientes[ingrediente.first] -= ingrediente.second;
      }
    }
    if (!fullfilled) {
      break;
    }
    ans++;
  }
  cout << ans << endl;

  return 0;
}
