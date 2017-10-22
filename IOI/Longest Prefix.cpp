#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define IZQ (nodo * 2)
#define DER (nodo * 2 + 1)
#define MAXN 10002
#define MAX_Q 500003
#define LOG_N 12
using namespace std;

int n, Q;
int arr[MAX_Q];

struct _nodo {
    bool final;
    int cubeta[26];
};
_nodo trie[400002];
int sigNodo;

void insert(string a) {
    int c = 0;
    for(int i = 0; i < a.size(); i++) {
        if(!trie[c].cubeta[a[i] - 'A'])
            trie[c].cubeta[a[i] - 'A'] = ++sigNodo;
        c = trie[c].cubeta[a[i] - 'A'];
    }
    trie[c].final = true;
}

int fila_1[MAX_Q];
int memo[52];
int node[52];

int f() {
    int nodo;
    for(int i = Q; i >= 1; i--) {
        nodo = trie[0].cubeta[arr[i]];
        for(int len = 1; len <= 50; len++) {
            node[len] = 0;
            memo[len] = 0;
            if(!nodo || i + len - 1 > Q) continue;
            node[len] = nodo;
            nodo = trie[nodo].cubeta[arr[i + len]];
        }
        for(int len = 50; len >= 1; len--) {
            nodo = node[len];
            if(!nodo) continue;
            if(node[len + 1]) memo[len] = memo[len + 1];
            if(trie[nodo].final) {
                memo[len] = max(memo[len], i + len - 1);
                if(trie[0].cubeta[arr[i + len]])
                    memo[len] = max(memo[len], fila_1[i + len]);
            }
        }
        fila_1[i] = memo[1];
    }
    return fila_1[1];
}


int main() {
    optimizar;
    cin >> n;
    string S;
    for(int i = 1; i <= n; i++) {
        cin >> S;
        insert(S);
    }
    cin >> S;
    Q = S.size();
    for(int i = 1; i <= Q; i++)
        arr[i] = S[i - 1] - 'A';

    cout << f() << "\n";
    return 0;
}
