/*

    Dada una serie de caracteres que conforman una oración, donde cada palabra esta
    separada de la siguiente por un carácter blanco y la oración finaliza con un punto. Se
    pide informar:
    cantidad de veces que apareció cada vocal
    cantidad de palabras que contiene la oración
    cantidad de letras que posee la palabra mas larga.

*/

#include<iostream>

using namespace std;

int main()
{
    char oracion[100] = "___________________________________________________________________________________________________";

    cout << "Ingrese una oración: " << endl;
    cin.getline(oracion, 100, '\n');
    char currentChar = ' ';
    int spaces = 0;
    int spacePosA = 0;
    int spacePosB = 0;

    int maxLength = 0;
    int wordCount = 0;

    int vocalA = 0;
    int vocalE = 0;
    int vocalI = 0;
    int vocalO = 0;
    int vocalU = 0;

    int i = 0;

    while(oracion[i] != '\0')
    {
        //cout << currentChar;
        currentChar = oracion[i];
        if(currentChar == 'A' || currentChar == 'a')
        {
            vocalA++;
        }
        else if(currentChar == 'E' || currentChar == 'e')
        {
            vocalE++;
        }
        else if(currentChar == 'I' || currentChar == 'i')
        {
            vocalI++;
        }
        else if(currentChar == 'O' || currentChar == 'o')
        {
            vocalO++;
        }
        else if(currentChar == 'U' || currentChar == 'u')
        {
            vocalU++;
        }

        if(currentChar == ' ' || currentChar == '.')
        {
            wordCount++;
            spaces++;

            spacePosA = spacePosB + 1;
            spacePosB = i;
            // cout << endl << "Posicion de espacio: " << i << endl;
        }

        if(abs(spacePosB - spacePosA) > maxLength)
        {
            maxLength = abs(spacePosB - spacePosA);
        }
        i++;

    }
    cout << "Cantidad de palabras: " << wordCount << endl;
    cout << "Caracteres de la palabra mas larga: " << maxLength << endl;

    //cout << spacePosA << " - " << spacePosB << endl;

    if(vocalA != 0)
        cout << endl << "Cantidad de a's: " << vocalA;

    if(vocalE != 0)
        cout << endl << "Cantidad de e's: " << vocalE;

    if(vocalI != 0)
        cout << endl << "Cantidad de i's: " << vocalI;

    if(vocalO != 0)
        cout << endl << "Cantidad de o's: " << vocalO;

    if(vocalU != 0)
        cout << endl << "Cantidad de u's: " << vocalU;

    cout << endl << endl;

    return 0;
}
