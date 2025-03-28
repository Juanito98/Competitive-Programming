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
    int n, k;
    cin >> n >> k;
    vector<lld> arr(n);

    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
    }

    lld ans = 0;
    if (k == 1) {
      ans = arr[0] + arr[n - 1];
      for (int i = 1; i < n - 1; ++i) {
        ans = max(ans, (arr[i] + max(arr[0], arr[n - 1])));
      }
    } else {
      sort(arr.begin(), arr.end());
      reverse(arr.begin(), arr.end());
      for (int i = 0; i < k + 1; ++i) {
        ans += arr[i];
      }
    }
    cout << ans << endl;
  }

  return 0;
}
