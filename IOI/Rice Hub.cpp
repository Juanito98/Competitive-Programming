#include <stdio.h>
#include <algorithm>
#define MAXN 100002
#define lld long long int
using namespace std;
lld n;
lld b;
lld sums[MAXN];
lld resp;

lld max(lld a, lld b) {
    return a < b ? b : a;
}

lld suma(lld ini, lld fin) {
    return (sums[fin]-sums[ini-1]);
}

void barrido() {
    lld ini=1;
    lld fin=1;
    lld costo=0;
    lld med;
    while(fin<=n) {
        med=(ini+fin+2)/2;
        costo=suma(med,fin);
        med=(ini+fin-1)/2;
        costo-=suma(ini,med);
        if(costo<=b) {
            fin++;
            resp=max(resp,fin-ini);
        } else {
            ini++;
        }
    }
}

int main()
{
    scanf("%lld", &n);
    scanf("%lld", &b);
    scanf("%lld", &b);
    for(lld i=1; i<=n; i++)
        scanf("%lld", &sums[i]);
    sort(sums+1,sums+n+1);
    for(lld i=1; i<=n; i++)
        sums[i]+=sums[i-1];
    barrido();
    printf("%lld\n", resp);
    return 0;
}
