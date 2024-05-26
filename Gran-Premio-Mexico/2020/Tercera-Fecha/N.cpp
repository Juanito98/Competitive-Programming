/*
    Bin search + DP
*/
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

const int MAXN = 102;

int D, B, n;
int arr[MAXN];

lld minBudget(int d) {
    /*
        DP(n, p) minimo budget tal que estan a distancia a lo mas de d
    */
   vector<lld>* dp_ant = new vector<lld>(D + 2);
   vector<lld>* dp_act = new vector<lld>(D + 2);

   // Fijamos el primer satelite que este en la pos 0
    fill (dp_act -> begin(), dp_act -> end(), INT_MAX);
    (*dp_act)[0] = 0;

    // Ponemos el ultimo en la posicion D
    arr[n] = D;

    for (int i = 0; i <= n; ++i) {
        swap(dp_ant, dp_act);
        deque<int> q; // Pila para guardar el menor entre [pi-d, pi]
        for (int pi = 0; pi <= D; ++pi) {
            // Sacamos los oxidados
            while (!q.empty() && pi - q.front() > d) 
                q.pop_front();
            // Metemos a la pila dp (i-1, pi)
            while (!q.empty() && (*dp_ant)[q.back()] >= (*dp_ant)[pi])
                q.pop_back();
            q.push_back(pi);

            (*dp_act)[pi] = (*dp_ant)[q.front()] + abs(arr[i] - pi);
        }
        //for (int pi = 0; pi <= D; ++pi)
        //    cout << (*dp_act)[pi] << " ";
        //cout << endl;
    }

    return (*dp_act)[D];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> D >> B >> n;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    sort(arr, arr + n);

    // Bin search
    int l = 1, r = D;
    while (l < r) {
        int m = (l + r) / 2;
        //cout << m << ": " << endl;
        if (minBudget(m) <= B)
            r = m;
        else 
            l = m + 1;
    }

    cout << l << "\n";

    return 0;
}