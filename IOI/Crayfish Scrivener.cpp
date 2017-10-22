#include <stdio.h>
#define MAXN 1000002
#define LOG_MAXN 22
using namespace std;
struct ura {
    char letra;
    int tam;
    int saltos[LOG_MAXN];
};
ura tiempo[MAXN];
int n;
int tope;
 
void imprime(int i, int val) {
    if(tiempo[i].tam==val) {
        printf("%c\n", tiempo[i].letra);
    } else {
        int sal=0;
        for(int j=1; tiempo[i].tam-j>=val; j*=2)
            sal++;
        imprime(tiempo[i].saltos[sal-1],val);
    }
}
 
void undo(int val) {
    tope++;
    tiempo[tope]=tiempo[tope-val];
}
 
void inserta(char val) {
    tiempo[++tope].letra=val;
    tiempo[tope].tam=tiempo[tope-1].tam+1;
    tiempo[tope].saltos[0]=tope-1;
    int apunt=1;
    int j=tiempo[tope].saltos[0];
    while(tiempo[tope].saltos[apunt-1]) {
        tiempo[tope].saltos[apunt]=tiempo[j].saltos[apunt-1];
        apunt++;
        j=tiempo[tope].saltos[apunt-1];
    }
}
 
int main()
{
    scanf("%d", &n);
    char aux;
    char letra;
    int val;
    for(int i=1; i<=n; i++) {
        scanf(" %c", &aux);
        if(aux=='T') {
            scanf(" %c", &letra);
            inserta(letra);
        } else {
            scanf("%d", &val);
            if(aux=='U')
                undo(val+1);
            if(aux=='P')
                imprime(tope,val+1);
        }
    }
    return 0;
}