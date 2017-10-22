#include <iostream>
#include <stack>
#include <queue>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define IZQ (nodo * 2)
#define DER (nodo * 2) + 1
#define MAX_C 202
#define MAX_R 5002
using namespace std;
const int TAM = 16;

int R, C;
int H[MAX_R][MAX_C]; // H[i][j] = dist((i, j) , (i, j + 1))
int V[MAX_R][MAX_C]; // V[i][j] = dist((i, j) , (i + 1, j))

struct segment_tree {
    struct ura {
        int costo[MAX_C][MAX_C];

        void acomoda(const int &piso, int *sol) {
            for(int i = 2; i <= C; i++)
                sol[i] = min(sol[i], sol[i - 1] + H[piso][i - 1]);
            for(int i = C - 1; i; i--)
                sol[i] = min(sol[i], sol[i + 1] + H[piso][i]);
        }

        void solve(const int &A, const int &B, int *sol) {
            for(int i = A; i < B; i++) {
                acomoda(i, sol);
                for(int j = 1; j <= C; j++) sol[j] += V[i][j];
            }
            acomoda(B, sol);
        }

        void llena(const int &A, const int &B) { // (B - A) C^2
            int *sol = new int[C + 2];
            for(int i = 1; i <= C; i++) {
                for(int j = 1; j <= C; j++)
                    sol[j] = j == i ? 0 : (1 << 30);
                solve(A, B, sol);
                for(int j  = 1; j <= C; j++) costo[i][j] = sol[j];
            }
        }

        void merge(const int &c, int i, int j, int ini, int fin, const ura &I, const ura &D) {
            if(i > j) return;
            int med = (i + j) / 2;
            int menor = (1 << 30);
            int p;
            for(int a = ini; a <= fin; a++) {
                if(I.costo[c][a] + D.costo[a][med] < menor) {
                    menor = I.costo[c][a] + D.costo[a][med];
                    p = a;
                }
            }
            costo[c][med] = menor;
            merge(c, i, med - 1, ini, p, I, D);
            merge(c, med + 1, j, p, fin, I, D);
        }

        void merge(const ura &I, const ura &D) {
            for(int i = 1; i <= C; i++)
                merge(i, 1, C, 1, C, I, D);
        }
    };
    ura tree[1500];

    void construye(int nodo, int ini, int fin) {
        if(fin - ini <= TAM) {
            tree[nodo].llena(ini, fin);
        } else {
            int med = (ini + fin) / 2;
            construye(IZQ, ini, med);
            construye(DER, med, fin);
            tree[nodo].merge(tree[IZQ], tree[DER]);
        }
    }

    void update(int nodo, int ini, int fin, int pos) {
        if(ini > pos || fin < pos) return;
        if(fin - ini <= TAM) {
            tree[nodo].llena(ini, fin);
        } else {
            int med = (ini + fin) / 2;
            update(IZQ, ini, med, pos);
            update(DER, med, fin, pos);
            tree[nodo].merge(tree[IZQ], tree[DER]);
        }
    }
};
segment_tree ST;

void changeH(int i, int j, int v) {
    H[i][j] = v;
    ST.update(1, 1, R, i);
}

void changeV(int i, int j, int v) {
    V[i][j] = v;
    ST.update(1, 1, R, i);
}

int escape(int a, int b) {
    return ST.tree[1].costo[a][b];
}

int main()
{
    optimizar;
    cin >> R >> C;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j < C; j++)
            cin >> H[i][j];

        H[i][0] = H[i][C] = (1 << 30);
    }

    for(int i = 1; i < R; i++)
        for(int j = 1; j <= C; j++)
            cin >> V[i][j];

    ST.construye(1, 1, R);

    int E;
    cin >> E;
    int aux, a, b, c;
    for(int i = 1; i <= E; i++) {
        cin >> aux;
        cin >> a >> b;
        a++, b++;
        if(aux == 3) {
            cout << escape(a, b) << "\n";
        } else {
            cin >> c;
            if(aux == 1) changeH(a, b, c);
            else changeV(a, b, c);
        }
    }
    return 0;
}
