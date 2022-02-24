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

const lld M = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int caso = 1; caso <= T; ++caso) {
        cout << "Case #" << caso << ": ";
        int n;
        string s;
        cin >> n >> s;
        lld prefSum = 0, suffSum = 0, ans = 0;
        lld lenA = 0;
        int posUlt = -1;
        int posPrimer = -1;
        char ultCar, primerCar;
        int totalSwitches = 0;

        for (int i = 0; i < s.size(); ++i) {
            //cout << i << " " << " " << posPrimer << " " << posUlt << endl;

            lld newPrefSum = prefSum, newSuffSum = suffSum, newAns = ans;
            if (s[i] == '.') {
                if (posPrimer != -1) {
                    // Actualizo ans
                    newAns += ans;
                    newAns %= M;
                    // ambos pos son distintos de -1
                    // Combino cada prefijo con cada sufijo
                    newAns += (lenA * ((suffSum + prefSum) % M)) % M;
                    newAns %= M;
                    if (ultCar != primerCar) {
                        newAns += (posUlt * ((lenA - posPrimer + M + 1) % M)) % M;
                        newAns %= M;
                    }

                    // Actualizo suff sum
                    newSuffSum += suffSum;
                    newSuffSum %= M;
                    newSuffSum += (totalSwitches * lenA) % M;
                    newSuffSum %= M;
                    if (ultCar != primerCar) {
                        newSuffSum += (lenA - posPrimer + M + 1) % M;
                        newSuffSum %= M;
                    }

                    // Actualizo preff sum
                    newPrefSum += prefSum;
                    newPrefSum %= M;
                    newPrefSum += (totalSwitches * lenA) % M;
                    newPrefSum %= M;
                    if (ultCar != primerCar) {
                        newPrefSum += posUlt;
                        newPrefSum %= M;
                    }

                    // Actualizo context swithces
                    totalSwitches *= 2;
                    totalSwitches %= M;
                    if (ultCar != primerCar) {
                        totalSwitches += 1;
                        totalSwitches %= M;
                    }

                    // Actualizo posUlt
                    posUlt += lenA;
                    posUlt %= M;
                }
                // Actualizo lenA
                lenA *= 2;
                lenA %= M;
            } else {
                
                if (posPrimer != -1) {
                    // Actualizo ans
                    newAns += prefSum;
                    newAns %= M;
                    if (s[i] != 'F' && ultCar != s[i]) {
                        newAns += posUlt;
                        newAns %= M;
                    }

                    // Actualizo sum pref
                    if (s[i] != 'F' && ultCar != s[i]) {
                        newPrefSum += posUlt;
                        newPrefSum %= M;
                    }

                    // Actualizo totalSwitches
                    if (s[i] != 'F' && ultCar != s[i]) {
                        totalSwitches ++;
                        totalSwitches %= M;
                    }

                    // Actualizo sum suff
                    newSuffSum += totalSwitches;
                    newSuffSum %= M;
                }

                if (s[i] != 'F') {
                    // Actualizo primer caracter
                    if (posPrimer == -1) {
                        posPrimer = (lenA + 1) % M;
                        primerCar = s[i];
                    }
                    // Actualizo ultimo caracter
                    posUlt = (lenA + 1) % M;
                    ultCar = s[i];
                }

                lenA++;
                lenA %= M;
            }

            ans = newAns;
            prefSum = newPrefSum;
            suffSum = newSuffSum;

            //cout << lenA << " " << ans << " " << prefSum << " " << suffSum << endl;
            //cout <<  posPrimer << " " << posUlt << " " << totalSwitches << " " << endl;
        }

        cout << ans << "\n";
    }

    return 0;
}