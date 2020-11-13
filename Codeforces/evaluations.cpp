/*
    Union find
    Problema E. https://codeforces.com/gym/101840
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

const int MAXN = 100002;
int divisor[MAXN];
void init() {
    for (int i = 2; i * i < MAXN; ++i) {
        if (divisor[i]) continue;
        for (int j = i * i; j < MAXN; j += i)
            divisor[j] = i;
    }
}

bool isPrime(int x) {
    if (x <= 1) return false;
    return !divisor[x];
}

bool has2DistFact(int x) {
    if (x <= 1) return false;
    return divisor[x] != 0 && divisor[x / divisor[x]] == 0 && divisor[x] * divisor[x] != x;
}

int n;
int padre[MAXN], sz[MAXN], cnt[MAXN];

int raiz(int nodo) {
    if (!padre[nodo]) return nodo;
    return padre[nodo] = raiz(padre[nodo]);
}

void join(int a, int b) {
    int ra = raiz(a), rb = raiz(b);
    if (ra == rb) return;
    sz[ra] += sz[rb];
    padre[rb] = ra;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (fopen("evaluations.in", "r")) freopen("evaluations.in", "r", stdin);
    init();
    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cin >> n;
        fill(padre + 1, padre + n + 1, 0);
        fill(sz + 1, sz + n + 1, 1);
        fill(cnt + 1, cnt + n + 1, 0);

        vector<pii> primeEdges;
        vector<pii> twoPrimeEgdes;
        for (int i = 1; i < n; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            if (c == 1) {
                join(a, b);
            } else if (isPrime(c)) {
                primeEdges.push_back({a, b});
            } else if (has2DistFact(c)) {
                twoPrimeEgdes.push_back({a, b});
            }
        }
        lld ans = 0;
        for (auto e : primeEdges) {
            int a = e.first, b = e.second;
            int ra = raiz(a), rb = raiz(b);
            ans += (lld)cnt[ra] * (lld)sz[rb] + (lld)sz[ra] * (lld)cnt[rb];
            cnt[ra] += sz[rb];
            cnt[rb] += sz[ra];
        }
        for (auto e : twoPrimeEgdes) {
            int a = e.first, b = e.second;
            int ra = raiz(a), rb = raiz(b);
            ans += (lld)sz[ra] * (lld)sz[rb];
        }
        cout << "Case " << caso << ": " << ans << "\n";
    }

    return 0;
}