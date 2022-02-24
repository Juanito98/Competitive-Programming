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

const int MAXN = 52;

int n, k;
lld arr[MAXN];
vector<int> adj[MAXN];
int hijo[MAXN], brother[MAXN];

int color;
int vis[MAXN][MAXN][3];
lld memo[MAXN][MAXN][3];
lld dp(int nodo, int m, int conFather) {
    if (nodo == 0) return 0;
    if (vis[nodo][m][conFather] != color) {
        vis[nodo][m][conFather] = color;
        memo[nodo][m][conFather] = 0;
        // Veo cuánto repartir a mi hijo y a mi hermano
        for (int h = 0; h <= m; ++h) {
            // 1. Forma parte de la cadena con el padre
            if (conFather > 0) {
                memo[nodo][m][conFather] =
                    max(memo[nodo][m][conFather],
                        dp(hijo[nodo], h, 1) + dp(brother[nodo], m - h, conFather - 1) + arr[nodo]);
            }
            // 2. Crea una nueva cadena
            if (m > 0 && h > 0) {
                // Creo una siendo el LCA
                memo[nodo][m][conFather] =
                    max(memo[nodo][m][conFather],
                        dp(hijo[nodo], h - 1, 2) + dp(brother[nodo], m - h, conFather) + arr[nodo]);
                // Creo una siendo mi papa el lca, es decir, con un brother
                memo[nodo][m][conFather] =
                    max(memo[nodo][m][conFather],
                        dp(hijo[nodo], h - 1, 1) + dp(brother[nodo], m - h, conFather + 1) + arr[nodo]);
            }
            // 3. No uso a ese nodo ni de chiste
            memo[nodo][m][conFather] = 
                max(memo[nodo][m][conFather],
                    dp(hijo[nodo], h, 0) + dp(brother[nodo], m - h, conFather));
        }
    }
    return memo[nodo][m][conFather];
}

void bfs(int nodo = 1, int p = -1) {
    for (int h : adj[nodo]) {
        if (h == p) continue;
        brother[h] = hijo[nodo];
        hijo[nodo] = h;
        bfs(h, nodo);
    }
}

void clear() {
    color++;
    for (int i = 1; i <= n; ++i)
        adj[i].clear();
    fill(hijo, hijo + n + 1, 0);
    fill(brother, brother + n + 1, 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cin >> n >> k;
        clear();
        for (int i = 1; i <= n; ++i) {
            cin >> arr[i];
        }
        for (int i = 1; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        bfs();
        lld ans = arr[1] + (k > 0 ? dp(hijo[1], k-1, 2) : 0);
        cout << "Case #" << caso << ": ";
        cout << ans << "\n";
    }

    return 0;
}