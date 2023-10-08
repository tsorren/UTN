#include <iostream>
using namespace std;

int SumFromAtoB(int a, int b) // sum from a to b 
{
    if(a > b)
    {
        int aux = b;
        b = a;
        a = aux;
        return -((b*(b+1)/2) - (a*(a+1)/2));
    }
    return (b*(b+1)/2) - (a*(a+1)/2);
}
int main()
{
    cout << SumFromAtoB(6, 3) << endl;
    cout << SumFromAtoB(3, 6) << endl;
}