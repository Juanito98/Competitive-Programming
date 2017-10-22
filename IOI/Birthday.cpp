#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 1000002
using namespace std;

int n;

int d[MAXN];
int arr[MAXN];

int get_distance(int i, int f) {
    int c;
    if(f >= i) {
        c = f - i;
        if(i + n - f < c)
            c = -(i + n - f);
    } else {
        c = f + n - i;
        if(i - f < c)
            c = -(i - f);
    }
    return c;
}

int f(int a) {
    int c = a;
    if(c > (n/2)) {
        c = -((n-1) / 2);
        c+= a - (n/2) - 1;
    }
    return abs(c);
}

int solve() {
    int resp = (n / 2);
    sort(d+1, d+n+1);
    int suma = 0;
    int pos = n;
    int aux = d[1] + ((n-1) / 2);
    for(int i = 1; i<=n; i++)
        d[i]-= aux;
    d[n+1] = d[1];
    while(pos) {
        resp = min(resp, max(f(d[pos+1] + suma), f(d[pos] + suma)));
        suma++;
        while(d[pos] + suma > (n/2) && pos) pos--;
    }
    return resp;
}

int main()
{
    optimizar;
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> arr[i];

    int pos = 1;
    for(int i=1; i<=n; i++) {
        d[i] = get_distance(arr[i], pos);
        pos++;
        if(pos > n) pos = 1;
    }
    int menor = solve();
    pos = 1;
    for(int i=1; i<=n; i++) {
        d[i] = get_distance(arr[i], pos);
        pos--;
        if(!pos) pos = n;
    }
    menor = min(menor, solve());
    cout << menor << "\n";
    return 0;
}
