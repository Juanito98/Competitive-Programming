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
typedef pair<int, lld> pii;

const int MAXN = 100002;

int n, m;
vector<pii> adj[MAXN];  // first->adyacente, second->peso de la arista

bool vis[MAXN];
int padre[MAXN];
bool dijkstra(int nodoInicial, int nodoFinal) {
    priority_queue<pair<int, pii> > q;  // first -> costo total de llegar al nodo (second) desde el nodo inicial
    q.push({-0, {nodoInicial, -1}});
    while (!q.empty()) {
        int costo = -(q.top().first), nodo = q.top().second.first, p = q.top().second.second;
        q.pop();
        if (vis[nodo]) {
            continue;
        }
        vis[nodo] = true;
        // Al visitar también podemos guardar de dónde vienes
        padre[nodo] = p;
        if (nodo == nodoFinal) {
            vector<int> ans;
            int curr = nodoFinal;
            while (curr != -1) {
                ans.push_back(curr);
                curr = padre[curr];
            }
            while (!ans.empty()) {
                cout << ans.back() << " ";
                ans.pop_back();
            }
            cout << endl;
            return true;
        }
        for (auto p : adj[nodo]) {
            q.push({-(costo + p.second), {p.first, nodo}});
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    // costo mínimo de 1 a todos los nodos con dijstra
    bool posible = dijkstra(1, n);

    if (!posible) {
        cout << "-1\n";
    }

    return 0;
}
