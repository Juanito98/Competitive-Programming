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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    vector<int> ord = arr;
    sort(ord.begin(), ord.end());

    int j = 0;
    int mover = 0;
    for (int i = 0; i < n && j < n; ++i) {
        while (j < n && ord[i] != arr[j]) {
            //cout << i << " " << j << endl;
            mover++;
            j++;
        }
        if (ord[i] == arr[j])
            j++;
    }
    
    cout << mover << "\n";

    return 0;
}