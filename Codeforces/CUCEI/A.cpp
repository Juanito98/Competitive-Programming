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
 
const int MAX = 100002;
 
int n, m, x;
 
struct segment_tree {
   #define DER (nodo*2 + 1)
   #define IZQ (nodo*2)
   lld arr[MAX];
   lld lazy[MAX*5];
   bool lazy_clear[MAX*5];
 
   void propagate(int nodo, int ini, int fin) {
       if (lazy_clear[nodo]) {
           if (ini != fin) {
               lazy_clear[DER] = lazy_clear[IZQ] = true;
               lazy[DER] = 0;
               lazy[IZQ] = 0;
           } else {
               arr[ini] = 0;
           }
       }
       lazy_clear[nodo] = false;
 
       if (ini != fin) {
           lazy[DER] += lazy[nodo];
           lazy[IZQ] += lazy[nodo];
       } else {
           arr[ini] += lazy[nodo];
       }
       lazy[nodo] = 0;
   }
 
   void clear(int nodo, int ini, int fin, int i, int j) {
       propagate(nodo, ini, fin);
       if (ini > j || fin < i) return;
       if (ini >= i && fin <= j) {
           lazy_clear[nodo] = true;
           propagate(nodo, ini, fin);
       } else {
           int med = (ini + fin) / 2;
           clear(IZQ, ini, med, i, j);
           clear(DER, med+1, fin, i, j);
       }
   }
   void clear(int i, int j) {
       if (i > j) return;
       clear(1, 1, n, i, j);
   }
 
   void add(int nodo, int ini, int fin, int i, int j, lld v) {
       propagate(nodo, ini, fin);
       if (ini > j || fin < i) return;
       if (ini >= i && fin <= j) {
           lazy[nodo] += v;
           propagate(nodo, ini, fin);
       } else {
           int med = (ini + fin) / 2;
           add(IZQ, ini, med, i, j, v);
           add(DER, med + 1, fin, i, j, v);
       }
   }
   void add(int i, int j, int v) {
       if (i > j) return;
       add(1, 1, n, i, j, v);
   }
 
   lld query(int nodo, int ini, int fin, int pos) {
       propagate(nodo, ini, fin);
       if (ini == fin) {
           return arr[ini];
       } else {
           int med = (ini + fin) / 2;
           if (pos <= med) return query(IZQ, ini, med, pos);
           return query(DER, med+1, fin, pos);
       }
   }
   lld query(int pos) {
       return query(1, 1, n, pos);
   }
};
segment_tree A, Aindex;
 
void addDec(int i, int j) {
   //if << "Add dec " << i << " " << j << endl;
   if (i > j) return;
   Aindex.add(i, j, -1);
   A.add(i, j, j+1);
}
 
void addInc(int i, int j) {
   //if << "Add inc " << i << " " << j << endl;
   if (i > j) return;
   Aindex.add(i, j, 1);
   A.add(i, j, 1-i);
}
 
lld query(lld pos) {
   if (pos <= 0 || pos > n) return -1;
   return A.query(pos) + pos * Aindex.query(pos);
}
 
int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0);
 
   cin >> n >> m >> x;
 
   addInc(x + 1, n);
   addDec(1, x - 1);
 
   bool posible = true;
   for (int i = 0; i < m; ++i) {
       int tipo, a, b;
       cin >> tipo >> a >> b;
       if (tipo == 1) {
           if (a == 1 && b == n) {
               posible = false;
           }
           A.clear(a, b);
           Aindex.clear(a, b);
 
           lld qa = query(a-1);
           lld qb = query(b+1);
 
           if (qa == -1) {
               A.add(a, b, qb);
               addDec(a, b);
           } else if (qb == -1) {
               A.add(a, b, qa);
               addInc(a, b);
           } else {
               int med = (a+b+qb-qa)/2 -1;
               med = min(med, b);
               med = max(med, a-1);
               A.add(a, med, qa);
               addInc(a, med);
               A.add(med+1, b, qb);
               addDec(med+1, b);
           }
       } else {
           A.clear(1, a-1);
           A.clear(b+1, n);
           Aindex.clear(1, a - 1);
           Aindex.clear(b + 1, n);
 
           lld qa = query(a);
           lld qb = query(b);
 
           A.add(1, a-1, qa);
           A.add(b+1, n, qb);
           addDec(1, a-1);
           addInc(b+1, n);
       }
   }
 
   lld ans = LONG_MAX;
   for (int i = 1; i <= n; ++i) {
       ans = min(ans, query(i));
       //cout << query(i) << " ";
   }
   //cout << endl;
 
   if (!posible) ans = -1;
 
   cout << ans << "\n";
 
   return 0;
}