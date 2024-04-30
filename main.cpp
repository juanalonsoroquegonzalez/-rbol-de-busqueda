#include <iostream>
#include <cstdlib>

#include "Arbol.hpp"

int main() {
    Arbol<int>* arbol = new Arbol<int>(5);

    arbol->inserta(3, arbol);
    arbol->inserta(8, arbol);
    arbol->inserta(2, arbol);
    arbol->inserta(4, arbol);
    arbol->inserta(7, arbol);
    arbol->inserta(9, arbol);

    cout << "Arbol:" << endl;
    cout << "   " << arbol->datos << endl;
    cout << "  / \\" << endl;
    cout << " " << arbol->subarbol_izquierdo->datos << "   " << arbol->subarbol_derecho->datos << endl;
    cout << " / \\ / \\" << endl;
    cout << arbol->subarbol_izquierdo->subarbol_izquierdo->datos << " " << arbol->subarbol_izquierdo->subarbol_derecho->datos << " " << arbol->subarbol_derecho->subarbol_izquierdo->datos << " " << arbol->subarbol_derecho->subarbol_derecho->datos << endl;

    arbol->recorrido_preorder(arbol);

    delete arbol;

    std::system("pause");

    return 0;
}
