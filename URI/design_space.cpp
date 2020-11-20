/*
    MST (Minimum spaning tree)
    Conectar con el maximo costo es equivalente
    Es decir mismo algoritmo para "maximum spanning tree"
    https://www.urionlinejudge.com.br/judge/es/problems/view/2683
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
int padre[MAX];

int raiz(int nodo) {
    if (!padre[nodo]) return nodo;
    return padre[nodo] = raiz(padre[nodo]);
}

int MST(vector<pair<int, pii>>& edges) {
    fill(padre, padre + MAX, 0);
    int costo = 0;
    for (auto e : edges) {
        int a, b, c;
        c = e.first;
        tie(a, b) = e.second;
        
        int ra = raiz(a), rb = raiz(b);
        if (ra == rb) continue;
        costo += c;
        padre[ra] = rb;
    }
    return costo;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int,pii>> e(n);
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        e[i] = {c, {a, b}};
    }

    sort(e.begin(), e.end());
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        c = e[i].first;
        tie(a, b) = e[i].second;
    }
    int low = MST(e);
    reverse(e.begin(), e.end());
    int up = MST(e);

    cout << up << "\n";
    cout << low << "\n";

    return 0;
}