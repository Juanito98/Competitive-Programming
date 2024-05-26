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
const int MAX = 1E6+5;
vector<int> prime;
bool isPrime[MAX];
//int phi[MAX]; // Uncomment to get Euler's phi
int minP[MAX];
void sieve() {
    fill(isPrime, isPrime + MAX, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAX; ++i) {
        if (isPrime[i]) {
            prime.push_back(i);
            minP[i] = i;
        }
        for (int j = 0; j < prime.size() && i * prime[j] < MAX; ++j) {
            isPrime[i * prime[j]] = false;
            minP[i * prime[j]] = min(minP[i], prime[j]); 
            if (i % prime[j] == 0) {
                 minP[i * prime[j]] = min(minP[i], prime[j]) ;
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
    int k, p, s;
    sieve();
    vector<int> resp;
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        k+=2;
        resp.clear();
        while(k > 1){
            p = minP[k];
            if(p > 2) resp.push_back(p);
            while(k%p == 0) k/=p;
        }
        s = resp.size();
        if(s>0){
            cout<<resp[0];
            for(int i = 1; i < s;++i)
                cout<<" "<<resp[i];
            cout<<"\n";
        }else{cout<<"-1\n";}

        
    }
}