#include <bits/stdc++.h>
#define optimizar_cin ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 77
#define MAX_T 30000
using namespace std;
int n, m;

int tope;
int padre[MAX_T];
bool visitados[MAX_T];

int cuantos;
int mayor;

struct ura {
    int a, b, c, d;
};
ura noditos[MAXN][MAXN];

char arr[MAXN][MAXN];
vector < int > lista[MAX_T];

void inicializa() {
    swap(n , m);
    tope= 4 * (n * m);
    for(int i=1; i<=tope; i++) {
        padre[i]= 0;
        visitados[i]=false;
        lista[i].clear();
    }

    mayor=0;
    cuantos=0;
}

void junta() {
    for(int i=1; i <= n; i++) {
        for(int j=1; j <= m; j++) {
            if(j!=m) {
                if(arr[i][j] == '/') {
                    if(arr[i][j+1] == '/') {
                        noditos[i][j+1].b= noditos[i][j].c;
                    } else {
                        noditos[i][j+1].a= noditos[i][j].c;
                    }
                } else {
                    if(arr[i][j+1] == '/') {
                        noditos[i][j+1].b= noditos[i][j].d;
                    } else {
                        noditos[i][j+1].a= noditos[i][j].d;
                    }
                }
            }

            if(i > 1) {
                if(arr[i-1][j] == '/') {
                    if(arr[i][j] == '/') {
                        noditos[i][j].a= noditos[i-1][j].d;
                    } else {
                        noditos[i][j].c= noditos[i-1][j].d;
                    }
                } else {
                    if(arr[i][j] == '/') {
                        noditos[i][j].a= noditos[i-1][j].b;
                    } else {
                        noditos[i][j].c= noditos[i-1][j].b;
                    }
                }
            }

            lista[noditos[i][j].a].push_back(noditos[i][j].b);
            lista[noditos[i][j].b].push_back(noditos[i][j].a);
            lista[noditos[i][j].c].push_back(noditos[i][j].d);
            lista[noditos[i][j].d].push_back(noditos[i][j].c);
        }
    }
}

void recorreCiclo(int ini, int fin) {
    int tam=1;
    while(ini != fin) {
        ini= padre[ini];
        tam++;
    }

    if(ini == -1)
        return;

    mayor= max(mayor, tam);
}

bool hayCiclo;
void buscaCiclo(int nodo, int father) {
    if(!hayCiclo) {
        if(!visitados[nodo]) {
            visitados[nodo]=true;
            padre[nodo]= father;

            for(int i=0; i < lista[nodo].size(); i++)
                buscaCiclo(lista[nodo][i], nodo);
        } else {
            if(padre[nodo] != father && padre[father] != nodo) {
                hayCiclo=true;
                cuantos++;
                recorreCiclo(father, nodo);
            }
        }
    }
}

int main()
{
    optimizar_cin;

    cin >> n >> m;
    int caso=1;
    while( n != 0 || m != 0) {
        inicializa();

        int aux=0;
        for(int i=1; i <= n; i++)
            for(int j=1; j <= m; j++) {
                cin >> arr[i][j];
                noditos[i][j].a = ++aux;
                noditos[i][j].b = ++aux;
                noditos[i][j].c = ++aux;
                noditos[i][j].d = ++aux;
            }

        junta();

        for(int i=1; i <= tope; i++)
            if(!visitados[i]) {
                hayCiclo=false;
                buscaCiclo(i, -1);
            }

        cout << "Maze #" << caso << ":\n";

        if(cuantos == 0) {
            cout << "There are no cycles.\n";
        } else {
            cout << cuantos << " Cycles; the longest has length " << mayor << ".\n";
        }

        cin >> n >> m;
        cout << "\n";

        caso++;
    }
    return 0;
}