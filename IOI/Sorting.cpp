#include <iostream>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 200002
using namespace std;

int n;
int arr[MAXN];

int M;
int *X, *Y;

int _R;
int P[MAXN], Q[MAXN];

int A[MAXN];
int where[MAXN];
int debe_estar[MAXN];
int ind[MAXN];
int desordenados;

void move(int a, int b) {
    ind[debe_estar[a]] = b;
    ind[debe_estar[b]] = a;
    swap(debe_estar[a], debe_estar[b]);
}

void cambia(int a, int b){
    if(A[a] == a) desordenados++;
    if(A[b] == b) desordenados++;
    if(A[a] == b) desordenados--;
    if(A[b] == a) desordenados--;
    swap(where[A[a]], where[A[b]]);
    swap(A[a], A[b]);
}

bool can(int R) {
    desordenados = 0;
    for(int i = 0; i < n; i++) {
        debe_estar[i] = ind[i] = i;
        A[i] = arr[i];
        if(A[i] != i) desordenados++;
        where[A[i]] = i;
    }
    for(int i = R - 1; i >= 0; i--) move(X[i], Y[i]);
    int pos, ronda = 0;
    for(int i = 0; i < n; i++) {
        if(R == ronda) break;
        if(!desordenados) return true;
        cambia(X[ronda], Y[ronda]);
        move(X[ronda], Y[ronda]);
        pos = ind[i];
        if(pos == where[i]) {
            cambia(X[ronda], Y[ronda]);
            move(X[ronda], Y[ronda]);
        } else {
            P[ronda] = pos, Q[ronda] = where[i];
            cambia(pos, where[i]);
            ronda++;
        }
    }
    while(ronda < R) {
        cambia(X[ronda], Y[ronda]);
        P[ronda] = 0, Q[ronda] = 0;
        ronda++;
    }
    return !desordenados;
}

void solve() {
    int ini = 0, fin = n, med;
    while(ini < fin) {
        med = (ini + fin) / 2;
        if(can(med)) fin = med;
        else ini = med + 1;
    }
    _R = ini;
    can(ini);
}

int main()
{
    optimizar;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> M;
    X = new int[M];
    Y = new int[M];
    for(int i = 0; i < M; i++)
        cin >> X[i] >> Y[i];
    solve();
    cout << _R << "\n";
    for(int i = 0; i < _R; i++)
        cout << P[i] << " " << Q[i] << "\n";
    return 0;
}
