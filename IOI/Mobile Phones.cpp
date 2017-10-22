#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define MAXN 1030
using namespace std;

int n;
int bit[MAXN][MAXN];

void update(int x, int y, int v) {
    int j = y;
    while(x <= n) {
        j = y;
        while(j <= n) {
            bit[x][j]+= v;
            j+= j&(-j);
        }
        x+= x&(-x);
    }
}

lld query(int x, int y) {
    int j;
    lld sum = 0;
    while(x) {
        j = y;
        while(j) {
            sum+= bit[x][j];
            j-= j&(-j);
        }
        x-=x&(-x);
    }
    return sum;
}

lld suma(int x1, int x2, int y1, int y2) {
    return query(x2, y2) + query(x1-1, y1-1)
            - query(x1-1, y2) - query(x2, y1-1);
}

int main()
{
    optimizar;

    int ins = 0;
    int x1, x2, y1, y2;
    int a;
    for(cin >> ins; ins != 3; cin >> ins) {
        if(ins == 0)
            cin >> n;

        if(ins == 1) {
            cin >> x1 >> y1 >> a;
            x1++, y1++;
            update(x1, y1, a);
        }

        if(ins == 2) {
            cin >> x1 >> y1 >> x2 >> y2;
            x1++, x2++, y1++, y2++;
            cout << suma(x1, x2, y1, y2) << "\n";
        }
    }
    return 0;
}
