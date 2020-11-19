/*
    BFS
    https://codeforces.com/contest/769/problem/C
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
bool vis[MAX][MAX];
int tiempo[MAX][MAX];

int x, y;

bool invalid(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) return true;
    if (arr[i][j] == '*') return true;
    return false;
}

void bfs(int i, int j) {
    queue<pii> q;
    q.push({i, j});
    int t = 0;
    while (!q.empty()) {
        for (int sz = q.size(); sz; --sz) {
            tie(i, j) = q.front();
            q.pop();
            if (invalid(i, j)) continue;
            if (vis[i][j]) continue;
            vis[i][j] = true;
            tiempo[i][j] = t;
            q.push({i, j+1});
            q.push({i, j-1});
            q.push({i+1, j});
            q.push({i-1, j});
        }
        t++;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> arr[i][j];
            if (arr[i][j] == 'X') {
                x = i;
                y = j;
                arr[i][j] = '.';
            }
        }
    }
    bfs(x, y);

    if (k & 1 || (invalid(x+1, y) && invalid(x-1, y) && invalid(x, y+1) && invalid(x, y-1))) {
        cout << "IMPOSSIBLE\n";
    } else {
        string ans;
        for (int i = 1; i <= k; ++i) {
            if (!invalid(x + 1, y) && i + tiempo[x + 1][y] <= k) {
                ans.push_back('D');
                x++;
            } else if (!invalid(x, y - 1) && i + tiempo[x][y - 1] <= k) {
                ans.push_back('L');
                y--;
            } else if (!invalid(x, y + 1) && i + tiempo[x][y + 1] <= k) {
                ans.push_back('R');
                y++;
            } else if (!invalid(x - 1, y) && i + tiempo[x - 1][y] <= k) {
                ans.push_back('U');
                x--;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}