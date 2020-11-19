/*
    BFS
    https://codeforces.com/contest/877/problem/D
*/
#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
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

const int MAX = 1002;

int n, m, k;
char arr[MAX][MAX];
int vis[MAX][MAX];

int xf, yf;

const int movs[4][2] = {
    0, -1,
    0, 1,
    1, 0,
    -1, 0
};

int bfs(int i, int j) {
    queue<pii> q;
    q.push({i, j});
    vis[i][j] = 1;
    while (!q.empty()) {
        tie(i, j) = q.front();
        q.pop();
        if (i <= 0 || j <= 0 || i > n || j > m) continue;
        if (arr[i][j] == '#') continue;
        //expandirse
        for (int mov = 0; mov < 4; ++mov) {
            int x = i, y = j;
            int dx = movs[mov][0], dy = movs[mov][1];
            for (int l = 0; l < k; ++l) {
                x += dx;
                y += dy;
                if (x <= 0 || y <= 0 || x > n || y > m) break;
                if (vis[x][y] != 0 && vis[x][y] <= vis[i][j]) break;
                if (arr[x][y] == '#') break;
                if (vis[x][y] == 0) {
                    vis[x][y] = vis[i][j] + 1;
                    q.push({x, y});
                }
            } 
        }
    }
    return vis[xf][yf]-1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> arr[i][j];

    int x, y;
    cin >> x >> y >> xf >> yf;
    cout << bfs(x, y) << "\n";

    return 0;
}