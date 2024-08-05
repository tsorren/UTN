#include <stdio.h>
#include <assert.h>
#include <math.h>

void mostrar(long long int valor)
{
    printf("Resultado: %lld\n", valor);
    return;
}

int p1(int limite)
{
    int total = 0;

    for (int i = 1; i < limite; i++) 
    {
        if(i % 3 == 0)
            total += i;
        
        else if (i % 5 == 0)
            total += i;
    }
    return total;
}

void t1()
{
    assert(p1(10) == 23);
    mostrar(p1(10));
    mostrar(p1(1000));
}

int p2(int terminos)
{
    int total = 0;
    int termino1 = 0;
    int termino2 = 1;
    int suma = 0;

    for (int i = 0; i < terminos || (terminos == 0 && termino2 < 4000000); i++)
    {
        suma = termino2 + termino1;
        if(suma % 2 == 0)
            total += suma;

        termino1 = termino2;
        termino2 = suma;
    }
    return total;
}

void t2()
{
    assert(p2(10) == 44);
    mostrar(p2(10));
    mostrar(p2(0));
}
/* Resolucion chota
int p3(long long int num) 
{
    
    long long  maxFactor = 0;
    int esPrimo = 0;

    for (long long posibleMax = 1; posibleMax <= sqrt(num); posibleMax++)
    {
        esPrimo = 1;
        for (long long divisor = 2; divisor < posibleMax; divisor++)
        {
            if(posibleMax % divisor == 0)
                esPrimo = 0;
        }
        if (esPrimo && num % posibleMax == 0)
            maxFactor = posibleMax;
    }
    return maxFactor;
}

*/

int p3(long long int num, long long int maxFact) // Resolucion recursiva epica
{
    while(num % maxFact == 0)
        num = num / maxFact;

    if(num == 1)
        return maxFact;

    return p3(num, maxFact + 1);
}

void t3()
{
    assert(p3(13195, 2) == 29);
    mostrar(p3(13195, 2));
    mostrar(p3(600851475143, 2));
}

int p4(int digitos)
{
    int maxPal = 0;
    int numInicial = pow(10, digitos - 1);
    int numFinal = pow(10, digitos) - 1;
    int num = 0;
    int numReverso = 0;
    int cantDigitosNum = 0;
    int digito = 0;

    for (int i = numFinal; i > numInicial; i--)
    {
        for (int j = numFinal; j >= i; j--)
        {
            num = i * j;
            cantDigitosNum = ceil(log10(num));
            numReverso = 0;
            for (int k = 0; k < cantDigitosNum; k++)
            {
                digito = num % 10;
                numReverso += digito * pow(10, cantDigitosNum - 1 - k);
                num = num / 10;
            }
            num = i * j;

            if (num == numReverso && num > maxPal)
                maxPal = num;
        }
    }
    return maxPal;
}

void t4()
{
    assert(p4(2) == 9009);
    mostrar(p4(2));
    mostrar(p4(3));
    mostrar(p4(4));
}

int p5(int divFinal)
{
    long long int maxNum = 1;
    for (int i = 1; i <= divFinal; i++)
        maxNum *= i;

    int control = 1;

    //int minNum = maxNum;
    for (long long int num = 1; num < maxNum; num++)
    {
        control = 1;
        for (int divisor = 1; divisor <= divFinal && control; divisor++)
        {
            control = num % divisor == 0;
        }
        if(control)
            return num;
    }
}

void t5()
{
    assert(p5(10) == 2520);
    mostrar(p5(10));
    mostrar(p5(20));
}

int p6(int cantNumeros)
{
    int sumaHastaN = cantNumeros * (cantNumeros + 1) / 2;
    int sumaDeCuadrados = 0;
    for (int num = 1; num <= cantNumeros; num++)
        sumaDeCuadrados += num * num;

    return sumaHastaN * sumaHastaN - sumaDeCuadrados;
}   

void t6()
{
    assert(p6(10) == 2640);
    mostrar(p6(10));
    mostrar(p6(100));
}

long long int p7(int nEsimo)
{
    int cantPrimos = 0;
    int num = 1;
    int esPrimo = 1;
    while(cantPrimos < nEsimo)
    {
        num++;
        esPrimo = 1;
        for (int divisor = 2; divisor <= sqrt(num); divisor++)
        {
            if(num % divisor == 0)
                esPrimo = 0;
        }
        if(esPrimo)
            cantPrimos++;
    }
    return num;
}

void t7()
{
    assert(p7(6) == 13);
    mostrar(p7(6));
    mostrar(p7(10001));
}

