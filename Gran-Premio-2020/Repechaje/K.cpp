#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> an, am;
    an.resize(n+2);
    am.resize(m+2);
    for(int i = 0; i < n; i++){
        cin >> an[i];
    }
    for(int i = 0; i < m; i++){
        cin >> am[i];
    }
    int ans = 0;
    for(int i = 0; i < m; i++){
        if(i < n){
            ans+= (am[i]-an[i]);
        }else{
            ans+=am[i];
        }
    }
    cout<< ans << '\n';
    return 0;
}
