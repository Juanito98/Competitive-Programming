/*
    Trie
    https://csacademy.com/contest/archive/task/xor-submatrix/statement/
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

struct trie {
    const int LOG_N = 30;
    struct node {
        int sz;
        node *l, *r;
    };
    node *raiz;
    trie() {
        raiz = new node();
    }

    void add(int x) {
        node* it = raiz;
        for (int i = LOG_N; i >= 0; --i) {
            it->sz++;
            if (x & (1 << i)) {
                if (!it->l) it->l = new node();
                it = it->l;
            } else {
                if (!it->r) it->r = new node();
                it = it->r;
            }
        }
        it -> sz++;
    }

    int maxXor(int x) {
        int ans = 0;
        node *it = raiz;
        if (it -> sz == 0) return -1;  // no hay con quien
        for (int i = LOG_N; i >= 0; --i) {
            if (x & (1 << i)) {
                // Quiero ir a la derecha
                if (it->r && it->r->sz > 0) {
                    ans |= 1 << i;
                    it = it->r;
                } else {
                    it = it->l;
                }
            } else {
                if (it->l && it->l->sz > 0) {
                    ans |= 1 << i;
                    it = it->l;
                } else {
                    it = it->r;
                }
            }
        }
        return ans;
    }

} T;

int n, m;
int A[MAX], B[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i) 
        cin >> A[i];
    for (int i = 0; i < m; ++i)
        cin >> B[i];

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        int etzor = 0;
        for (int j = i; j < n; ++j) {
            etzor ^= A[j];
            if ((j-i+1) & 1) T.add(etzor);
            else ans = max(ans, etzor);
        }
    }

    for (int i = 0; i < m; ++i) {
        int etzor = 0;
        for (int j = i; j < m; ++j) {
            etzor ^= B[j];
            if ((j - i + 1) & 1) 
                ans = max(ans, T.maxXor(etzor));
            else ans = max(ans, etzor);
        }
    }

    cout << ans << "\n";

    return 0;
}