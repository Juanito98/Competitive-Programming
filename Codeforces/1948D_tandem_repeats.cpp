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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    for(cin >> T; T; --T) {
        std::string s;
        cin >> s;
        int largest = 0;
        for (int l = 2; l <= s.size(); l += 2) {
            int i = 0, lmid = l / 2;
            int equal = 0;
            while (equal < l / 2 && i + l <= s.size()) {
                char ci = s[i + equal];
                char cj = s[i + lmid + equal];
                if (ci == cj || ci == '?' || cj == '?') {
                    ++equal;
                } else {
                    ++i;
                    equal = max(0, equal - 1);
                }
            }
            if (equal == l / 2) {
                largest = l;
            }
        }
        cout << largest << endl;
    }

    return 0;
}
