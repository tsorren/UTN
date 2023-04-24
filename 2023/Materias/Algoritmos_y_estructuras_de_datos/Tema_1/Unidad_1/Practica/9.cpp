/*

    Se realiza una inspección en una fábrica de pinturas, y se detectaron 20 infracciones.
    De cada infracción se tomó nota de los siguientes datos:
    - Tipo de Infracción (1, 2, 3, o 4)
    - Motivo de la Infracción
    - Valor de la multa (un entero)
    - Gravedad de la infracción (‘L’,‘M’, ‘G’)
    Se pide informar al final del proceso:
    • Los valores totales de la multa a pagar de acuerdo al tipo de gravedad.
    • La leyenda “Clausurar fabrica” si la cantidad de infracciones 3 y 4 con gravedad “G”
    sean mayor a 3.

    ----

    cin:
    - Tipo de Infracción (1, 2, 3, o 4)
    - Motivo de la Infracción
    - Valor de la multa (un entero)
    - Gravedad de la infracción (‘L’,‘M’, ‘G’)

    calcular:
    • Los valores totales de la multa a pagar de acuerdo al tipo de gravedad.

    condicion:    
    • La leyenda “Clausurar fabrica” si la cantidad de infracciones 3 y 4 con gravedad “G”
    sean mayor a 3.

*/

#include <iostream>

using namespace std;

int main()
{
    int cantidadInfracciones = 4;

    // Se informa:
    int infraccionMulta;                    // Entero
    int multaAgravada;                      // infraccionMulta multiplicada

    char infraccionTipo;                    // 1, 2, 3, 4
    char infraccionMotivo[16+1];            // Reporte, 1 palabra
    char infraccionGravedad;                // 'L', 'M', 'G' -> Leve, media, grave

    int cantidadInfraccionGrave = 0;        // Acumulador infracciones graves
    int valorTotalMultaLeve = 0;                // Acumulador multas agravadas
    int valorTotalMultaMedia = 0;                // Acumulador multas agravadas
    int valorTotalMultaGrave = 0;                // Acumulador multas agravadas

    int i;
    for(i = 0; i < cantidadInfracciones; i++)
    {
        cout << "REPORTE DE LA INFRACCION " << i+1 << ":" << endl << endl;

        cout << "Tipo de infracción: ";
        cin >> infraccionTipo;

        cout << "Motivo de la infracción: ";
        cin >> infraccionMotivo;

        cout << "Valor de la multa: $";
        cin >> infraccionMulta;

        cout << "Gravedad de la infracción: ";
        cin >> infraccionGravedad;

        if((infraccionTipo == '3' || infraccionTipo == '4') && infraccionGravedad == 'G')
        {
            cantidadInfraccionGrave++;
        }

        if(infraccionGravedad == 'L')
        {
            multaAgravada = infraccionMulta;
            valorTotalMultaLeve += multaAgravada;
        }
        else if (infraccionGravedad == 'M')
        {
            multaAgravada = infraccionMulta * 2;
            valorTotalMultaLeve += multaAgravada;
        }
        else if (infraccionGravedad == 'G')
        {
            multaAgravada = infraccionMulta * 3;
            valorTotalMultaLeve += multaAgravada;
        }

        cout << endl << "Multa agravada: $" << multaAgravada << endl << endl << "------------------------------------------------------------" << endl;

    }

    cout << endl << "Multa total a pagar:" << endl;
    cout << "Leve: $" << valorTotalMultaLeve << endl;
    cout << "Media: $" << valorTotalMultaMedia << endl;
    cout << "Grave: $" << valorTotalMultaGrave << endl << endl;

    if(cantidadInfraccionGrave > 3)
    {
        cout << "Clausurar fabrica" << endl;
    }

    return 0;
}
