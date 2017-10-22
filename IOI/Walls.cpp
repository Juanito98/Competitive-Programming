#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 300
using namespace std;

int n, m;
vector < int > pertenece[MAXN];

int pared[MAXN][MAXN];
int matriz[MAXN][MAXN];

int main()
{
    optimizar;
    cin >> m >> n;
    int k;
    cin >> k;
    vector < int > arr(k);
    for(int i = 0; i < k; i++)
        cin >> arr[i];

    int a, b;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= m; j++) matriz[i][j] = (1 << 20);
        matriz[i][i] = 0;
    }
    for(int i = 1; i <= m; i++) {
        cin >> k;
        vector < int > region(k);
        for(int j = 0; j < k; j++) {
            cin >> region[j];
            pertenece[region[j]].push_back(i);
        }
        for(int j = 0; j < k; j++) {
            a = region[j], b = region[(j + 1) % k];
            if(!pared[a][b]) {
                pared[a][b] = pared[b][a] = i;
                continue;
            }
            matriz[pared[a][b]][i] = matriz[i][pared[a][b]] = 1;
        }
    }
    for(int k = 1; k <= m; k++)
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= m; j++)
                matriz[i][j] = min(matriz[i][j], matriz[i][k] + matriz[k][j]);

    int R = (1 << 20);
    int reg = 1, suma, menor;
    for(int i = 1; i <= m; i++) {
        suma = 0;
        for(int j = 0; j < arr.size(); j++) {
            menor = (1 << 20);
            for(int l = 0; l < pertenece[arr[j]].size(); l++)
                menor = min(menor, matriz[i][pertenece[arr[j]][l]]);
            suma += menor;
        }
        if(suma < R) {
            R = suma;
            reg = i;
        }
    }
    cout << R << "\n" << reg << "\n";
    return 0;
}
