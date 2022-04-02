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
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        const int n = 3, m = 4;
        const int D = 1e6;
        int color[n][m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> color[i][j];
            }
        }
        int ans[m] = {0};
        int s = 0;
        for (int j = 0; j < m; ++j) {
            ans[j] = 1e9;
            for (int i = 0; i < n; ++i) {
                ans[j] = min(ans[j], color[i][j]);
            }
            s += ans[j];
            if (s >= D) {
                ans[j] -= s - D;
                s = D;
            }
        }

        if (s == D) {
            for (int j = 0; j < m; ++j) {
                cout << ans[j] << " ";
            }
            cout << endl;
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}
