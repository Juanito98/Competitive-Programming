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
    string s;
    cin >> n;
    cin >> s;
    auto alice = [&](int i) { return s[i] == 'A'; };
    auto bob = [&](int i) { return !alice(i); };
    auto count = [&](auto clause) {
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        if (clause(i)) {
          cnt++;
        }
      }
      return cnt;
    };
    string winner;
    if (alice(0) && alice(n - 1)) {
      winner = "Alice";
    } else if (bob(0) && bob(n - 1)) {
      winner = "Bob";
    } else if (alice(0) && bob(n - 1)) {
      if (n > 2 && count(bob) > 1) {
        winner = "Bob";
      } else {
        winner = "Alice";
      }
    } else { // bob(0) && alice(n-1)
      if (n == 2 || bob(n - 2)) {
        winner = "Bob";
      } else {
        winner = "Alice";
      }
    }

    cout << winner << endl;
  }

  return 0;
}
