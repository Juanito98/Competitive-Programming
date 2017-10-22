#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 1000002
using namespace std;

int N;
int n, k;
int arr[MAXN];

bool valido(int d) {
    int ini = 1, fin = 2;
    int c = 0;
    while(ini < N && ini < fin) {
        if(arr[ini + 1] - arr[ini] <= d) {
            c++;
            ini++;
            fin += 2 * k;
        }
        ini++;
    }
    return c >= n;
}

int binSearch(int ini, int fin) {
    int med;
    while(ini < fin) {
        med = (ini + fin) / 2;
        if(valido(med)) fin = med;
        else ini = med + 1;
    }
    return ini;
}

int main()
{
    optimizar;
    while(cin >> n >> k) {
        N = n * k * 2;
        for(int i = 1; i <= N; i++) cin >> arr[i];
        sort(arr + 1, arr + N + 1);
        cout << binSearch(0, arr[N] - arr[1]) << endl;
    }
    return 0;
}
