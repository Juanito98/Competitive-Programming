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

    lld n, m;

    cin >> n >> m;

    if (n == 1) {
        cout << m << "\n";
        return 0;
    }

    lld ans = 1;
    for (lld x = 2; x*x <= m; ++x) {
        int cnt = 0;
        while (!(m % x)) {
            cnt++;
            m /= x;
        }
        for (int i = 0; i < cnt / n; ++i)
            ans *= x;
    }

    cout << ans << "\n";

    return 0;
}