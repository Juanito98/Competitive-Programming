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

// Starting from 0 and applying s for t seconds,
// how many times will return to 0.
lld f(string s, lld t) {
  int p = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'L') {
      p--;
    } else {
      p++;
    }
    if (p == 0) {
      return t / (i + 1);
    }
  }
  return 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n, x;
    lld k;
    cin >> n >> x >> k;
    string s;
    cin >> s;
    lld ans = 0;
    for (char c : s) {
      if (c == 'L') {
        x--;
      } else {
        x++;
      }
      k--;
      if (x == 0) {
        ans = 1 + f(s, k);
        break;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
