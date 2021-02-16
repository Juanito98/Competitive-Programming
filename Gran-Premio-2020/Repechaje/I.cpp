#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <stack>
#include <utility>
#include <queue>
#include <set>
#include <iomanip>
#include <sstream>


using namespace std;
const int MAX = 1E7+5;
vector<int> prime;
bool isPrime[MAX];
//int phi[MAX]; // Uncomment to get Euler's phi
int cant[MAX];
void sieve() {
    fill(isPrime, isPrime + MAX, true);
    isPrime[0] = isPrime[1] = false;
    //phi[0] = phi[1] = 0;
    for (int i = 2; i < MAX; ++i) {
        if (isPrime[i]) {
            prime.push_back(i);
            cant[i] = 1;
        }
        for (int j = 0; j < prime.size() && i * prime[j] < MAX; ++j) {
            isPrime[i * prime[j]] = false;
            cant[i * prime[j]] = cant[i] + 1; 
            if (i % prime[j] == 0) {
                 cant[i * prime[j]] = cant[i] ;
                break;
            }
        }
    }
}

int gcd(int a, int b){
    if(a == 0)
        return b;
    else
        return gcd(b%a, a);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int a, b;
    int g;
    sieve();
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        g = gcd(a,  b);
        //cout<<a/g<<" "<<b/g<<" "<<g<<endl;
        //cout<<cant[a/g]<<" "<<cant[b/g]<<" "<<cant[g]<<endl;
        cout << (cant[a] + cant[b] - cant[g]) << '\n';
    }
}