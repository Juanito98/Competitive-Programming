#include <bits/stdc++.h>
#define optimizar ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 100002
#define lld long long int
using namespace std;
int n;

int mapeo[MAXN];

struct pto {
	lld x, y;
};
pto arr[MAXN];
int tope;


lld pCruz(pto A, pto B) {
	return (A.x*B.y) - (A.y*B.x);
}

lld aux;
int derecha(pto i, pto A, pto B) {
	i.x-= B.x;
	i.y-= B.y;
	A.x-= B.x;
	A.y-= B.y;

    aux= pCruz(i, A);

    if(aux == 0)
        return 3;

	if(pCruz(i, A) < 0)
		return -1;
	else
		return 1;
}

bool contenido(int i, int A, int B, int C) {
	int lol= derecha(arr[i], arr[A], arr[B]);
	if( lol == derecha(arr[i], arr[C], arr[A])
	    && lol == derecha(arr[i], arr[B], arr[C]) )
		return true;

	return false;
}

void divide(vector <int> r, vector <int> v,
			 int A, int B, int punta, bool puntaIsR) {

	if(r.size() == 0 || v.size() == 0) {

		for(int i=0; i < r.size(); i++)
			if(puntaIsR)
				cout << mapeo[punta] << " " << mapeo[r[i]] << " r\n";
			else
				cout << mapeo[A] << " " << mapeo[r[i]] << " r\n";

		for(int i=0; i < v.size(); i++)
			if(!puntaIsR)
				cout << mapeo[punta] << " " << mapeo[v[i]] << " v\n";
			else
				cout << mapeo[A] << " " << mapeo[v[i]] << " v\n";

	} else {
		vector <int> izqR;
		vector <int> izqV;
		vector <int> derR;
		vector <int> derV;
		vector <int> downR;
		vector <int> downV;

		int news;

		if(puntaIsR) {
			news= r[rand() % r.size()];
			cout << mapeo[punta] << " " << mapeo[news] << " r\n";
		} else 	{
			news= v[rand() % v.size()];
			cout << mapeo[punta] << " " << mapeo[news] << " v\n";
		}

		for(int i=0; i < r.size(); i++)
			if( contenido(r[i], punta, news, A) )
				izqR.push_back(r[i]);
			else
				if( contenido(r[i], punta, news, B) )
					derR.push_back(r[i]);
				else
					if( contenido(r[i], news, A, B) )
						downR.push_back(r[i]);

		for(int i=0; i < v.size(); i++)
			if( contenido(v[i], punta, news, A) )
				izqV.push_back(v[i]);
			else
				if( contenido(v[i], punta, news, B) )
					derV.push_back(v[i]);
				else
					if( contenido(v[i], news, A, B) )
						downV.push_back(v[i]);

		divide(izqR, izqV, news, punta, A, !puntaIsR);
		divide(derR, derV, news, punta, B, !puntaIsR);
		divide(downR, downV, A, B, news, puntaIsR);

	}
}

int main() {

	optimizar;

	srand(time(NULL));

	cin >> n;

	vector < int > r;
	vector < int > v;

	for(int i=1; i<=n; i++) {
        tope++;
		cin >> arr[tope].x >> arr[tope].y;
		v.push_back(tope);

		mapeo[tope]=i;
	}

	cin >> n;

	for(int i=1; i<=n; i++) {
		tope++;
		cin >> arr[tope].x >> arr[tope].y;
		r.push_back(tope);

		mapeo[tope]=i;
	}

	vector < int > rIzq;
	vector < int > vIzq;
	vector < int > rDer;
	vector < int > vDer;

	for(int i=3; i<=tope; i++) {
		if(i <= tope-n || i > tope-n+2) {
			if( contenido(i, 1, 2, tope-n+2) ) {
				if(i <= tope-n)
					vDer.push_back(i);
				else
					rDer.push_back(i);
			} else {
				if(i <= tope-n)
					vIzq.push_back(i);
				else
					rIzq.push_back(i);
			}
		}
	}

    divide(rDer, vDer, 1, 2, tope-n+2, true);
    divide(rIzq, vIzq, tope-n+1, tope-n+2, 1, false);

    cout << "1 2 r\n";
    cout << "1 2 v\n";

	return 0;
}
