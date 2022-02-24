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
typedef pair<lld, lld> pii;



int n, m, k;
vector<vector<int> > matriz;
vector<pii> arr;
lld T;

void init(vector<vector<int> >& matriz, vector<vector<int> >& U, vector<vector<int> >& L) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            L[i][j] = U[i][j] = matriz[i][j];
            if (i > 0) U[i][j] += U[i - 1][j];
            if (j > 0) L[i][j] += L[i][j - 1];
        }
}

int cnt_ones(pii ini, pii fin, vector<vector<int> >& U, vector<vector<int> >& L) {
    if (ini > fin) swap(ini, fin);
    if (ini.first == fin.first) {
        if (ini.second == 0) return L[ini.first][fin.second];
        return L[ini.first][fin.second] - L[ini.first][ini.second - 1];
    }
    if (ini.first == 0) return U[fin.first][ini.second];
    return U[fin.first][ini.second] - U[ini.first - 1][ini.second];
}

int cnt_zeroes(pii& ini, pii& fin, vector<vector<int> >& U, vector<vector<int> >& L) {
    return abs(ini.first - fin.first) + abs(ini.second - fin.second) + 1 - cnt_ones(ini, fin, U, L);
}

void add(pii ini, pii fin, int v, vector<vector<int> >& U, vector<vector<int> >& L) {
    if (ini > fin) swap(ini, fin);
    if (ini.first == fin.first) {
        L[ini.first][ini.second] += v;
        if (fin.second < m - 1) L[ini.first][fin.second + 1] -= v;
    } else {
        U[ini.first][ini.second] += v;
        if (fin.first < n - 1) U[fin.first + 1][ini.second] -= v;
    }
}

pii next_pos(pii& pos, int d, int l) {
    if (d == 0)
        return {pos.first - l, pos.second};
    else if (d == 1)
        return {pos.first, pos.second - l};
    else if (d == 2)
        return {pos.first, pos.second + l};
    return {pos.first + l, pos.second};
}

bool possible(lld t) {
    vector<vector<int> > new_matriz = matriz;
    // Vectores de banderas
    vector<vector<int> > L(n, vector<int>(m, 0));
    vector<vector<int> > U(n, vector<int>(m, 0));

    pii curr = {n - 1, 0};
    for (int i = 0; i < arr.size(); ++i) {
        pii sig = next_pos(curr, arr[i].first, arr[i].second);
        if (arr[i].second < t) {
            t -= arr[i].second;
        } else {
            // Avanzamos t
            curr = next_pos(curr, arr[i].first, t);
            t = 0;
            // Sumamos 1 a ese rango
            add(curr, sig, 1, U, L);
        }
        curr = sig;
    }

    // Sumamos las banderas
    // Creamos la nueva matriz normalizada
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (i > 0) U[i][j] += U[i - 1][j];
            if (j > 0) L[i][j] += L[i][j - 1];
            new_matriz[i][j] += U[i][j] + L[i][j];
            if (new_matriz[i][j] > 1)
                new_matriz[i][j] = 1;
        }

    init(new_matriz, U, L);

    // Checamos que no hayan ceros
    curr = {n - 1, 0};
    for (auto p : arr) {
        pii sig = next_pos(curr, p.first, p.second);
        if (cnt_zeroes(sig, curr, U, L) > 0) {
            return false;
        }
        curr = sig;
    }
    return true;
}

bool missingPosition() {
    vector<vector<int> > new_matriz = matriz;
    // Vectores de banderas
    vector<vector<int> > L(n, vector<int>(m, 0));
    vector<vector<int> > U(n, vector<int>(m, 0));

    pii curr = {n - 1, 0};
    for (int i = 0; i < arr.size(); ++i) {
        pii sig = next_pos(curr, arr[i].first, arr[i].second);
        add(curr, sig, -1, U, L);
        curr = sig;
    }

    // Sumamos las banderas
    // Creamos la nueva matriz normalizada
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (i > 0) U[i][j] += U[i - 1][j];
            if (j > 0) L[i][j] += L[i][j - 1];
            new_matriz[i][j] += U[i][j] + L[i][j];
            if (new_matriz[i][j] >= 1)
                return true;
        }

    return false;
}

pii solve() {
    vector<vector<int> > L(n, vector<int>(m, 0));
    vector<vector<int> > U(n, vector<int>(m, 0));
    init(matriz, U, L);
    T = 1;

    if (missingPosition()) return {-1, -1};

    // Lets find the min time
    pii ini = {n - 1, 0};
    pii fin = {n - 1, 0};
    for (auto p : arr) {
        fin = next_pos(fin, p.first, p.second);
        T += p.second;
    }

    lld t = T;
    // A partir de la ultima posicion vemos donde se corta
    pii curr = fin;
    for (int i = arr.size() - 1; i >= 0; --i) {
        pii sig = next_pos(curr, (arr[i].first ^ 3), arr[i].second);
        if (cnt_ones(sig, curr, U, L) > 0) {
            // Stop here
            while (matriz[curr.first][curr.second] == 0) {
                t--;
                curr = next_pos(curr, (arr[i].first ^ 3), 1);
            }
            break;
        }
        t -= arr[i].second;
        curr = sig;
    }
    if (matriz[curr.first][curr.second] == 0)
        t--;

    if (!possible(t)) return {-1, -1};

    lld l = t, r = T;
    while (l < r) {
        lld med = (l + r + 1) / 2;
        if (possible(med)) {
            l = med;
        } else {
            r = med - 1;
        }
    }

    return {t, l};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    cin >> n >> m >> k;
    arr.resize(k);
    matriz.resize(n);
    for (int i = 0; i < n; ++i) {
        matriz[i].resize(m);
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            if (c == '#') matriz[i][j] = 1;
        }
    }

    for (int i = 0; i < k; ++i) {
        string s;
        cin >> s >> arr[i].second;
        if (s == "up")
            arr[i].first = 0;
        else if (s == "down")
            arr[i].first = 3;
        else if (s == "left")
            arr[i].first = 1;
        else if (s == "right")
            arr[i].first = 2;
    }

    pii ans = solve();

    cout << ans.first << " " << ans.second << "\n";

    return 0;
}