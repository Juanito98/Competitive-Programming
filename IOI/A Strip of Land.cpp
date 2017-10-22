#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 702
using namespace std;

int n, m, c;
int arr[MAXN][MAXN];
int ant = 0, act = 1;
int h[2][12][MAXN];

int r;
int _x1, _y1, _x2, _y2;

int main()
{
    optimizar;
    cin >> m >> n >> c;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) cin >> arr[i][j];
    int suma;
    for(int i = 1; i <= n; i++) {
        swap(ant, act);
        for(int j = 1; j <= m; j++) {
            for(int d = 0; d <= c; d++) {
                h[act][d][j] = 1;
                if(d - (arr[i-1][j] - arr[i][j]) >= 0 && d - (arr[i-1][j] - arr[i][j]) <= c)
                    h[act][d][j] += h[ant][d - (arr[i-1][j] - arr[i][j])][j];
                suma = h[act][d][j];
                for(int k = j; k > max(j - 100, 0); k--) {
                    if((j - k + 1) * suma > r) {
                        r = (j - k + 1) * suma;
                        _x1 = i - suma + 1, _x2 = i;
                        _y1 = k, _y2 = j;
                    }
                    if(d - (arr[i][k - 1] - arr[i][j]) < 0) break;
                    if(d - (arr[i][k - 1] - arr[i][j]) > c) break;
                    suma = min(suma, h[act][d - (arr[i][k-1] - arr[i][j])][k - 1]);
                }
            }
        }
    }
    cout << _y1 << " " << n - _x2 + 1 << " " << _y2 << " " << n - _x1 + 1 << "\n";
    return 0;
}
