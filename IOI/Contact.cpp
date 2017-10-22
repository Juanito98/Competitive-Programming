#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;

int a, b;
int n;
string num;
int cubeta[(1 << 15)];
priority_queue < pair < int, int > > monti;

void print(int x) {
    if(x == 1) { cout << " "; return; }
    print(x >> 1);
    cout << (x & 1);
}

int main()
{
    optimizar;
    cin >> a >> b;
    cin >> n;
    cin >> num;
    int c = 0;
    for(int i = 0; i < num.size() - 1; i++) {
        c = 1;
        for(int j = i; j < num.size() - 1 && j - i + 1 <= b; j++) {
            c <<= 1;
            c += num[j] - '0';
            if(j - i + 1 >= a) cubeta[c]++;
        }
    }
    for(int i = 0; i < (1 << 15); i++)
        if(cubeta[i]) monti.push(make_pair(cubeta[i], i));

    int ant = -1;
    for(int i = 0; i < n && !monti.empty(); i++) {
        ant = monti.top().first;
        cout << monti.top().first;
        while(!monti.empty() && monti.top().first == ant) {
            print(monti.top().second);
            monti.pop();
        }
        cout << "\n";
    }
    return 0;
}
