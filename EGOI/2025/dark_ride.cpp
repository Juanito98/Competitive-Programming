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

const bool test = false;
struct Interactive {
  vector<int> p;

  Interactive(int n) {
    if (test) {
      for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        p.push_back(x);
      }
    }
  }

  // Returns odd if one end is turned on and the other
  // is turned off. Otherwise, returns 0.
  int ask(const vector<bool> &q) {
    cout << "?";
    for (int i = 0; i < q.size(); ++i) {
      cout << " " << q[i];
    }
    cout << endl;
    if (test) {
      if (q.size() != p.size()) {
        throw "InputError";
      }
      int ends = 0;
      for (int i = 0; i < q.size(); ++i) {
        if (q[i] == 1 && (p[i] == 0 || p[i] == (q.size() - 1))) {
          ends++;
        }
      }
      return ends;
    } else {
      int ans;
      cin >> ans;
      return ans;
    }
  }

  void answer(int a, int b) {
    cout << "! " << a << " " << b << endl;
    if (test) {
      if (a == b) {
        throw "InputError";
      }
      if ((p[a] == 0 || p[a] == (p.size() - 1)) &&
          (p[a] == 0 || p[a] == (p.size() - 1))) {
        cout << "Correct answer!" << endl;
      } else {
        cout << "Incorrect answer" << endl;
      }
    }
  }
};

int count(const vector<bool> &arr) {
  int s = 0;
  for (auto x : arr) {
    if (x) {
      s++;
    }
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  Interactive interactive(n);

  // query (i) means every 2^i
  // And find some query that is odd
  vector<int> queries;
  vector<bool> binSearch;
  for (int i = 0; (1 << i) < n; i++) {
    vector<bool> q(n);
    for (int p = 0; p < n; ++p) {
      q[p] = (p & (1 << i));
    }
    int x = interactive.ask(q);
    queries.push_back(x);

    if (x & 1) {
      binSearch = q;
    }
  }

  // Start the binsearch to find a
  while (count(binSearch) > 1) {
    int med = count(binSearch) / 2;
    vector<bool> l(n);
    vector<bool> r(n);
    int acc = 0;
    // take only the first med turned on bits
    for (int i = 0; i < binSearch.size(); ++i) {
      if (!binSearch[i]) {
        continue;
      }
      if (acc < med) {
        l[i] = true;
      } else {
        r[i] = true;
      }
      acc++;
    }
    if (interactive.ask(l) & 1) {
      binSearch = l;
    } else {
      binSearch = r;
    }
  }

  int a = -1;
  for (int i = 0; i < n; ++i) {
    if (binSearch[i]) {
      a = i;
    }
  }

  // use queries and a position to find b
  int b = 0;
  for (int i = 0; i < queries.size(); ++i) {
    int a_bit = a & (1 << i);
    if (queries[i] & 1) {
      // a and b belong to different set
      b ^= (a_bit ^ (1 << i));
    } else {
      // belong to the same set.
      b ^= a_bit;
    }
  }

  interactive.answer(a, b);

  return 0;
}
