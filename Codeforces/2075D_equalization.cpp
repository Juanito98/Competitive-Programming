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

int msb(lld x) {
  int b = 0;
  for (b = 0; x > 1; b++)
    x >>= 1;
  return b;
}

lld min_pos(lld x, lld y) {
  if (x < 0)
    return y;
  if (y < 0)
    return x;
  return min(x, y);
}

lld memo[100][100][100];
lld dp(int jx, int jy, int b) {
  if (jx < 0 || jy < 0)
    return -1;
  if (jx == 0 && jy == 0)
    return 0;
  if (jx > 0 && b > jx)
    return -1;
  if (jy > 0 && b > jy)
    return -1;
  if (!memo[jx][jy][b]) {
    lld take = min_pos(dp(jx - b, jy, b + 1), dp(jx, jy - b, b + 1));
    take = (take == -1) ? take : take + (1ll << b);
    memo[jx][jy][b] = min_pos(dp(jx, jy, b + 1), take);
  }
  return memo[jx][jy][b];
}

lld f(lld x, lld y) {
  if (x == y)
    return 0;
  if (x < y)
    swap(x, y);

  int u = msb(x), v = msb(y);
  int jx = 0, jy = 0;

  if (y == 0) {
    jx = u + 1;
  } else {
    jx = u - v;
    x >>= jx;

    while (x != y) {
      x >>= 1;
      y >>= 1;
      jx++;
      jy++;
    }
  }

  lld ans = dp(jx, jy, 1);
  // Tambien puedos saltarlos mas de eso
  for (int i = 1; jx + i < 60 && jy + i < 60; ++i) {
    ans = min_pos(ans, dp(jx + i, jy + i, 1));
  }
  // Tambien puedo hacerlos cero
  for (int ix = u + 1; ix < 60; ix++) {
    if (y == 0) {
      ans = min_pos(ans, dp(ix, 0, 1));
    } else {
      for (int iy = v + 1; iy < 60; iy++) {
        ans = min_pos(ans, dp(ix, iy, 1));
      }
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; T--) {
    lld x, y;
    cin >> x >> y;

    cout << f(x, y) << endl;
  }

  return 0;
}
