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
    int n, x;
    cin >> n >> x;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
    }
    // f[i] is the number of subarrays starting from i
    // that ends up with score greater than 0
    vector<int> f(n);
    lld ans = 0;
    int j = n - 1;
    int s = 0;
    for (int i = n - 1; i >= 0; --i) {
      s += arr[i];
      while (s > x) {
        s -= arr[j];
        j--;
      }
      f[i] = (j - i + 1) + (j + 2 < n ? f[j + 2] : 0);
      ans += f[i];
    }
    cout << ans << endl;
  }

  return 0;
}
