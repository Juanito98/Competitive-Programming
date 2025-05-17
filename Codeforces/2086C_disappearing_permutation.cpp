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
  for (cin >> T; T; T--) {
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    vector<bool> replaced(n + 1, false);
    for (int i = 0; i < n; ++i) {
      cin >> arr[i + 1];
    }
    int ans = 0;
    for (int q = 0; q < n; ++q) {
      int p;
      cin >> p;
      while (!replaced[p]) {
        replaced[p] = true;
        ans++;
        p = arr[p];
      }
      cout << ans << " \n"[q == (n - 1)];
    }
  }

  return 0;
}
