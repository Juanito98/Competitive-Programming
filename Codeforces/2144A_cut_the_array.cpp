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
    int s = 0;
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
      s += arr[i];
    }
    int l = 0, r = 0;
    int s1 = 0, s2 = 0;
    for (int i = 0; i < n; ++i) {
      s1 += arr[i];
      s2 = 0;
      for (int j = i + 1; j < n - 1; ++j) {
        s2 += arr[j];
        int s3 = s - (s1 + s2);

        int m1 = s1 % 3, m2 = s2 % 3, m3 = s3 % 3;
        if ((m1 == m2 && m2 == m3) || (m1 != m2 && m2 != m3 && m1 != m3)) {
          l = i + 1, r = j + 1;
        }
      }
    }
    cout << l << " " << r << endl;
  }
  return 0;
}
