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

  int n, m;
  cin >> n;
  cin >> m;

  set<int> antes;

  int ans = 0;
  for (int i = 0; i < m; ++i) {
    int x;
    cin >> x;
    int p = abs(x), sign = (x < 0 ? -1 : 1);
    if (antes.count(p) == 0) {
      if (sign > 0) {
        // Alcanzo a alguien que está despues de mi
        antes.insert(p);
      } else {
        // Alguien que está después de mí me alcanza
        // No-op
      }
    } else {
      if (sign > 0) {
        // Alcanzo alguien que estaba atras de mi
        // Debo dar la vuelta para eso, además todos los que
        // Estaban antes, se pasan a estar después
        ans++;
        antes.clear();
        antes.insert(p);
      } else {
        // Alguien que está detrás de mí me alcanza
        antes.erase(p);
      }
    }
  }
  cout << ans << endl;

  return 0;
}
