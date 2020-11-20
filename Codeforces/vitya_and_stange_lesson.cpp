/*
    Trie
    https://codeforces.com/contest/842/problem/D
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

const int LOG_N = 20;

struct trie {
    struct node {
        int sz;
        node *l, *r;
    };
    node* raiz;

    trie() {
        raiz = new node();
    }

    void add(int x, int i, node *nodo) {
        if (i < 0) {
            nodo -> sz = 1;
            return;
        }
        if (!nodo->r) nodo->r = new node();
        if (!nodo->l) nodo->l = new node();
        if (x & (1 << i)) {
            // Left
            add(x, i-1, nodo->l);
        } else {
            // Right
            add(x, i-1, nodo->r);
        }
        nodo->sz = nodo->l->sz + nodo->r->sz;
    }
    void add (int x) { add(x, LOG_N, raiz); }

    int mex(int x) { // mex de todos xor x
        node* it = raiz;
        int ans = 0;
        for (int i = LOG_N; i >= 0; --i) {
            if (x & (1 << i)) {
                // Izquierda va primero
                if (!it || !it->l || it->l->sz < (1 << i)) {
                    // La respuesta esta en el menor
                    if (it) it = it -> l;
                } else {
                    // La respuesta esta en mayor
                    ans |= (1 << i);
                    if (it) it = it -> r;
                }
            } else {
                // Derecha va primero
                if (!it || !it->r || it->r->sz < (1 << i)) {
                    // La respuesta esta en el menor
                    if (it) it = it->r;
                } else {
                    // La respuesta esta en mayor
                    ans |= (1 << i);
                    if (it) it = it->l;
                }
            }
        }
        return ans;
    }

} T;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.add(x);
    }

    int x = 0;
    for (int i = 0; i < m; ++i) {
        int y;
        cin >> y;
        x ^= y;
        cout << T.mex(x) << "\n";
    }


    return 0;
}