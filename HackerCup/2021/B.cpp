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

const int MAXN = 52;

int n;
char arr[MAXN][MAXN];

int missingRow[MAXN];
bool canWinRow[MAXN];
int missingColumn[MAXN];
bool canWinColumn[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cin >> n;
        fill(missingRow, missingRow + n + 1, 0);
        fill(missingColumn, missingColumn + n + 1, 0);
        fill(canWinColumn, canWinColumn + n + 1, true);
        fill(canWinRow, canWinRow + n + 1, true);
        
        // Tener cuidado cuando falte 1 para ganar
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> arr[i][j];
                if (arr[i][j] == '.') {
                    missingColumn[j] ++;
                    missingRow[i] ++;
                } else if (arr[i][j] == 'O') {
                    canWinColumn[j] = false;
                    canWinRow[i] = false;
                }
            }
        }

        int ans = -1;
        int ways = 0;
        for (int i = 0; i < n; ++i) {
            // Ver si puedo ganar columna i
            if (canWinColumn[i]) {
                if (ans == -1 || missingColumn[i] < ans) {
                    ans = missingColumn[i];
                    ways = 0;
                }
                if (missingColumn[i] == ans) {
                    ways++;
                }
            }
            // Ver si puedo ganar la fila
            if (canWinRow[i]) {
                if (ans == -1 || missingRow[i] < ans) {
                    ans = missingRow[i];
                    ways = 0;
                }
                if (missingRow[i] == ans) {
                    // Si también puedo ganar la columna con 1, no lo sumo
                    ways++;
                }
            }
        }

        // Corregir si ans = 1
        if (ans == 1) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (canWinRow[i] && canWinColumn[j] && missingColumn[j] == 1 && missingRow[i] == 1 && arr[i][j] == '.')
                        ways--;
                }
            }
        }

        cout << "Case #" << caso << ": ";
        if (ans == -1) {
            cout << "Impossible\n";
        } else {
            cout << ans << " " << ways << "\n";
        }
    }

    return 0;
}