long long int p8(int cantDigitos)
{
    int numeros[1000] = {
        7, 3, 1, 6, 7, 1, 7, 6, 5, 3, 1, 3, 3, 0, 6, 2, 4, 9, 1, 9, 2, 2, 5, 1, 1, 9, 6, 7, 4, 4, 2, 6, 5, 7, 4, 7, 4, 2, 3, 5, 5, 3, 4, 9, 1, 9, 4, 9, 3, 4,
        9, 6, 9, 8, 3, 5, 2, 0, 3, 1, 2, 7, 7, 4, 5, 0, 6, 3, 2, 6, 2, 3, 9, 5, 7, 8, 3, 1, 8, 0, 1, 6, 9, 8, 4, 8, 0, 1, 8, 6, 9, 4, 7, 8, 8, 5, 1, 8, 4, 3,
        8, 5, 8, 6, 1, 5, 6, 0, 7, 8, 9, 1, 1, 2, 9, 4, 9, 4, 9, 5, 4, 5, 9, 5, 0, 1, 7, 3, 7, 9, 5, 8, 3, 3, 1, 9, 5, 2, 8, 5, 3, 2, 0, 8, 8, 0, 5, 5, 1, 1,
        1, 2, 5, 4, 0, 6, 9, 8, 7, 4, 7, 1, 5, 8, 5, 2, 3, 8, 6, 3, 0, 5, 0, 7, 1, 5, 6, 9, 3, 2, 9, 0, 9, 6, 3, 2, 9, 5, 2, 2, 7, 4, 4, 3, 0, 4, 3, 5, 5, 7,
        6, 6, 8, 9, 6, 6, 4, 8, 9, 5, 0, 4, 4, 5, 2, 4, 4, 5, 2, 3, 1, 6, 1, 7, 3, 1, 8, 5, 6, 4, 0, 3, 0, 9, 8, 7, 1, 1, 1, 2, 1, 7, 2, 2, 3, 8, 3, 1, 1, 3,
        6, 2, 2, 2, 9, 8, 9, 3, 4, 2, 3, 3, 8, 0, 3, 0, 8, 1, 3, 5, 3, 3, 6, 2, 7, 6, 6, 1, 4, 2, 8, 2, 8, 0, 6, 4, 4, 4, 4, 8, 6, 6, 4, 5, 2, 3, 8, 7, 4, 9,
        3, 0, 3, 5, 8, 9, 0, 7, 2, 9, 6, 2, 9, 0, 4, 9, 1, 5, 6, 0, 4, 4, 0, 7, 7, 2, 3, 9, 0, 7, 1, 3, 8, 1, 0, 5, 1, 5, 8, 5, 9, 3, 0, 7, 9, 6, 0, 8, 6, 6,
        7, 0, 1, 7, 2, 4, 2, 7, 1, 2, 1, 8, 8, 3, 9, 9, 8, 7, 9, 7, 9, 0, 8, 7, 9, 2, 2, 7, 4, 9, 2, 1, 9, 0, 1, 6, 9, 9, 7, 2, 0, 8, 8, 8, 0, 9, 3, 7, 7, 6,
        6, 5, 7, 2, 7, 3, 3, 3, 0, 0, 1, 0, 5, 3, 3, 6, 7, 8, 8, 1, 2, 2, 0, 2, 3, 5, 4, 2, 1, 8, 0, 9, 7, 5, 1, 2, 5, 4, 5, 4, 0, 5, 9, 4, 7, 5, 2, 2, 4, 3,
        5, 2, 5, 8, 4, 9, 0, 7, 7, 1, 1, 6, 7, 0, 5, 5, 6, 0, 1, 3, 6, 0, 4, 8, 3, 9, 5, 8, 6, 4, 4, 6, 7, 0, 6, 3, 2, 4, 4, 1, 5, 7, 2, 2, 1, 5, 5, 3, 9, 7,
        5, 3, 6, 9, 7, 8, 1, 7, 9, 7, 7, 8, 4, 6, 1, 7, 4, 0, 6, 4, 9, 5, 5, 1, 4, 9, 2, 9, 0, 8, 6, 2, 5, 6, 9, 3, 2, 1, 9, 7, 8, 4, 6, 8, 6, 2, 2, 4, 8, 2,
        8, 3, 9, 7, 2, 2, 4, 1, 3, 7, 5, 6, 5, 7, 0, 5, 6, 0, 5, 7, 4, 9, 0, 2, 6, 1, 4, 0, 7, 9, 7, 2, 9, 6, 8, 6, 5, 2, 4, 1, 4, 5, 3, 5, 1, 0, 0, 4, 7, 4,
        8, 2, 1, 6, 6, 3, 7, 0, 4, 8, 4, 4, 0, 3, 1, 9, 9, 8, 9, 0, 0, 0, 8, 8, 9, 5, 2, 4, 3, 4, 5, 0, 6, 5, 8, 5, 4, 1, 2, 2, 7, 5, 8, 8, 6, 6, 6, 8, 8, 1,
        1, 6, 4, 2, 7, 1, 7, 1, 4, 7, 9, 9, 2, 4, 4, 4, 2, 9, 2, 8, 2, 3, 0, 8, 6, 3, 4, 6, 5, 6, 7, 4, 8, 1, 3, 9, 1, 9, 1, 2, 3, 1, 6, 2, 8, 2, 4, 5, 8, 6,
        1, 7, 8, 6, 6, 4, 5, 8, 3, 5, 9, 1, 2, 4, 5, 6, 6, 5, 2, 9, 4, 7, 6, 5, 4, 5, 6, 8, 2, 8, 4, 8, 9, 1, 2, 8, 8, 3, 1, 4, 2, 6, 0, 7, 6, 9, 0, 0, 4, 2,
        2, 4, 2, 1, 9, 0, 2, 2, 6, 7, 1, 0, 5, 5, 6, 2, 6, 3, 2, 1, 1, 1, 1, 1, 0, 9, 3, 7, 0, 5, 4, 4, 2, 1, 7, 5, 0, 6, 9, 4, 1, 6, 5, 8, 9, 6, 0, 4, 0, 8,
        0, 7, 1, 9, 8, 4, 0, 3, 8, 5, 0, 9, 6, 2, 4, 5, 5, 4, 4, 4, 3, 6, 2, 9, 8, 1, 2, 3, 0, 9, 8, 7, 8, 7, 9, 9, 2, 7, 2, 4, 4, 2, 8, 4, 9, 0, 9, 1, 8, 8,
        8, 4, 5, 8, 0, 1, 5, 6, 1, 6, 6, 0, 9, 7, 9, 1, 9, 1, 3, 3, 8, 7, 5, 4, 9, 9, 2, 0, 0, 5, 2, 4, 0, 6, 3, 6, 8, 9, 9, 1, 2, 5, 6, 0, 7, 1, 7, 6, 0, 6,
        0, 5, 8, 8, 6, 1, 1, 6, 4, 6, 7, 1, 0, 9, 4, 0, 5, 0, 7, 7, 5, 4, 1, 0, 0, 2, 2, 5, 6, 9, 8, 3, 1, 5, 5, 2, 0, 0, 0, 5, 5, 9, 3, 5, 7, 2, 9, 7, 2, 5,
        7, 1, 6, 3, 6, 2, 6, 9, 5, 6, 1, 8, 8, 2, 6, 7, 0, 4, 2, 8, 2, 5, 2, 4, 8, 3, 6, 0, 0, 8, 2, 3, 2, 5, 7, 5, 3, 0, 4, 2, 0, 7, 5, 2, 9, 6, 3, 4, 5, 0};

    long long int productoMaximo = 0;
    long long int  producto = 0;
    long long int digitos = 0;
    for (int indice = 0; indice < 1000 - cantDigitos; indice++)
    {
        producto = 1;
        digitos = 0;

        for (int subIndice = indice; subIndice < indice + cantDigitos; subIndice++)
        {
            digitos += numeros[subIndice] * pow(10, cantDigitos - (subIndice - indice) - 1);
            producto *= numeros[subIndice];
        }
        
        if(producto > productoMaximo)
            productoMaximo = producto;
    }
    return productoMaximo;
}

