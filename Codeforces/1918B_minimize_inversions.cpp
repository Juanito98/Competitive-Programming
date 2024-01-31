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
        vector<pii> A(n);
        for (int i = 0; i < n; ++i) cin >> A[i].first;
        for (int i = 0; i < n; ++i) cin >> A[i].second;
        sort(A.begin(), A.end());
        for (int i = 0; i < n; ++i) cout << A[i].first << ' ';
        cout << '\n';
        for (int i = 0; i < n; ++i) cout << A[i].second << ' ';
        cout << '\n';
    }

    return 0;
}
