#include <iostream>
#include <cstring>
using namespace std;
void Tendencia(int,int,char[20]);
int main(){
    int a,b;
    char texto[20];
    cout<<"\nIngrese dos valores: "; cin>>a>>b;
    Tendencia(a,b,texto);
    cout<<texto;
    return 0;
}
void Tendencia(int A, int B, char frase[20]){
    if((B-A)<0){
        strcpy(frase,"Decreciente");
    }
    else if((B-A)<(A*0.2)){
        strcpy(frase,"Estable");
    }
    else if ((B-A)<(A*0.5)){
        strcpy(frase,"Leve ascenso");
    }
    else{
        strcpy(frase,"En ascenso");
    }
    return;
}