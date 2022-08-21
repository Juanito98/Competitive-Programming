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
typedef pair<int, int> pii;

const int MAXN = 1000002;

int n;
pair<pair<int, int>, int> arr[MAXN]; // arr.first es el pair que define el rango, arr.second es la cantidad de boletos de ese juego

int tfin(int i) {
    return arr[i].first.second;
}
int tini(int i) {
    return arr[i].first.first;
}

// Dado que voy saliendo del juego i, cuál es el índice del juego siguiente que puedo tomar
// -1 si ya no puedo tomar ningún juego 
int sigJuegoPosible(int i) {
    if (i >= n) {
        return -1;
    }
    int ini = i+1, fin = n;
    if (tini(n) < tfin(i)) { // xxxxxxxxxxxxxxx
        return -1;
    }
    while (ini < fin) {
        int med = (ini + fin) / 2; // xv 
        if (tini(med) < tfin(i)) {
            // No puedo jugar en el juego med
            ini = med + 1;
        } else {
            fin = med;
        }
    }
    return ini;
}

int F[MAXN]; // Memorizar F(i) = max fj tal que j >= i
int f[MAXN]; // memorizar feria()
// Dado que tomé el juego i, quiero maximizar la cantidad de boletos
int feria() {
    f[n] = 0;
    F[n] = arr[n].second;
    for (int i = n - 1; i >= 0; --i) {
        int j = sigJuegoPosible(i);
        if (j == -1) {
            f[i] = 0; // no puedes ir a ningun juego
        } else {
            f[i] = F[j];  // maxj f(j) tal que j >= i
        }
        // Calcular F[i]
        F[i] = max(f[i] + arr[i].second, F[i+1]);
    }
    return f[0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i].first.first >> arr[i].first.second >> arr[i].second;
    }
    // Ordenar por inicio el arreglo
    sort(arr + 1, arr + n + 1);
    
    // tenemos un juego 0 ficticio que siempre nos conviene tomar
    // da 0 boletos y no bloquea ningun otro juego
    cout << feria() << "\n";
    

    return 0;
}
