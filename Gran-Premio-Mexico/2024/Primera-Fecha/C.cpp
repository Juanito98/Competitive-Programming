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

  lld shipping[3];
  for (int i = 0; i < 3; ++i) {
    cin >> shipping[i];
  }
  lld box[3];
  for (int i = 0; i < 3; ++i) {
    cin >> box[i];
  }

  // Every permutation of 3
  int p[6][3] = {
      {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0},
  };

  lld ans = 0;
  for (int k = 0; k < 6; ++k) {
    lld aux = 1;
    for (int i = 0; i < 3; ++i) {
      aux *= shipping[i] / box[p[k][i]];
    }
    ans = max(ans, aux);
  }
  cout << ans << "\n";
  return 0;
}
