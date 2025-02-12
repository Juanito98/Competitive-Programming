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
    vector<int> arr(n);
    bool possible = false;
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
      if (i > 0) {
        int a = arr[i], b = arr[i - 1];
        if (a > b) {
          swap(a, b);
        }
        if (2 * a > b) {
          possible = true;
        }
      }
    }
    cout << (possible ? "YES" : "NO") << endl;
  }

  return 0;
}
