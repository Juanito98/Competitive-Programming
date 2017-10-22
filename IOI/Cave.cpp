#include <bits/stdc++.h>
#include "cave.h"
using namespace std;
int *msc;
bool visitado[5002];
int n;
int aux;

int binSearch(int i) {
	int ini = 0;
	int fin = n - 1;
	int med;

	aux = tryCombination(msc);
	int estorba = 0;
	if(aux == i) estorba = 1;

	while(ini < fin) {
		estorba^=1;
		med = (ini + fin) / 2;
		for(aux = ini; aux <= med; aux++)
			if(!visitado[aux]) 
				msc[aux]^=1;

		aux = tryCombination(msc);
		if(estorba) {
			if(aux == i)
				fin = med;
			else
				ini = med + 1;
		} else {
			if(aux != i)
				fin = med;
			else
				ini = med + 1;
		}


		if(aux == i)
            		estorba = 1;
        	else
        	    estorba = 0;
	}

	if(aux == i) 
		msc[ini]^=1;

	return ini;

}

void exploreCave(int N) {
	n= N;
	msc = new int[N];
	fill(msc, msc+n, 0);
	int fin[n];

	int x;
	for(int i=0; i < n; i++) {
		x = binSearch(i);    // binSearch regresa el boton de la puerta i.
		visitado[x] = true;  // si el boton debe estar prendido regresa el numero negativo
        	fin[x] = i;
	}

	answer(msc, fin);
}