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
        int n, m;
        cin >> n >> m;
        if (m == 1) {
            cout << 0 << endl;
        } else {
            cout << min(m, n + 1) << endl;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; j++) {
                // where is 0 located
                int offset = i >= m - 1 ? m - 1 : i + 1;
                cout << (j - offset + m) % m << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
