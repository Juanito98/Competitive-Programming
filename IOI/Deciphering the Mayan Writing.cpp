#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define INF (1 << 30)
#define LETTERS 500
#define MAXN 3000002
using namespace std;
int n, m;

string p;

int cubeta[LETTERS];
int laPro[LETTERS];
int dif;

void procesa(string a){
    for(int i=0; i < a.size(); i++)
        cubeta[a[i]]++;
}

int resp;
void recorre() {
    dif= m;

    int ini=0;
    int fin= -1;

    while(fin < (m-1)) {
        fin++;
        laPro[p[fin]]++;
        if(laPro[p[fin]] <= cubeta[p[fin]])
            dif--;
    }

    if(!dif)
        resp++;

    while(fin < n) {
        if(laPro[p[ini]] <= cubeta[p[ini]])
            dif++;
        laPro[p[ini]]--;
        ini++;

        fin++;
        laPro[p[fin]]++;
        if(laPro[p[fin]] <= cubeta[p[fin]])
            dif--;

        if(!dif)
            resp++;
    }
}

int main() {
	optimizar;

	cin >> m >> n;
	string a;
	cin >> a >> p;

    procesa(a);

    recorre();

    cout << resp << "\n";

	return 0;
}
