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
        int n, m, A, B;
        cin >> n >> m >> A >> B;
        if (n + m - 2 >= A || n + m - 2 >= B) {
            cout << "Impossible\n";
        } else {
            cout << "Possible\n";
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (i == 1 && j == 1) {
                        cout << A - n - m + 2 << " ";
                    } else if (i == 1 && j == m) {
                        cout << B - n - m + 2 << " ";
                    } else {
                        cout << 1 << " ";
                    }
                }
                cout << "\n";
            }
        }
    }

    return 0;
}