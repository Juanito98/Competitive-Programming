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

lld f(lld n) {
  // Number of good numbers from 1 to n
  auto div = [&n](int div) { return n / div; };
  vector<int> p = {2, 3, 5, 7};

  lld ans = 0;
  // take 1
  for (auto x : p) {
    ans += div(x);
  }
  // take 2
  for (auto x : p) {
    for (auto y : p) {
      if (x <= y)
        continue;
      ans -= div(x * y);
    }
  }
  // take 3
  for (auto x : p) {
    ans += div((2 * 3 * 5 * 7) / x);
  }
  ans -= div(2 * 3 * 5 * 7);
  return n - ans - 1;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    lld l, r;
    cin >> l >> r;
    lld ans = f(r) - f(l - 1);
    cout << ans << endl;
  }

  return 0;
}
