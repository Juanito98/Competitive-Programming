#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
#define lld long long int
#define LIMIT 1000000000
using namespace std;

int n, m, k;
vector < pair < int, lld > > lista[MAXN];

bool procese[MAXN];
bool pase[MAXN];
priority_queue < pair < lld, int > > monti;

void genera(int nodo, lld c) {
    for(int i=0; i < lista[nodo].size(); i++) {
        if(!procese[lista[nodo][i].first]) {
            monti.push(make_pair(-(c + lista[nodo][i].second), lista[nodo][i].first));
        }
    }
}

int expande() {
    int nodo;
    lld c;
    while(!monti.empty()) {
        nodo = monti.top().second;
        c = -monti.top().first;
        monti.pop();
        if(!pase[nodo]) {
            pase[nodo] = true;
        } else {
            if(!procese[nodo] && c <= LIMIT) {
                if(nodo == 0) return c;
                procese[nodo] = true;
                genera(nodo, c);
            }
        }
    }
    return LIMIT;
}

int main()
{
    optimizar;
    cin >> n >> m >> k;
    int a, b, c;
    for(int i=1; i<=m; i++) {
        cin >> a >> b >> c;
        lista[a].push_back(make_pair(b, c));
        lista[b].push_back(make_pair(a, c));
    }
    for(int i=1; i<=k; i++) {
        cin >> a;
        pase[a] = true;
        monti.push(make_pair(0, a));
    }
    cout << expande() << "\n";
    return 0;
}
