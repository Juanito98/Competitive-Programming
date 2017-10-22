#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define lld long long int
#define INF (1 << 30)
#define h first
#define t second
using namespace std;

map < lld, lld > resp;
priority_queue < pair < lld, lld > > monti;
lld ant; // ultimo impreso

void saca(lld x) {
    lld t = 0;
    while(!monti.empty() && monti.top().t < x) {
        t = monti.top().t;
        while(!monti.empty() && monti.top().t <= t)
            monti.pop();
        if(!monti.empty()) {
            if(ant != monti.top().h) {
                resp[t]= max(resp[t], monti.top().h);
                ant = resp[t];
            }
        } else {
            resp[t] = max(resp[t], 0ll);
            ant = 0;
        }
    }
}

int main()
{
    optimizar;
    lld izq, h, der;
    while(cin >> izq) {
        cin >> h >> der;
        saca(izq);
        monti.push(make_pair(h, der));
        if(monti.top().h != ant) {
            resp[izq] = max(resp[izq], h);
            ant = h;
        }
    }

    saca(INF);

    map < lld , lld > :: iterator it;
    bool impreso = false;
    for(it = resp.begin(); it != resp.end(); it++) {
        if(impreso) cout << " ";
        cout << it -> first << " " << it -> second;
        impreso = true;
    }

    cout << "\n";

    return 0;
}
