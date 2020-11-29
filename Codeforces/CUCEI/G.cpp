#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <complex>
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

// O(nlogn)
vector<int> suffix_array(string& s) {
    s.push_back('$');
    int N = s.size();
    vector<int> p(N), c(N);
    {  // k = 0
        vector<pair<char, int>> a(N);
        for (int i = 0; i < N; ++i)
            a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < N; ++i)
            p[i] = a[i].second;
        for (int i = 1; i < N; ++i)
            c[p[i]] = a[i].first == a[i - 1].first ? c[p[i - 1]] : c[p[i - 1]] + 1;
    }
    for (int k = 0; (1 << k) < N; ++k) {
        for (int i = 0; i < N; ++i)
            p[i] = (p[i] - (1 << k) + N) % N;
        {  // Counting sort
            vector<int> cnt(N), pos(N), p_new(N);
            for (auto x : c)
                cnt[x]++;
            for (int i = 1; i < N; ++i)
                pos[i] = pos[i - 1] + cnt[i - 1];
            for (auto x : p)
                p_new[pos[c[x]]++] = x;
            p = p_new;
        }
        vector<int> c_new(N);
        for (int i = 1; i < N; ++i) {
            pii prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % N]};
            pii now = {c[p[i]], c[(p[i] + (1 << k)) % N]};
            c_new[p[i]] = now == prev ? c_new[p[i - 1]] : c_new[p[i - 1]] + 1;
        }
        c = c_new;
    }
    s.pop_back();
    return vector<int>(p.begin() + 1, p.end());
}

// lcp[i] = lcp(i, i+1)
// lcp(x, y) = min(lcp[x], lcp[x+1], ... lcp[y-1])
vector<int> lcp_array(string& s, vector<int>& p) {
    int N = s.size();
    vector<int> c(N), lcp(N);
    for (int i = 0; i < N; ++i)
        c[p[i]] = i;
    int k = 0;
    for (int i = 0; i < N; ++i) {
        if (c[i] < N - 1) {
            int j = p[c[i] + 1];
            while (max(i, j) + k < N && s[i + k] == s[j + k])
                k++;
            lcp[c[i]] = k;
            k = max(k - 1, 0);
        }
    }
    return lcp;
}

vector<int> construye(vector<int>& arr) {
    stack<int> p;  // de indices
    // cuanto se extiende a la izquierda
    int n = arr.size();
    vector<int> L(n);
    for (int i = 0; i < n; ++i) {
        while (!p.empty() && arr[p.top()] >= arr[i])
            p.pop();
        if (p.empty())
            L[i] = i;
        else
            L[i] = i - p.top() - 1;
        p.push(i);
    }
    return L;
}

const int LOG_N = 30;
const int MAX = 1000002;
const lld M = 1e9 + 7;

int n, k;
int arr[MAX];
int sparse[LOG_N][MAX];

int minIndex(int i, int j) {
    return arr[i] < arr[j] ? i : j;
}

void do_sparse() {
    for (int i = 0; i < n; ++i) {
        sparse[0][i] = i;
    }
    for (int l = 1; l < LOG_N; ++l) {
        for (int i = 0; i < n; ++i) {
            if (i + (1 << (l - 1)) >= n) {
                sparse[l][i] = -1;
                continue;
            }
            sparse[l][i] = minIndex(sparse[l - 1][i], sparse[l - 1][i + (1 << (l - 1))]);
        }
    }
}

int query(int i, int j) {
    if (i > j) return -1;  // Imposible
    int ans = minIndex(sparse[0][i], sparse[0][j]);
    for (int l = LOG_N - 1; l >= 0; --l) {
        if (i + (1 << l) <= j) {
            ans = minIndex(ans, sparse[l][i]);
            i += (1 << l);
        }
    }
    return ans;
}

lld sol(int i, int j, int inundado) {
    //cout << i << " " << j << " " << inundado << endl;
    if (i > j) return 0;
    int idx = query(i, j);
    if (arr[idx] <= inundado) {
        return (sol(i, idx-1, inundado) + sol(idx+1, j, inundado)) % M;
    }
    // inundo desde [inundado+1 hasta arr[idx]]    
    lld ans = 1;
    for (int l = 0; l < k; ++l) {
        ans *= (lld) (j-i + 2); // freq
        ans %= M;
    }
    ans *= (arr[idx] - inundado);
    ans %= M;

    ans += (sol(i, idx - 1, arr[idx]) + sol(idx + 1, j, arr[idx])) % M;

    return ans % M;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    string s;
    cin >> s;

    vector<int> p = suffix_array(s);
    vector<int> lcp = lcp_array(s, p);

    lld ans = 0;
    int coincido_atras = 0, freq = 0;
    for (int i = 0; i < n; ++i) {
        int coincido_sig = lcp[i];
        int len = n - p[i];
        ans += len - max(coincido_atras, coincido_sig);
        ans %= M;
        coincido_atras = coincido_sig;
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = lcp[i];
        //cout << lcp[i] << " ";
    }
    //cout << endl;

    do_sparse();

    ans += sol(0, n-1, 0);

    cout << ans%M << "\n";

    return 0;
}