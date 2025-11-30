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
    vector<int> p(n + 1);
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; ++i) {
      cin >> p[i];
      pos[p[i]] = i;
    }

    {
      int j = n;
      for (int i = 1; i <= n; ++i) {
        if (p[i] == 0) {
          while (pos[j] > 0) {
            j--;
          }
          p[i] = j;
          pos[j] = i;
        }
      }
    }

    int ans = n;
    {
      int i = 1, j = n;
      while ((p[i] == i || p[j] == j) && i <= j) {
        if (p[i] == i) {
          i++;
        } else {
          j--;
        }
        ans--;
      }
    }

    cout << ans << endl;
  }
  return 0;
}
