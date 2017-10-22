#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 150002
#define SQRT_N 387
using namespace std;

int n, L, m;
int A[MAXN];

struct ura {
    int tam;
    int arr[SQRT_N * 2 + 2]; // arr[0] = size arr
    pair < int, int > memo[SQRT_N * 2 + 2]; // first -> camaras second -> ultima pos

    void calcula() { // sqrt(n)
        memo[tam + 1].first = 0;
        memo[tam + 1].second = -1;
        int cola = tam;
        for(int i = tam; i >= 1; i--) {
            while(arr[cola] - arr[i] > L) cola--;
            memo[i].first = memo[cola + 1].first + 1;
            memo[i].second = memo[cola + 1].second;
            if(memo[i].second == -1) memo[i].second = arr[i] + L;
        }
    }

    void erase(int x) {
        int i;
        for(i = 1; arr[i] != x; i++);
        for(; i < tam; i++) arr[i] = arr[i + 1];
        tam--;
        calcula();
    }

    void insert(int x) {
        arr[++tam] = x;
        for(int i = tam; arr[i] < arr[i - 1]; i--)
            swap(arr[i], arr[i - 1]);
        calcula();
    }

    int binSearch(int x) { // indice del upper_bound x
        int ini = 1, fin = tam, med;
        while(ini < fin) {
            med = (ini + fin) / 2;
            if(arr[med] > x) {
                fin = med;
            } else {
                ini = med + 1;
            }
        }
        return ini;
    }

    int solve(int &pos) {
        if(arr[tam] <= pos) return 0;
        int donde = binSearch(pos);
        pos = memo[donde].second;
        return memo[donde].first;
    }
};
ura cubeta[SQRT_N + 2];
int tam;

int S[MAXN];
void init() {
    int pos = 0;
    for(int i = 1; i <= tam; i++) {
        for(int j = 1; j <= cubeta[i].tam; j++) S[++pos] = cubeta[i].arr[j];
        cubeta[i].tam = 0;
    }
    tam = 1;
    for(int i = 1; i <= n; i++) {
        if(cubeta[tam].tam == SQRT_N) tam++;
        cubeta[tam].arr[++cubeta[tam].tam] = S[i];
    }
    for(int i = 1; i <= tam; i++)
        cubeta[i].calcula();
}

void elimina(int x) {
    int i;
    for(i = 1; i < tam && cubeta[i].arr[cubeta[i].tam] < x; i++);
    cubeta[i].erase(x);
}

void inserta(int x) {
    int i;
    for(i = 1; i < tam && cubeta[i].arr[cubeta[i].tam] < x; i++);
    cubeta[i].insert(x);
}

int solve() {
    int pos = -1;
    int r = 0;
    for(int i = 1; i <= tam; i++)
        r += cubeta[i].solve(pos);
    return r;
}

int main()
{
    optimizar;
    cin >> n >> L >> m;
    for(int i = 1; i <= n; i++)
        cin >> A[i];

    for(int i = 1; i <= n; i++) S[i] = A[i];
    sort(S + 1, S + n + 1);

    int ind, pos;
    for(int i = 0; i < m; i++) {
        if(!(i % SQRT_N)) init();
        cin >> ind >> pos;
        ind++;
        elimina(A[ind]);
        inserta(pos);
        A[ind] = pos;
        cout << solve() << "\n";
    }
    return 0;
}