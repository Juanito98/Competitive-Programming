/*
    BFS Problem
    https://www.spoj.com/problems/SPIRALGR/
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
typedef pair<int, int> pii;

const int MAX = 1e5;
vector<int> prime;
bool isPrime[MAX];

void sieve() {
    fill(isPrime, isPrime + MAX, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAX; ++i) {
        if (isPrime[i]) {
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size() && i * prime[j] < MAX; ++j) {
            isPrime[i * prime[j]] = false;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

const int mov[4][2] = {
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0}};

const int MAXN = 502;

pii pos[MAX];
bool invalid[MAXN][MAXN];

void init() {
    int x = MAXN/2, y = MAXN/2;
    pos[1] = {x, y};
    int currLen = 2;
    int dir = 0;
    int missing = 2;
    x++;
    for (int i = 2; i < MAX; ++i) {
        pos[i] = {x, y};
        if (isPrime[i]) invalid[x][y] = true;
        missing--;
        if (missing == 0) {
            dir++;
            if (dir == 4) {
                dir = 0;
                x++;
                currLen += 2;
                missing = currLen;
                continue;
            }
            missing = currLen;
        }
        x += mov[dir][0];
        y += mov[dir][1];
    }
}

int caso;
int vis[MAXN][MAXN];
int bfs(pii ini, pii fin) {
    int x, y;
    queue<pii> q;
    q.push(ini);
    int t = 0;
    while (!q.empty()) {
        for (int sz = q.size(); sz; --sz) {
            tie(x, y) = q.front();
            q.pop();
            if (x == fin.first && y == fin.second) return t;
            if (invalid[x][y]) continue;
            if (x < 0 || y < 0 || x >= MAXN || y >= MAXN) continue;
            if (vis[x][y] == caso) continue;
            vis[x][y] = caso;
            for (int k = 0; k < 4; ++k) {
                q.push({x + mov[k][0], y + mov[k][1]});
            }
        }
        t++;
    }
    return -1;
} 

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    sieve();
    init();

    int x, y;
    while (cin >> x >> y) {
        caso++;
        pii u = pos[x];
        pii v = pos[y];
        int ans = bfs(u, v);
        cout << "Case " << caso << ": ";
        if (ans != -1) {
            cout << ans << "\n";
        } else {
            cout << "impossible\n";
        }
    }

    return 0;
}