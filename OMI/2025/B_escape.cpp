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

  int t;
  for (cin >> t; t; --t) {
    int n, k;
    cin >> n >> k;
    if (n * n - 1 == k) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          int cnt = (i * n) + j;
          if (cnt < k) {
            cout << "U";
          } else {
            // Redirect to a cycle in the bottom corner
            if (i < n - 1) {
              cout << "D";
            } else if (j < n - 1) {
              cout << "R";
            } else {
              cout << "L";
            }
          }
        }
        cout << endl;
      }
    }
  }

  return 0;
}
