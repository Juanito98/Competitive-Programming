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

  int n, r, c;
  cin >> n >> r >> c;
  r--;
  c--;

  vector<int> ans;

  int active = n;
  vector<int> arr(n, 1);

  auto moveToNextActive = [&](int idx, int step) {
    idx = (idx + step + n) % n;
    while (arr[idx] == 0) {
      idx = (idx + step + n) % n;
    }
    return idx;
  };

  auto moveK = [&](int idx, int step, int k) {
    k %= active;
    for (int i = 0; i < k; ++i) {
      idx = moveToNextActive(idx, step);
    }
    return idx;
  };

  int i = 0, j = n - 1;
  while (active > 0) {
    i = moveK(i, 1, r);
    j = moveK(j, -1, c);

    arr[i] = 0;
    arr[j] = 0;
    if (i == j) {
      ans.push_back(i);
      active--;
    } else {
      active -= 2;
      if (active == 0) {
        ans.push_back(i);
        ans.push_back(j);
      }
    }

    if (active > 0) {
      i = moveToNextActive(i, 1);
      j = moveToNextActive(j, -1);
    }
  }

  sort(ans.begin(), ans.end());
  for (auto x : ans) {
    cout << x + 1 << " ";
  }
  cout << endl;

  return 0;
}
