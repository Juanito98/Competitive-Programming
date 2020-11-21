/*
    Regional Latinoamerica 2019
    Geometria
    https://www.urionlinejudge.com.br/judge/es/problems/view/3015
*/
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

pii operator-(pii a, pii b) { return {a.first - b.first, a.second - b.second}; }

bool isLeq(pii a, pii b) {
    return a.first * b.second <= b.first * a.second;
}

// m <= tant <= M 
// pairs represented by c/d

bool check_ineq(int a, int b, bool cosNeg, pii& m, pii& M) {
    pii v = {-b, a};
    if (a < 0) v = {b, -a};
    if (cosNeg) {
        // forma a tant <= -b
        if (a == 0) return 0 <= -b;
        if (a > 0) { // tan <= v
            if (isLeq(v, M)) M = v;
        } else { // tan >= v
            if (isLeq(m, v)) m = v;
        }
    } else {
        // forma a tant >= -b
        if (a == 0) return 0 >= -b;
        if (a > 0) {  // tan >= v
            if (isLeq(m, v)) m = v;
        } else {  // tan <= v
            if (isLeq(v, M)) M = v;
        }
    }
    return isLeq(m, M);
}

// Check if there is t such that ai sent + bi cost >= 0
bool check_satisf(vector<pii>& ineq) {
    int n = ineq.size();
    for (int c = 0; c < 2; ++c) {
        // Check for cos cases
        pii m = {-1, 0}, M = {1, 0};
        bool ans = true, cosEZ = true;
        for (int i = 0; i < n; ++i) {
            int a, b;
            tie(a, b) = ineq[i];
            if (!check_ineq(a, b, c, m, M)) 
                ans = false;
            // Checar cost = 0
            // a sent >= 0
            if (c == 0 && a < 0) // sen = 1
                cosEZ = false;
            if (c == 1 && a > 0) // sen = -1
                cosEZ = false;
        }
        if (ans || cosEZ)
            return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<int, pii>> arr(n);
    vector<pii> ineq;
    for (int i = 0; i < n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        arr[i] = {c, {x, y}};
        for (int j = 0; j < i; ++j) {
            if (arr[i].first > arr[j].first)
                ineq.push_back(arr[i].second - arr[j].second);
            if (arr[i].first < arr[j].first)
                ineq.push_back(arr[j].second - arr[i].second);
        }
    }

    bool ans = check_satisf(ineq);

    cout << (ans ? "Y" : "N") << "\n";

    return 0;
}