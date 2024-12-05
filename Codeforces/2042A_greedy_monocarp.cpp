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
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
      cin >> arr[i];
    sort(arr.begin(), arr.end());
    int s = 0;
    for (int i = arr.size() - 1; i >= 0 && s + arr[i] <= k; --i)
      s += arr[i];

    cout << k - s << endl;
  }

  return 0;
}
