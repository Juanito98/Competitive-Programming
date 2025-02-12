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
    vector<pii> arr(n);

    vector<int> forced(2 * n + 2, 0);
    for (int i = 0; i < n; ++i) {
      int l, r;
      cin >> l >> r;
      if (l == r) {
        forced[l]++;
      }
      arr[i] = {l, r};
    }

    // prefixSum[i] will give how many values
    // are not forced from 1 to i
    vector<int> prefixSum(2 * n + 2, 0);
    for (int i = 1; i <= 2 * n; ++i) {
      if (forced[i] == 0) {
        prefixSum[i] = 1;
      }
      prefixSum[i] += prefixSum[i - 1];
    }

    for (int i = 0; i < n; ++i) {
      int l, r;
      tie(l, r) = arr[i];
      bool ans;
      if (l == r) {
        ans = forced[l] == 1;
      } else {
        ans = (prefixSum[r] - prefixSum[l - 1] > 0);
      }
      cout << ans;
    }
    cout << endl;
  }

  return 0;
}
