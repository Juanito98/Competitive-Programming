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

const int MAXN = 100002;

struct bit {
    int tree[MAXN];

    void update(int pos, int v) {
        for (; pos < MAXN; pos += pos&(-pos))
            tree[pos] += v;
    }

    int query(int pos) {
        int v = 0;
        for (; pos; pos -= pos&(-pos))
            v += tree[pos];
        return v;
    }
};

bit BIT, BIT_R;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    vector<int> L(n), R(n);
    lld f1 = 0, f2 = 0;

    for (int i = 0; i < n; ++i) {
        L[i] = i - BIT.query(arr[i]);
        BIT.update(arr[i], 1);
    }

    for (int i = n - 1; i >= 0; --i) {
        R[i] = n - i - 1 - BIT_R.query(arr[i]);
        BIT_R.update(arr[i], 1);
    }

    for (int i = 0; i < n; ++i) {
        f1 += L[i];
        f2 += min(L[i], R[i]);
        //cout << L[i] << " " << R[i] << endl; 
    }

    cout << f1 << " " << f2 << "\n";

    return 0;
}