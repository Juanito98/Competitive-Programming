#include <iostream>
#include <vector>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 52
#define lld long long int
using namespace std;

int n;
int v[MAXN];
int arr[MAXN];
char edge[MAXN][MAXN];
int color;

int maximo(int i, int j);

int _memo[MAXN][MAXN];
int _vis[MAXN][MAXN];
int minimo(int i, int j) {
    if(i == j) return v[arr[i]];
    if(_vis[i][j] != color) {
        _vis[i][j] = color;
        _memo[i][j] = 1 << 30;
        for(int k = i; k < j; k++) {
            if(edge[arr[k]][arr[k + 1]] == 't') {
                _memo[i][j] = min(_memo[i][j], minimo(i, k) + minimo(k + 1, j));
            } else {
                _memo[i][j] = min(_memo[i][j], maximo(i, k) * minimo(k + 1, j));
                _memo[i][j] = min(_memo[i][j], minimo(i, k) * maximo(k + 1, j));
                _memo[i][j] = min(_memo[i][j], minimo(i, k) * minimo(k + 1, j));
            }
        }
    }
    return _memo[i][j];
}

int memo[MAXN][MAXN];
int vis[MAXN][MAXN];
int maximo(int i, int j) {
    if(i == j) return v[arr[i]];
    if(vis[i][j] != color) {
        vis[i][j] = color;
        memo[i][j] = -(1 << 30);
        for(int k = i; k < j; k++) {
            if(edge[arr[k]][arr[k + 1]] == 't') {
                memo[i][j] = max(memo[i][j], maximo(i, k) + maximo(k + 1, j));
            } else {
                memo[i][j] = max(memo[i][j], maximo(i, k) * maximo(k + 1, j));
                memo[i][j] = max(memo[i][j], minimo(i, k) * minimo(k + 1, j));
            }
        }
    }
    return memo[i][j];
}

int mayor;
vector < int > resp;

int main()
{
    optimizar;
    cin >> n;
    cin >> edge[n][1];
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        arr[i] = i;
        if(i < n) cin >> edge[i][i + 1];
    }
    mayor = -(1 << 30);
    for(int i = 1; i <= n; i++) {
        color++;
        if(maximo(1, n) > mayor) {
            mayor = maximo(1, n);
            resp.clear();
            resp.push_back(i);
        } else if(maximo(1, n) == mayor) resp.push_back(i);
        for(int j = 1; j < n; j++) swap(arr[j], arr[j + 1]);
    }
    cout << mayor << "\n";
    for(int i = 0; i < resp.size(); i++) cout << resp[i] << " ";
    cout << "\n";
    return 0;
}