/*
    Linear sieve
    https://codeforces.com/contest/546/problem/D
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

const int MAX = 5000002;

vector<int> prime;
bool isPrime[MAX];
int E[MAX];
lld sum[MAX];

void sieve() {
    fill(isPrime, isPrime + MAX, true);
    isPrime[0] = isPrime[1] = false;
    E[0] = E[1] = 0;
    for (int i = 2; i < MAX; ++i) {
        if (isPrime[i]) {
            prime.push_back(i);
            E[i] = 1;
        }
        for (int j = 0; j < prime.size() && i * prime[j] < MAX; ++j) {
            isPrime[i * prime[j]] = false;
            E[i * prime[j]] = E[i] + 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    sieve();
    for (int i = 1; i < MAX; ++i) 
        sum[i] = sum[i-1] + (lld)(E[i]);

    int T;
    for (cin >> T; T; --T) {
        int a, b;
        cin >> a >> b;
        cout << sum[a] - sum[b] << "\n";
    }
    return 0;
}