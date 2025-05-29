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
    int n;
    cin >> n;
    vector<lld> arr(n);
    vector<lld> L(n);
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
      L[i] = arr[i];
      if (i > 0)
        L[i] = max(L[i], L[i - 1]);
    }
    lld s = 0;
    for (int k = 1; k <= n; k++) {
      s += arr[n - k];
      lld ans = max(s, k == n ? 0 : (s - arr[n - k] + L[n - k - 1]));
      cout << ans << " \n"[k == n];
    }
  }

  return 0;
}
