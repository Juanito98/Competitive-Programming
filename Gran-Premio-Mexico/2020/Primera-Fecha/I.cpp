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
const int MAXN = 100000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    string cur;
    set<char> s;
    s.insert('.');
    s.insert('#');
    s.insert('$');
    s.insert('%');
    s.insert('/');
    s.insert('(');
    s.insert('&');
    s.insert(')');
    for (int i = 0; i < n; i++) {
        int low = 0, up = 0, nums = 0, car = 0;
        int tam;
        int tot = 0;
        bool flag = true;
        cin >> cur;
        tam = cur.size();
        if (tam >= 10)
            tot++;
        int j = 0;
        while (j < tam && (up == 0 || low == 0 || car == 0 || nums == 0)) {
            if (low < 1 && cur[j] >= 'a' && cur[j] <= 'z')
                low++;
            if (up < 1 && cur[j] >= 'A' && cur[j] <= 'Z')
                up++;
            if (nums < 1 && cur[j] >= '0' && cur[j] <= '9')
                nums++;
            if (car < 1 && s.find(cur[j]) != s.end())
                car++;
            j++;
        }
        for (j = 0; j < tam - 1 && flag; j++) {
            if (cur[j] >= '0' && cur[j] <= '9') {
                if (cur[j + 1] >= '0' && cur[j + 1] <= '9') {
                    int n1 = cur[j] - '0';
                    int n2 = cur[j + 1] - '0';
                    if (n1 + 1 == n2 || n2 + 1 == n1)
                        flag = false;
                }
            }
        }
        int sum = flag && nums > 0 ? 1 : 0;
        sum += (low + up + car + tot);
        string ans;
        if (sum <= 2)
            ans = "Rejected";
        else if (sum <= 3)
            ans = "Weak";
        else if (sum <= 4)
            ans = "Good";
        else
            ans = "Strong";
        cout << "Assertion number #" << i + 1 << ": " << ans << '\n';
    }
    return 0;
}