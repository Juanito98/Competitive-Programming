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
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      arr[i] = {x, i + 1};
    }
    vector<pii> ans;
    for (int x = n - 1; x >= 1; x--) {
      vector<int> bucket(x, -1);
      for (int i = 0; i <= x; ++i) {
        int mod = arr[i].first % x;
        if (bucket[mod] == -1) {
          bucket[mod] = arr[i].second;
        } else {
          ans.push_back({arr[i].second, bucket[mod]});
          swap(arr[i], arr[x]);
          break;
        }
      }
    }
    cout << "YES\n";
    for (int i = ans.size() - 1; i >= 0; --i) {
      cout << ans[i].first << " " << ans[i].second << endl;
    }
  }

  return 0;
}
