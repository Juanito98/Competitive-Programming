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
    lld x;
    cin >> n >> k;
    cin >> x;
    vector<lld> arr(n);
    lld s = 0;
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
      s += arr[i];
    }
    lld j = ((lld)(n) * (lld)(k)) - 1ll;
    lld acum = 0;
    while (j >= 0 && acum + s < x) {
      acum += s;
      j -= n;
    }
    while (j >= 0 && acum + arr[j % n] < x) {
      acum += arr[j % n];
      j--;
    }

    cout << (j + 1) << endl;
  }

  return 0;
}
