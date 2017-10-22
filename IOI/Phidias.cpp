#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 602
using namespace std;

bool tam[MAXN][MAXN];
bool vis[MAXN][MAXN];
int memo[MAXN][MAXN];

int suma[MAXN][MAXN];

int DP(int i, int j) {
    if(tam[i][j]) return 0;
    if(!vis[i][j]) {
        vis[i][j] = true;
        memo[i][j] = i * j;
        if(suma[i][j]) {
            for(int k = 1; k <= (i+1)/2; k++)
                memo[i][j] = min(memo[i][j], DP(k, j) + DP(i-k, j));
            for(int k = 1; k <= (j+1)/2; k++)
                memo[i][j] = min(memo[i][j], DP(i, k) + DP(i, j-k));
        }
    }
    return memo[i][j];
}

int main()
{
    optimizar;
    int n, m, k;
    cin >> n >> m >> k;
    int a, b;
    for(int i=1; i<=k; i++) {
        cin >> a >> b;
        tam[a][b] = true;
        suma[a][b]++;
    }

    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            suma[i][j]+= suma[i-1][j] + suma[i][j-1];

    cout << DP(n, m) << "\n";
    return 0;
}
