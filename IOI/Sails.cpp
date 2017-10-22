#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define MAXN 100002
#define izq (nodo * 2)
#define der (nodo * 2) + 1
using namespace std;

struct BIT {
    lld bit[MAXN*4];

    int _size;

    void init(int s) {
        _size = s;
    }

    void update(int p, int v) {
        for(; p <= _size; p += p&(-p))
            bit[p] += v;
    }

    void update(int a, int b, int v) {
        update(a, v);
        update(b + 1, -v);
    }

    lld query(int b) {
        lld sum = 0;
        for(; b > 0; b -= b&(-b))
            sum += bit[b];
        return sum;
    }


    void aumenta(int ini, int fin) {
        update(ini, fin, 1);
    }

    lld num(int pos) {
        return query(pos);
    }

};

int n;

BIT arr;

struct ura {
    int h, cuantas;
};


bool funcion(ura a, ura b) {
    return a.h < b.h;
}

ura sails[MAXN];

lld suma;

int ultimo(lld v, int ini, int fin) {
    int med;
    while(ini < fin) {
        med = (ini + fin + 1) / 2;
        if(arr.num(med) < v) {
            fin = med - 1;
        } else {
            ini = med;
        }
    }
    return ini;
}

int primero(lld v, int ini, int fin) {
    int med;
    while(ini < fin) {
        med = (ini + fin) / 2;
        if(arr.num(med) > v) {
            ini = med + 1;
        } else {
            fin = med;
        }
    }
    return ini;
}

void actualiza(int ini, int fin, int cuantos) {
    lld cai_en = arr.num(ini);
    int _ultimo = ultimo(cai_en, ini, fin) + 1;
    int _primero = primero(cai_en, 1, ini);
    if(_ultimo <= fin) {
        cuantos-= fin - _ultimo + 1;
        arr.aumenta(_ultimo, fin);
    }
    arr.aumenta(_primero, _primero+cuantos-1);
}

void procesa() {
    int h, cuantos;
    int ini;

    for(int i=1; i<=n; i++) {
        h = sails[i].h;
        cuantos = sails[i].cuantas;
        ini = h - cuantos + 1;
        if(h > cuantos) {
            actualiza(ini, h, cuantos);
        } else {
            arr.aumenta(1, cuantos);
        }
    }

    lld aux;

    for(int i=1; i<=arr._size; i++) {
        aux = arr.num(i) - 1;
        suma+= (aux * (aux+1));
    }
    suma/=2;
}

int main()
{
    optimizar;

    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> sails[i].h >> sails[i].cuantas;

    sort(sails+1, sails+n+1, funcion);
    arr.init(sails[n].h);
    procesa();

    cout << suma << "\n";

    return 0;
}
