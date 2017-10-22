#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define MAXN (1 << 18)
using namespace std;

lld changes[12];

void init() {
    changes[1] = 110110000;
    changes[2] = 111000000;
    changes[3] = 11011000;
    changes[4] = 100100100;
    changes[5] = 10111010;
    changes[6] = 1001001;
    changes[7] = 110110;
    changes[8] = 111;
    changes[9] = 11011;
}

struct ura {
    lld num;
    int p;
    int mov;
};

bool vis[MAXN + 10];
ura cola[MAXN + 10];
int ini, fin;

void mete(ura a) {
    cola[++fin] = a;
}

ura saca() {
    return cola[++ini];
}

void imprime(int nodo) {
    if(cola[nodo].p != -1) {
        imprime(cola[nodo].p);
        cout << cola[nodo].mov << " ";
    }
}

lld convierte(lld a) {
    lld diez = 1;
    lld halp = a;
    while(diez <= a) {
        if(halp % (diez * 10) == (4 * diez))
            a-= (4 * diez);

        halp-= halp % (diez * 10);

        diez*= 10;
    }
    return a;
}

int base_4(lld a) {
    int num = 0;
    int base = 1;
    while(a) {
        num += base * (a % 10);
        base*=4;
        a /= 10;
    }
    return num;
}

void genera(ura a) {
    ura b;
    for(int i=1; i<=9; i++) {
        b.num = convierte(a.num + changes[i]);
        if(!vis[base_4(b.num)]) {
            vis[base_4(b.num)] = true;
            b.mov = i;
            b.p = ini;
            mete(b);
        }
    }
}

void busca() {
    ura edo;
    edo = saca();
    while(edo.num) {
        genera(edo);
        edo = saca();
    }
    imprime(ini);
    cout << "\n";
}

int main()
{
    optimizar;

    init();

    ura inis;
    inis.p = -1;
    inis.mov = -1;
    inis.num = 0;

    int aux;
    for(int i=1; i <= 9; i++)  {
        cin >> aux;
        aux/=3;
        aux%=4;
        inis.num*= 10;
        inis.num+= aux;
    }
    init();
    mete(inis);
    busca();

    return 0;
}