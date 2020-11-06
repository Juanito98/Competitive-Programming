#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
typedef long long int lld;
typedef long double llf;
typedef pair<int, int> pii;

struct ura {
    char v;
    int r, c;
};

vector<ura> arr;

bool isLetter(char c) {
    return 'a' <= c && c <= 'z';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    string s;
    getline(cin, s);
    for (int i = 0; i < n; ++i) {
        getline(cin, s);
        //cout << s << endl;
        int c = 0;
        for (auto car : s) {
            c++;
            if (car == ' ' || car == '\n') continue;
            arr.push_back({car, i+1, c});
        }
    }

    stack<pii> activos[30];
    stack<char> pila;
    for (int i = 0; i < arr.size(); ++i) {
        char v = arr[i].v;
        if (v == '}') {
            while (pila.top() != '{') {
                activos[pila.top()-'a'].pop();
                pila.pop();
            }
            pila.pop();
        } else {
            pila.push(v);
            if (isLetter(v)) {
                if (!activos[v-'a'].empty())
                    printf("%d:%d: warning: shadowed declaration of %c, the shadowed position is %d:%d\n", arr[i].r, arr[i].c, arr[i].v, activos[v - 'a'].top().first, activos[v - 'a'].top().second);
                activos[v-'a'].push({arr[i].r, arr[i].c});
            }
        }
    }

    return 0;
}