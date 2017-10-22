#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 52
#define lld long long int
#define _MEMO memo[a.x][a.y][b.x][b.y]
using namespace std;

struct Pto {
    int x, y;
    Pto(int a, int b) {
        x = a;
        y = b;
    }
    Pto() {
        x = 0, y = 0;
    }
};

Pto make_Pto(int a, int b) {
    Pto P(a, b);
    return P;
}

int raisins[MAXN][MAXN];
int sum[MAXN][MAXN];

int query(int x1, int y1, int x2, int y2) {
    if(x1 > x2 || y1 > y2) return 0;
    int c = sum[x2][y2] + sum[x1-1][y1-1] - sum[x2][y1-1] - sum[x1-1][y2];
    return c;
}

lld memo[MAXN][MAXN][MAXN][MAXN];

lld DP(Pto a, Pto b) {
    if(a.x == b.x && a.y == b.y) return 0;
    if(!_MEMO) {
        _MEMO = INFINITY;
        for(int x = a.x; x < b.x; x++)
            _MEMO = min(_MEMO, DP(a, make_Pto(x, b.y)) + DP(make_Pto(x+1, a.y), b));
        for(int y = a.y; y < b.y; y++)
            _MEMO = min(_MEMO, DP(a, make_Pto(b.x, y)) + DP(make_Pto(a.x, y+1), b));
        _MEMO += query(a.x, a.y, b.x, b.y);
    }
    return _MEMO;
}

int main()
{
    optimizar;
    int n, m;
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            cin >> raisins[i][j];
            sum[i][j] = query(1, 1, i-1, j) + query(i, 1, i, j-1) + raisins[i][j];
        }
    }

    cout << DP(make_Pto(1, 1), make_Pto(n, m));
    return 0;
}
