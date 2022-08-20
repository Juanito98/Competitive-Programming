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

vector<int> primos = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

const int MAXN = 5002;

int n;
int arr[MAXN];
vector<int> adj[MAXN];
int padre[MAXN];
int hijo[MAXN];
int hermano[MAXN];
int sz[MAXN];

void dfs(int nodo = 1) {
    sz[nodo] = 1;
    for (int h : adj[nodo]) {
        if (h == padre[nodo]) continue;
        padre[h] = nodo;
        if (!hijo[nodo]) {
            hijo[nodo] = h;
        } else {
            hermano[h] = hijo[nodo];
            hijo[nodo] = h;
        }
        dfs(h);
        sz[nodo] += sz[h];
    }
}

const int LIMIT = 10002;
bool vis[MAXN][LIMIT];
int memo[MAXN][LIMIT];
// Padre es ¿cuánto vale mi padre al momento?
// 0 significa que no lo cambié
int dp(int nodo, int valor_padre) {
    if (valor_padre >= LIMIT) {
        return LIMIT;
    }
    if (vis[nodo][valor_padre]) {
        return memo[nodo][valor_padre];
    }
    vis[nodo][valor_padre] = true;
    memo[nodo][valor_padre] = LIMIT;
    // Decidir sobre el valor de la arista con el padre
    for (int prime : primos) {
        int newPadre = (valor_padre % prime == 0 ? valor_padre : valor_padre * prime);
        bool padreEsMultiplo = (arr[padre[nodo]] % newPadre == 0);
        bool hijoEsMultiplo = (arr[nodo] % prime == 0);
        if (!hermano[nodo] && !hijo[nodo]) {
            memo[nodo][valor_padre] = min(memo[nodo][valor_padre],
                                          (hijoEsMultiplo ? 0 : prime) + (padreEsMultiplo ? 0 : newPadre));
        } else if (!hermano[nodo]) {
            memo[nodo][valor_padre] = min(memo[nodo][valor_padre],
                                          dp(hijo[nodo], prime) + (padreEsMultiplo ? 0 : newPadre));
        } else if (!hijo[nodo]) {
            memo[nodo][valor_padre] = min(memo[nodo][valor_padre],
                                          (hijoEsMultiplo ? 0 : prime) + dp(hermano[nodo], newPadre));
        } else {
            memo[nodo][valor_padre] = min(memo[nodo][valor_padre], dp(hijo[nodo], prime) + dp(hermano[nodo], newPadre));
        }
    }
    return memo[nodo][valor_padre];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs();
    cout << dp(1, 1) << endl;
    return 0;
}
