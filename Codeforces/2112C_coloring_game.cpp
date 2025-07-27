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

    sort(arr.begin(), arr.end());
    lld ans = 0;
    for (int k = 2; k < arr.size(); ++k) {
      int bob = max(2 * arr[k], arr.back());
      // We want to find the number of pairs i,j
      // such that i < j < k and arr[i]+arr[j]+arr[k] > bob
      int i = 0;
      for (int j = k - 1; i < j; --j) {
        while (i < j && (arr[i] + arr[j] + arr[k] <= bob)) {
          i++;
        }
        ans += j - i;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
