#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define MAXN 200002
#define MAX_R 25002
using namespace std;
const int SQRT_N = 447;

int n, R, Q;
int num_region[MAXN];
vector < int > hijos[MAXN];
pair < int, int > ordenados[MAXN * 2]; // first -> ind (negativo es fin), second -> region
int sigNodo;

struct _region {
    vector < int > arr;
    void push_back(int x) { arr.push_back(x); }
    int size() { return arr.size() / 2; }

    lld *Q; // de cuantos soy padre ?
    lld *H; // de cuantos soy hijo ?

    stack < pair < int, lld > > pila; // first -> ind, second -> cuantos
    void pop() {
        int aux = pila.top().first, cont = pila.top().second;
        H[aux] += cont;
        pila.pop();
        if(!pila.empty()) {
            aux = pila.top().first, cont += pila.top().second;
            pila.pop();
            pila.push(make_pair(aux, cont));
        }
    }

    void precalcula() {
        Q = new lld [R + 2];
        H = new lld [R + 2];
        for(int i = 1; i <= R; i++) Q[i] = H[i] = 0;

        int cont = 0, aux;
        int i = 0;
        for(int j = 1; j <= sigNodo; j++) {
            if(ordenados[j].first < 0) continue;
            while(i < arr.size() && abs(arr[i]) < ordenados[j].first) {
                cont += arr[i] > 0 ? 1 : -1;
                i++;
            }
            Q[ordenados[j].second] += cont;
        }
        i = 1;
        for(int j = 0; j < arr.size(); j++) {
            if(arr[j] < 0) continue;
            while(i <= sigNodo && ordenados[i].first < arr[j]) {
                if(ordenados[i].first > 0)
                    pila.push(make_pair(ordenados[i].second, 0));
                else
                    pop();
                i++;
            }
            if(!pila.empty()) {
                aux = pila.top().first, cont = pila.top().second;
                pila.pop();
                pila.push(make_pair(aux, cont + 1));
            }
        }
        while(!pila.empty()) pop();
    }

    lld query(const _region &A) {
        int i = 0;
        lld r = 0;
        int cont = 0;
        for(int j = 0; j < A.arr.size(); j++) {
            if(A.arr[j] < 0) continue;
            while(i < arr.size() && abs(arr[i]) < A.arr[j]) {
                cont += arr[i] > 0 ? 1 : -1;
                i++;
            }
            r += cont;
        }
        return r;
    }
};
_region regiones[MAX_R];

void recorre(int nodo) {
    ++sigNodo;
    ordenados[sigNodo] = make_pair(sigNodo, num_region[nodo]);
    regiones[num_region[nodo]].push_back(sigNodo);
    for(int i = 0; i < hijos[nodo].size(); i++)
        recorre(hijos[nodo][i]);
    ++sigNodo;
    ordenados[sigNodo] = make_pair(-sigNodo, num_region[nodo]);
    regiones[num_region[nodo]].push_back(-sigNodo);
}

int main()
{
    optimizar;
    cin >> n >> R >> Q;
    cin >> num_region[1];
    int padre;
    for(int i = 2; i <= n; i++) {
        cin >> padre >> num_region[i];
        hijos[padre].push_back(i);
    }
    recorre(1);
    for(int i = 1; i <= R; i++)
        if(regiones[i].size() >= SQRT_N) regiones[i].precalcula();

    int a, b;
    for(int i = 1; i <= Q; i++) {
        cin >> a >> b;
        if(regiones[a].size() >= SQRT_N) {
            cout << regiones[a].Q[b] << "\n";
        } else if(regiones[b].size() >= SQRT_N) {
            cout << regiones[b].H[a] << "\n";
        } else {
            cout << regiones[a].query(regiones[b]) << "\n";
        }
    }
    return 0;
}
