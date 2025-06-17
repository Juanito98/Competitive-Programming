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

  int T;
  for (cin >> T; T; --T) {
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; ++i) {
      cin >> a[i];
    }
    sort(a.begin(), a.end());
    auto assign = [](int a, int b) {
      cout << a << " " << b << " " << a << " " << b << " " << a << " " << b
           << "\n";
    };

    for (int i = 0, assigned = 0; assigned < n; i++, assigned += 2) {
      assign(a[i], a[m - i - 1]);

      if (assigned + 1 < n) {
        assign(a[m - i - 1], a[i]);
      }
    }
  }

  return 0;
}
