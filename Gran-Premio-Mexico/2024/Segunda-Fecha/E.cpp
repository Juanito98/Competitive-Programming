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

const int MAXN = 100002;
const int MAXS = 1000002;

pii arr[MAXN];
int ansSz = 0;
pii ans[MAXS];
bool belongsToBiggestTree[MAXN];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  int s = 0;
  for (int i = 0; i < n; ++i) {
    cin >> arr[i].first;
    arr[i].second = i + 1;
    s += arr[i].first - 1;
  }

  sort(arr, arr + n);

  bool possible = true;
  for (int i = 0; i < n; ++i) {
    if (arr[i].first > i + 1) {
      possible = false;
      break;
    }
  }

  if (!possible) {
    cout << "-1\n";
    return 0;
  }

  // cout << s << endl;
  int k = 0;
  belongsToBiggestTree[0] = true;
  for (int i = 1; i < n; ++i) {
    if (arr[i].first == arr[i - 1].first) {
      // Lo unos mismos que i-1
      for (int j = ansSz - 1; j >= 0 && ans[j].first == arr[i - 1].second;
           --j) {
        ans[ansSz++] = {arr[i].second, ans[j].second};
      }
      // Le robamos a i-1 ser el prota
      belongsToBiggestTree[i - 1] = false;
      // Fix k just in case
      k = min(k, i - 1);
    } else {
      ans[ansSz++] = {arr[i].second, arr[i - 1].second};
      int missing = arr[i].first - arr[i - 1].first - 1;
      for (int j = 0; j < missing; ++j) {
        while (belongsToBiggestTree[k]) {
          k++;
        }
        ans[ansSz++] = {arr[i].second, arr[k].second};
        belongsToBiggestTree[k] = true;
      }
    }

    belongsToBiggestTree[i] = true;
  }

  cout << ansSz << endl;
  for (int i = 0; i < ansSz; ++i) {
    cout << ans[i].first << " " << ans[i].second << endl;
  }

  return 0;
}
