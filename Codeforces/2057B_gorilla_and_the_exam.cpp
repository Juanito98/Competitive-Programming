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
    int n, k;
    cin >> n >> k;
    map<int, int> freq;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      freq[x]++;
    }
    vector<int> arr;
    for (const auto it : freq) {
      arr.push_back(it.second);
    }
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());

    while (k > 0 && arr.size() > 1) {
      int take = min(k, arr.back());
      arr[0] += take;
      k -= take;
      arr[arr.size() - 1] -= take;
      if (arr.back() == 0) {
        arr.pop_back();
      }
    }
    cout << arr.size() << endl;
  }

  return 0;
}
