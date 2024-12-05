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
    map<int, int> freq;
    {
      int n;
      cin >> n;
      for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        freq[x]++;
      }
    }
    vector<int> arr;
    for (auto it : freq) {
      arr.push_back(it.second);
    }

    sort(arr.begin(), arr.end());
    int ans = 0;
    for (int i = 0; i < arr.size(); ++i) {
      if (arr[i] == 1) {
        ans += ((i & 1) == 0 ? 2 : 0);
      } else {
        ans++;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
