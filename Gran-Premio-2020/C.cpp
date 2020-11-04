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

const int MAXN = 100000;

unordered_map<string, int> bucket;
vector<string> arr;

int padre[MAXN];
int tamInd[MAXN];

int root(int nodo) {
    if (padre[nodo] == nodo) return nodo;
    return padre[nodo] = root(padre[nodo]);
}

int maxStrInd(int i, int j) {
    if (arr[i].size() == arr[j].size())
        return arr[i] < arr[j] ? i : j;
    return arr[i].size() < arr[j].size() ? i : j;
}

void join(int i, int j) {
    int ra = root(i), rb = root(j);
    if (ra == rb) return;
    tamInd[ra] = tamInd[rb] = maxStrInd(tamInd[ra], tamInd[rb]);
    padre[rb] = ra;
}

int getId(string& s) {
    if (bucket.count(s) == 0) {
        int id = arr.size();
        bucket[s] = id;
        arr.push_back(s);
        tamInd[id] = id;
        padre[id] = id;
    }
    return bucket[s];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s, t;
        cin >> s >> t;
        join(getId(s), getId(t));
    }

    string s;
    getline(cin, s);
    getline(cin, s);
    stringstream ss(s);

    string st;
    bool space = false;
    while (ss >> st) {
        if (space) cout << " ";
        cout << arr[tamInd[root(getId(st))]];
        space = true;
    }
    cout << "\n";

    return 0;
}