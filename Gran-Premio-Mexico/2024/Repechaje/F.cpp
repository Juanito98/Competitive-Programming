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

  int n = 5, m = 4;
  int a[n], b[m];

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int j = 0; j < m; ++j) {
    cin >> b[j];
  }
  for (int i = 0; i < n; ++i) {
    bool found = false;
    for (int j = 0; j < m; ++j) {
      if (a[i] == b[j]) {
        found = true;
      }
    }
    if (!found) {
      cout << a[i] << endl;
    }
  }

  return 0;
}
