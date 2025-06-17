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
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    lld ans = (lld)(a[0]) * (lld)(n);
    int j = 0;
    for (int i = 0; i < n; i = j + 1) {
      while (j < n - 1 && a[j + 1] == a[i]) {
        j++;
      }
      ans = min(ans, (lld)(a[i]) * (lld)(n - (j - i + 1)));
    }
    cout << ans << endl;
  }

  return 0;
}
