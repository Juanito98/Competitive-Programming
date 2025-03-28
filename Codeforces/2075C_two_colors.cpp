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
    cin >> k >> n;
    vector<lld> arr(n);

    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
      arr[i] = min(arr[i], k - 1ll);
    }

    lld ans = 0;
    sort(arr.begin(), arr.end());

    int j = n - 1; // (j, n-1] will suffice that a[i] + a[j] >= k
    lld s = 0;
    for (int i = n - 1; i >= 0; i--) {
      while (j > i && arr[i] + arr[j] >= k) {
        s += arr[j];
        j--;
      }
      while (j < n - 1 && arr[i] + arr[j + 1] < k) {
        j++;
        s -= arr[j];
      }
      int cnt = n - 1 - j;
      lld part = (arr[i] - k + 1) * cnt + (s);
      ans += 2 * part;
    }
    cout << ans << endl;
  }

  return 0;
}
