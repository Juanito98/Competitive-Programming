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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arr(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> arr[i][j];
      }
    }
    if (n == 1 && m == 1) {
      cout << -1 << endl;
    } else {
      for (int idx = 1; idx <= n * m; ++idx) {
        int i = idx / m;
        int j = idx % m;
        if (idx == n * m) {
          i = j = 0;
        }
        cout << arr[i][j] << " ";
        if ((idx % m) == 0) {
          cout << endl;
        }
      }
    }
  }

  return 0;
}
