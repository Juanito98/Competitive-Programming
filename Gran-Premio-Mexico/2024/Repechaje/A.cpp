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
typedef pair<string, string> pss;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  vector<pss> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i].first;
    arr[i].second = arr[i].first;
    sort(arr[i].first.begin(), arr[i].first.end());
  }

  sort(arr.begin(), arr.end());

  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    string s;
    cin >> s;
    string t = s;
    sort(t.begin(), t.end());
    pss p = {t, s};
    auto it = upper_bound(arr.begin(), arr.end(), p);
    int ans;
    if (it == arr.end()) {
      ans = arr.size();
    } else {
      ans = it - arr.begin();
    }
    cout << ans << endl;
  }

  return 0;
}
