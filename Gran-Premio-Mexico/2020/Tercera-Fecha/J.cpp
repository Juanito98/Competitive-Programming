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
#include <utility>
#include <vector>

using namespace std;

typedef int64_t ll;
typedef long double ld;

typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;

#define MINF -1000000000000
#define MOD 1000000007

#define m(a, b) (a % b + b) % b
#define loop(i, a, b) for (int i = a; i < b; ++i)
#define invl(i, a, b) for (int i = a; i > b; --i)

const int maxN = 1005, maxT = 1e4 + 5;
int n, k, o;

int dist[maxN][maxN];
vi adj[maxN];
void bfs(int i) {
    queue<pii> c;
    c.push(pii(i, 0));
    int nd, v;

    bool visited[maxN];
    for (int j = 1; j <= maxN; ++j)
        dist[i][j] = 3 * maxN;

    dist[i][i] = 0;
    fill(visited, visited + n + 5, 0);
    while (!c.empty()) {
        nd = c.front().first;
        v = c.front().second;
        c.pop();
        if (!visited[nd]) {
            visited[nd] = true;
            dist[i][nd] = v;

            //meto a mis hijos con distancia mas uno
            for (int h : adj[nd])
                c.push(pii(h, v + 1));
        }
    }
}

int dest[maxN], mid[maxN], val[maxN];
int dp[maxN][maxT];
bool visited[maxN][maxT];

int DP(int indx, int actual, int tiempo) {
    if (tiempo < 0) return -110000;
    if (indx == o + 1) return 0;
    if (!visited[indx][tiempo]) {
        visited[indx][tiempo] = 1;

        int t1, t2;
        int op1 = -110000, op2 = -110000;
        //voy al intermedio)
        t1 = k * (dist[actual][mid[indx]] + dist[mid[indx]][dest[indx]]);
        if (t1 < 3 * maxN)
            op1 = val[indx] + DP(indx + 1, dest[indx], tiempo - t1);

        //no voy
        t2 = k * (dist[actual][dest[indx]]);
        if (t2 < 3 * maxN)
            op2 = DP(indx + 1, dest[indx], tiempo - t2);

        dp[indx][tiempo] = max(op1, op2);
    }
    return dp[indx][tiempo];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    int m, a, b;
    cin >> n >> m >> k;
    loop(i, 0, m) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    loop(i, 1, n + 1) {
        bfs(i);
    }

    int t;
    cin >> o >> t;
    loop(i, 0, o) {
        cin >> dest[i];
    }
    dest[o] = 1;

    mid[0] = 1;
    val[0] = 0;
    loop(i, 1, o + 1) {
        cin >> mid[i] >> val[i];
    }

    int resp = DP(0, 1, t);
    if (resp < 0)
        cout << "Impossible\n";
    else
        cout << resp << "\n";
}
