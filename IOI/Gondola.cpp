#include <bits/stdc++.h>
#define MAXN 100002
#define MOD 1000000009
#define lld long long int
using namespace std;

int es_secuencia(int s, int arr[ ]) {
    int ind;
    int i;
    for(i=0; i < s && arr[i] > s; i++);
    if(i == s) return 1;

    int cual = arr[i];
    for(i+= 1; i < s; i++) {
        cual++;
        if(cual == s + 1) cual = 1;
        if(arr[i] <= s && cual != arr[i])
            return 0;
    }
    return 1;
}

int valid(int s, int arr[ ]) {
    if(!es_secuencia(s, arr)) return 0;
    sort(arr, arr+s);
    for(int i = 1; i < s; i++)
        if(arr[i] == arr[i-1])
            return 0;
    return 1;
}

void get_ini(int s, int arr[ ], int * r) {
    int i;
    for(i = 0; arr[i] > s && i < s; i++);
    int cual;
    if(i == s) {
        i = 0;
        cual = 1;
    } else {
        cual = arr[i];
    }
    r[i] = cual;
    for(int j = (i + 1) % s; j != i; j = (j+1)%s) {
        cual++;
        if(cual == s + 1) cual = 1;
        r[j] = cual;
    }
}

int replacement(int s, int arr[ ], int *r) {
    int * inicial;
    inicial = new int[s+2];
    get_ini(s, arr, inicial);
    int t = s + 1;
    priority_queue < pair < int, int > > monti;
    for(int i= 0; i < s; i++) {
        if(inicial[i] != arr[i])
            monti.push(make_pair(-arr[i], inicial[i]));
    }
    int tope = 0;
    while(!monti.empty()) {
        r[tope++] = monti.top().second;
        t++;
        while(t <= -monti.top().first) {
            r[tope++] = t-1;
            t++;
        }
        monti.pop();
    }
    return tope;
}

lld exp_binaria(int x, int exp) {
    if(exp == 0) return 1;
    if(exp == 1) return x;
    lld aux = exp_binaria(x, exp/2);
    aux*=aux;
    aux%= MOD;
    if(exp & 1)
        return (lld) (aux * x) % MOD;
    return aux;
}

int countReplacement(int s, int arr[ ]) {
    if(!valid(s, arr)) return 0;

    int t = s + 1;
    lld resp = 1;
    priority_queue < int > monti;
    for(int i=0; i < s; i++)
        if(arr[i] > s) monti.push(-arr[i]);

    bool todos = monti.size() == s;

    lld aux;
    while(!monti.empty()) {
        aux = -monti.top();
        resp*= exp_binaria(monti.size(), aux - t);
        resp%= MOD;
        t = aux + 1;
        monti.pop();
    }

    if(todos) {
            resp*= s;
            resp%= MOD;
    }

    return resp;
}

int main()
{
    int T;
    cin >> T;
    int n;
    cin >> n;
    int arr[MAXN];
    int * auxiliar;
    auxiliar = new int[MAXN * 4];
    for(int i=0; i < n; i++)
        cin >> arr[i];
    if(T <= 3) {
        cout << valid(n, arr) << " ";
    } else {
        if(T <= 6) {
            int l = replacement(n, arr, auxiliar);
            cout << l;
            for(int i=0; i<l; i++)
                cout << " " << auxiliar[i];
        } else {
            cout << countReplacement(n, arr);
        }
    }
    return 0;
}
