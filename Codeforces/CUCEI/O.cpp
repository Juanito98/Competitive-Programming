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

const int MAX = 100002;

int n, m, k;
vector<int> adj[MAX];

bool vis[MAX];
bool expandi[MAX];
int bfs(int ini, int fin) {
    queue<int> q;
    int nodo = ini;
    int t = 0;
    q.push(ini);
    while (!q.empty()) {
        for (int sz = q.size(); sz; sz--) {
            nodo = q.front();
            //cout << nodo << " " << t << endl;
            q.pop();
            if (nodo == fin) return t;
            if (vis[nodo]) continue;
            vis[nodo] = true;
            // Vemos hacia donde expandir
            int mod = nodo % k;
            if (!expandi[mod]) {
                expandi[mod] = true;
                for (int u = mod; u <= n; u += k) {
                    q.push(u);
                }
            }
            // expande adjacentes
            for (int u : adj[nodo]) {
                q.push(u);
            }
        }
        t++;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if ((a % k) != (b % k)) {
            adj[a].push_back(b);
        }
    }

    int s, t;
    cin >> s >> t;

    cout << bfs(s, t) << "\n";

    return 0;
}