void t8()
{
    assert(p8(4) == 5832);
    mostrar(p8(4));
    mostrar(p8(13));
}

int p9(int numero)
{
    int a = 1;
    int b = 2;
    int c = 3;
    int suma = 0;
    int producto = 0;

    while(a <= numero - b - c)
    {
        while(b <= numero - a - c)
        {
            c = sqrt(a * a + b * b);
            if(a*a + b*b == c*c)
            {
                suma = a + b + c;
                producto = a * b * c;
                if(suma == numero)
                    return producto;
            }
            b++;
        }
        a++;
        b = a + 1;
    }
}

long long int p10(int numero)
{
    if(numero == 1)
        return 2;

    if(numero == 2)
        return 5;

    long long int suma = 5;
    long long int  primo = 0;
    long long int  entero = 1;
    int raiz = 0;
    int esPrimo = 0;
    int iteracion = 0;

    primo = 5;

    while(primo < numero)
    {
        esPrimo = 1;
        raiz = sqrt(primo);
        for (int divisor = 2; divisor <= raiz; divisor++)
        {
            if(primo % divisor == 0)
                esPrimo = 0;
        }
        
        iteracion++;
        if(esPrimo)
            suma += primo;

        primo = 6 * entero;
        if(iteracion % 2)
        {
            primo += 1;
            entero++;
        }
        else
            primo -= 1;
    }
    return suma;
}

void t9()
{
    mostrar(p9(12));
    assert(p9(12) == 60);
    mostrar(p9(1000));
}

void t10()
{
    assert(p10(10) == 17);
    mostrar(p10(10));
    mostrar(p10(2000000));
}

int main()
{
    t10();
    return 0;
}