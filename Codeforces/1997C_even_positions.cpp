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
    cin >> n;
    string s;
    cin >> s;
    stack<int> st; // Guarda indices de los parentesis que voy dejando abierto
    lld ans = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (s[i] == '_') {
        if (i == 0 || s[i - 1] != '(') {
          s[i] = '(';
        } else {
          s[i] = ')';
        }
      }

      if (s[i] == ')') {
        st.push(i);
      } else if (s[i] == '(') {
        int j = st.top();
        st.pop();
        ans += j - i;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
