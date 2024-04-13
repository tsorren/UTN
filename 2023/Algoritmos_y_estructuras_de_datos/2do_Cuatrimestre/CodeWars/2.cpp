#include <iostream>
#include <cmath>
using namespace std;

int persistence(long long n)
{
  int number = n;
  int aux = 0;
  int l = log10(number) + 1;
  int p;
  
  for(p = 0; l > 1; p++)
  {
    aux = 1;
    for(int i = 0; i < l; i++)
    {
        aux *= number % (10);
        number /= 10;
    }
    number = aux;
    l = log10(number) + 1;
  }
  return p;
}

int main()
{
    //char c;
    //cin >> c;
    int p = persistence(39);
    cout << p;

    return 0;
}