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



// Solo puedo hacer movimientos hacia arriba
int getMinMovs(int n, int m, int k, vector<vector<char> >& arr) {
    vector<vector<int> > cntX(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i > 0) {
                cntX[i][j] = cntX[i-1][j];
            }
            if (arr[i][j] == 'X') {
                cntX[i][j]++;
            }
        }
    }

    // Si hago v movs hacia arriba, cuantos libres me quedan
    int minMovs = m;
    for (int v = 0; v <= n; ++v) {
        int libre = 0;
        // Vemos si con v hacia arriba me dejo sola la a
        for (int j = 0; j < m; ++j) {
            if (k + v < n && arr[k + v][j] == '.' && cntX[k + v][j]-1 < k) { 
                libre++;
            } else if (k + v >= n && cntX[n-1][j]-1 < k) { 
                libre++;
            }
        }
        minMovs = min(minMovs, m + v - libre);
    }
    return minMovs;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";

        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<char> > arr(n, vector<char>(m, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> arr[i][j];
            }
        }

        int v = getMinMovs(n, m, k-1, arr);
        // Al reves
        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            swap(arr[i], arr[j]);
        }
        v = min(v, getMinMovs(n, m, n-k, arr));

        cout << v << "\n";
    }

    return 0;
}