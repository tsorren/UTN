/*

Que imprime el siguiente código
    a. std::cout << “*\n**\n***\n****” <<std::endl;
    b. std::cout << ‘A’;
    c. std::cout << static_cast< int > ‘A’; (que es static_cast? Investigue.)

*/

#include <iostream>

using namespace std;

int main()
{
    cout << "std::cout << \"*\\n**\\n***\\n****\" <<std::endl;" << endl;
    cout << "*\n**\n***\n****" << endl << endl;
    
    cout << "std::cout << 'A';" << endl;
    cout << 'A' << endl << endl;

    cout << "std::cout << static_cast< int > 'A'" << endl;
    cout << static_cast< int > ('A') << endl;

    return 0;
}
