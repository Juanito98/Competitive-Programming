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
        cout << "Case #" << caso << ":\n";
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < 2 * n + 1; ++i) {
            for (int j = 0; j < 2 * m + 1; ++j) {
                if (i == 0 && j < 2) {
                    cout << ".";
                } else if (j == 0 && i < 2) {
                    cout << ".";
                } else if ((i & 1) && (j & 1)) {
                    cout << ".";
                } else if ((i & 1) && !(j & 1)) {
                    cout << "|";
                } else if (!(i & 1) && (j & 1)) {
                    cout << "-";
                } else if (!(i & 1) && !(j & 1)) {
                    cout << "+";
                }
            }
            cout << "\n";
        }
    }

    return 0;
}
