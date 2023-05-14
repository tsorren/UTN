#include <iostream>
#include <cstring>
using namespace std;
void Tendencia(int,int,char&);
int a,b;
char texto[20] = {"text"};
int main(){
    cout<<"\nIngrese dos valores: "; cin>>a>>b;
    Tendencia(a,b,texto);
    cout<<texto;
   return 0;
}
void Tendencia(int A, int B, char&){
    if((B-A)<0){
        strcpy(*texto,"Decreciente");
    }
    return;
}
/*
18.	Desarrollar la función
string Tendencia(int A, int B)que dados dos valores A y B, 
retorne una cadena de acuerdo al siguiente cuadro:

*/