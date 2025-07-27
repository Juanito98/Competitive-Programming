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
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
    }

    int ans = -1;

    for (int i = 1; i < n - 1; ++i) {
      if ((arr[i - 1] <= arr[i] && arr[i] >= arr[i + 1]) ||
          (arr[i - 1] >= arr[i] && arr[i] <= arr[i + 1])) {
        ans = 1;
      }
    }

    for (int i = 1; i < n; ++i) {
      if (abs(arr[i - 1] - arr[i]) <= 1) {
        ans = 0;
      }
    }

    cout << ans << endl;
  }

  return 0;
}
