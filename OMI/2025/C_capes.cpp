#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <complex>
#include <functional>
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

int check(int i, int were_facing_right, int should_face_left,
          const vector<int> &arr) {
  if (should_face_left < 0 || should_face_left > arr.size()) {
    return 0;
  }
  if (were_facing_right < 0 || were_facing_right > arr.size()) {
    return 0;
  }
  if (i >= arr.size()) {
    return (should_face_left == 0 && were_facing_right <= arr.size()) ? 1 : 0;
  }
  if (arr[i] == were_facing_right + should_face_left) {
    // must be facing left
    return check(i + 1, were_facing_right, should_face_left - 1, arr);
  } else if (arr[i] == were_facing_right + should_face_left + 1) {
    // must be facing right
    return check(i + 1, were_facing_right + 1, should_face_left,
                 arr); // facing right
  }
  return 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  for (cin >> t; t; --t) {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
    }
    int ans = check(1, 0, arr[0] - 1, arr) + check(1, 1, arr[0] - 1, arr);
    cout << ans << endl;
  }

  return 0;
}
