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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    int n, m;
    cin >> n >> m;
    int cnt[3] = {0};
    for (int i = 0; i < m; ++i) {
      char c;
      cin >> c;
      cnt[c - '0']++;
    }
    for (int i = 1; i <= n; ++i) {
      char ans;
      if (m == n || cnt[0] >= i || cnt[1] >= (n - i + 1)) {
        ans = '-';
      } else if (cnt[0] + cnt[2] >= i || cnt[1] + cnt[2] >= (n - i + 1)) {
        ans = '?';
      } else {
        ans = '+';
      }
      cout << ans;
    }
    cout << endl;
  }

  return 0;
}
