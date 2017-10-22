#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 102
#define lld long long int
using namespace std;

int n;
int arr[MAXN];
bool vis[MAXN][MAXN];
lld memo[MAXN][MAXN];

lld DP(int i, int j) {
    if(i > j)
        return 0;

    if(!vis[i][j]) {
        vis[i][j] = true;
        memo[i][j] = max( min(DP(i+1, j-1), DP(i+2, j)) + arr[i],
                          min(DP(i+1, j-1), DP(i, j-2)) + arr[j] );
    }
    return memo[i][j];
}

int main()
{
    optimizar;

    cin >> n;
    lld sum = 0;
    for(int i=1; i<=n; i++) {
        cin >> arr[i];
        sum+= arr[i];
    }

    cout << DP(1, n) << " " << sum - DP(1, n) << "\n";
    return 0;
}
