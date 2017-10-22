#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 202
#define lld long long int
#define IZQ (nodo * 2)
#define DER (nodo * 2 + 1)
using namespace std;

int n, m;
char car[MAXN][MAXN];
struct ura {
    int der, abajo;
};
ura arr[MAXN][MAXN];

int solve() {
    int resp = 0, mayor;
    int b, h;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if((n - i + 1) * (m - j + 1) <= resp) continue;
            for(int k = i; k <= n; k++) {
                if((k - i + 1) * (m - j + 1) <= resp) continue;
                for(int l = j; l <= m; l++) {
                    b = min(arr[i][j].abajo, arr[i][l].abajo);
                    if(i + b - 1 < k) continue;
                    h = min(arr[i][j].der , arr[k][j].der);
                    if(j + h - 1 < l) continue;
                    resp = max(resp, (k - i + 1) * (l - j + 1));
                }
            }
        }
    }
    return resp;
}

int main() {
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);
    optimizar;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> car[i][j];

    for(int i = n; i >= 1; i--)
        for(int j = m; j >= 1; j--)
            if(car[i][j] != 'X') {
                arr[i][j].der = arr[i][j + 1].der + 1;
                arr[i][j].abajo = arr[i +1][j].abajo + 1;
            }

    cout << solve() << "\n";
    return 0;
}
