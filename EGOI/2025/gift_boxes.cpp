// https://open.kattis.com/problem-sources/European%20Girls%27%20Olympiad%20in%20Informatics%202025
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

int range_length(const pii &p) { return p.second - p.first + 1; }

struct Sublist {
  std::queue<int> q;
  std::set<int> elems;
  int i = 0;
  int j = -1;

  void enqueue(int x) {
    if (elems.count(x) > 0) {
      throw "Can't add a duplicated entry";
    }
    q.push(x);
    elems.insert(x);
    j++;
  }

  void dequeue() {
    elems.erase(q.front());
    q.pop();
    i++;
  }

  bool mem(int x) { return elems.count(x) > 0; }

  pii range() { return {i, j}; }

  bool matches(std::function<bool(const pii &)> criteria) {
    return criteria(range());
  }
};

pii sliding_window(const std::vector<int> arr,
                   std::function<bool(const pii &)> criteria) {
  Sublist acc;
  pii best = acc.range();
  for (auto x : arr) {
    while (acc.mem(x)) {
      acc.dequeue();
    }
    acc.enqueue(x);
    best = (acc.matches(criteria) &&
            range_length(acc.range()) > range_length(best))
               ? (acc.range())
               : best;
  }
  return best;
}

pii solve(std::vector<int> arr) {
  int n = arr.size();
  arr.insert(arr.end(), arr.begin(), arr.end());
  pii p = sliding_window(arr, [&](const pii &p) {
    return p.first == 0 || p.second == (n - 1) ||
           (p.first < n && p.second >= n);
  });
  if (p.first == 0) {
    return {p.second + 1, n - 1};
  } else if (p.second == (n - 1)) {
    return {0, p.first - 1};
  } else {
    return {(p.second % n) + 1, p.first - 1};
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t, n;
  cin >> t >> n;

  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  pii s = solve(arr);
  cout << s.first << " " << s.second << endl;

  return 0;
}
