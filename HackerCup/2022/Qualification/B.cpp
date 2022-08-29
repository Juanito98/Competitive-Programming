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

const int MAXN = 3002;

int n, m;
char arr[MAXN][MAXN];  // #(rock), ^(tree), $(imposible), .(free)

const int movs[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}};

bool ecoNeigh(int i, int j) {
    return i >= 0 && j >= 0 && i < n && j < m && arr[i][j] != '#' && arr[i][j] != '$';
}
int ecoNeighbours(int i, int j) {
    int cnt = 0;
    for (int k = 0; k < 4; ++k) {
        if (ecoNeigh(i + movs[k][0], j + movs[k][1])) {
            cnt++;
        }
    }
    return cnt;
}

// Regresa true si es posible colorear chido
bool colorImpossibleCells() {
    queue<pii> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (arr[i][j] == '#') continue;
            if (ecoNeighbours(i, j) < 2) {
                if (arr[i][j] == '^') return false;
                arr[i][j] = '$';
                q.push({i, j});
            }
        }
    }
    while (!q.empty()) {
        int i = q.front().first, j = q.front().second;
        for (int k = 0; k < 4; ++k) {
            int ii = i + movs[k][0], jj = j + movs[k][1];
            if (ii < 0 || jj < 0 || ii >= n || jj >= m) continue;
            if (arr[ii][jj] == '$' || arr[ii][jj] == '#') continue;
            if (ecoNeighbours(ii, jj) < 2) {
                if (arr[ii][jj] == '^') return false;
                arr[ii][jj] = '$';
                q.push({ii, jj});
            }
        }
        q.pop();
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> arr[i][j];
            }
        }
        // Find impossible cells ($)
        if (colorImpossibleCells()) {
            cout << "Possible\n";
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (arr[i][j] == '.' || arr[i][j] == '^') {
                        cout << "^";
                    } else if (arr[i][j] == '#') {
                        cout << "#";
                    } else if (arr[i][j] == '$') {
                        cout << ".";
                    }
                }
                cout << "\n";
            }
        } else {
            cout << "Impossible\n";
        }
    }

    return 0;
}
