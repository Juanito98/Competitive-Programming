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

char sig(char c) { return ((c - 'a' + 1) % ('z' - 'a')) + 'a'; }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  for (cin >> T; T; --T) {
    string s;
    cin >> s;
    bool printed = false;
    for (int i = 0; i < s.size(); ++i) {
      if (!printed && i > 0 && s[i - 1] == s[i]) {
        cout << sig(s[i]);
        printed = true;
      }
      cout << s[i];
    }
    if (!printed) {
      cout << sig(s.back());
    }
    cout << endl;
  }

  return 0;
}
