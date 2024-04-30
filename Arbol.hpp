#ifndef __ARBOL_H__
#define __ARBOL_H__

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
class Arbol {
public:
    T datos;
    Arbol* subarbol_izquierdo;
    Arbol* subarbol_derecho;
    Arbol* posicion;

    // Constructor
    Arbol(T datos, Arbol* pos = nullptr) {
        this->datos = datos;
        this->subarbol_izquierdo = nullptr;
        this->subarbol_derecho = nullptr;
        this->posicion = pos;
    }

    void inserta(T elem, Arbol* arbol) {
        if (arbol == nullptr) {
            arbol = new Arbol(elem, this);
            return;
        }

        if (elem < arbol->datos) {
            if (arbol->subarbol_izquierdo == nullptr) {
                arbol->subarbol_izquierdo = new Arbol(elem, arbol);
            } else {
                inserta(elem, arbol->subarbol_izquierdo);
            }
        } else {
            if (arbol->subarbol_derecho == nullptr) {
                arbol->subarbol_derecho = new Arbol(elem, arbol);
            } else {
                inserta(elem, arbol->subarbol_derecho);
            }
        }
    }

    Arbol* localiza(T elem, Arbol* arbol) {
        if (arbol == nullptr) {
            return nullptr;
        }

        if (elem == arbol->datos) {
            return arbol;
        } else if (elem < arbol->datos) {
            return localiza(elem, arbol->subarbol_izquierdo);
        } else {
            return localiza(elem, arbol->subarbol_derecho);
        }
    }

    Arbol* menor(Arbol* arbol) {
        if (arbol == nullptr) {
            return nullptr;
        }

        if (arbol->subarbol_izquierdo == nullptr) {
            return arbol;
        }

        return menor(arbol->subarbol_izquierdo);
    }

    Arbol* mayor(Arbol* arbol) {
        if (arbol == nullptr) {
            return nullptr;
        }

        if (arbol->subarbol_derecho == nullptr) {
            return arbol;
        }

        return mayor(arbol->subarbol_derecho);
    }

    bool es_hoja(Arbol* arbol) {
        if (arbol == nullptr) {
            return false;
        }

        return (arbol->subarbol_izquierdo == nullptr && arbol->subarbol_derecho == nullptr);
    }

    void recorrido_preorder(Arbol* arbol) {
        if (arbol == nullptr) {
            return;
        }

        // Imprimimos el dato del nodo actual
        cout << arbol->datos << " ";

        // Recorremos el subárbol izquierdo en preorden
        recorrido_preorder(arbol->subarbol_izquierdo);

        // Recorremos el subárbol derecho en preorden
        recorrido_preorder(arbol->subarbol_derecho);
    }

    void recorrido_inorder(Arbol* arbol) {
        if (arbol == nullptr) {
            return;
        }

        // Recorremos el subárbol izquierdo en inorden
        recorrido_inorder(arbol->subarbol_izquierdo);

        // Imprimimos el dato del nodo actual
        cout << arbol->datos << " ";

        // Recorremos el subárbol derecho en inorden
        recorrido_inorder(arbol->subarbol_derecho);
    }

    void recorrido_postorder(Arbol* arbol) {
        if (arbol == nullptr) {
            return;
        }

        // Recorremos el subárbol izquierdo en postorden
        recorrido_postorder(arbol->subarbol_izquierdo);

        // Recorremos el subárbol derecho en postorden
        recorrido_postorder(arbol->subarbol_derecho);

        // Imprimimos el dato del nodo actual
        cout << arbol->datos << " ";
    }

    void elimina(Arbol* pos, Arbol*& arbol) {
        if (arbol == nullptr || pos == nullptr) {
            cout << "Error: Árbol o posición nula." << endl;
            return;
        }

        if (es_hoja(pos)) {
            delete pos;
            arbol = nullptr;
            return;
        }

        Arbol* pos_reemplazo = nullptr;
        if (arbol->subarbol_izquierdo != nullptr) {
            pos_reemplazo = mayor(arbol->subarbol_izquierdo);
        } else {
            pos_reemplazo = menor(arbol->subarbol_derecho);
        }

        arbol->datos = pos_reemplazo->datos;
        elimina(pos_reemplazo, arbol->subarbol_izquierdo != nullptr ? arbol->subarbol_izquierdo : arbol->subarbol_derecho);
    }

    int altura(Arbol* arbol) {
        if (arbol == nullptr) {
            return 0;
        }

        int alt_izq = altura(arbol->subarbol_izquierdo);
        int alt_der = altura(arbol->subarbol_derecho);

        return max(alt_izq, alt_der) + 1;
    }

    int fact_eq(Arbol* arbol) {
        if (arbol == nullptr) {
            return 0;
        }

        return altura(arbol->subarbol_derecho) - altura(arbol->subarbol_izquierdo);
    }

    void rot_sim_der(Arbol*& arbol) {
        Arbol* aux1 = arbol->subarbol_izquierdo;
        Arbol* aux2 = aux1->subarbol_derecho;
        arbol->subarbol_izquierdo = aux2;
        aux1->subarbol_derecho = arbol;
        arbol = aux1;
    }

    // Rotación simple a la izquierda
    void rot_sim_izq(Arbol*& arbol) {
        Arbol* aux1 = arbol->subarbol_derecho;
        Arbol* aux2 = aux1->subarbol_izquierdo;
        arbol->subarbol_derecho = aux2;
        aux1->subarbol_izquierdo = arbol;
        arbol = aux1;
    }

    // Rotación doble a la derecha
    void rot_dbl_der(Arbol*& arbol) {
        Arbol* aux1 = arbol->subarbol_izquierdo;
        Arbol* aux2 = aux1->subarbol_derecho;
        Arbol* aux3 = aux2->subarbol_izquierdo;
        Arbol* aux4 = aux2->subarbol_derecho;
        arbol->subarbol_izquierdo = aux4;
        aux1->subarbol_derecho = aux3;
        aux2->subarbol_izquierdo = aux1;
        aux2->subarbol_derecho = arbol;
        arbol = aux2;
    }

    // Rotación doble a la izquierda
    void rot_dbl_izq(Arbol*& arbol) {
        Arbol* aux1 = arbol->subarbol_derecho;
        Arbol* aux2 = aux1->subarbol_izquierdo;
        Arbol* aux3 = aux2->subarbol_derecho;
        Arbol* aux4 = aux2->subarbol_izquierdo;
        arbol->subarbol_derecho = aux4;
        aux1->subarbol_izquierdo = aux3;
        aux2->subarbol_derecho = aux1;
        aux2->subarbol_izquierdo = arbol;
        arbol = aux2;
    }

    void balanceo(Arbol*& arbol) {
        if (arbol == nullptr) {
            return;
        }

        if (fact_eq(arbol) < -1) {
            if (fact_eq(arbol->subarbol_izquierdo) == -1) {
                rot_sim_der(arbol);
            } else {
                rot_dob_der(arbol);
            }
        } else if (fact_eq(arbol) > 1) {
            if (fact_eq(arbol->subarbol_derecho) == 1) {
                rot_sim_izq(arbol);
            } else {
                rot_dob_izq(arbol);
            }
        }
    }
};

#endif // __ARBOL_H__