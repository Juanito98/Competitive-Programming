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

  int Q;
  for (cin >> Q; Q; --Q) {
    int n, t;
    cin >> n >> t;
    // Cuenta divisores de k = t-1
    // menores a n
    auto solve = [&]() {
      int k = t - 1;
      if (k == 0) {
        return n;
      }
      int ans = 0;
      for (int d = 1; d * d <= k && d <= n; d++) {
        if ((k % d) != 0)
          continue;
        ans++;
        int p = k / d;
        if (p != d && p <= n) {
          ans++;
        }
      }
      return ans;
    };
    cout << solve() << endl;
  }

  return 0;
}
