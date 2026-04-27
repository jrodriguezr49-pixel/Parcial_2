#include <iostream>
#include <string>
using namespace std;
//Nodo creado para la cola, pila y lista simple
struct NodoSimple {
    int dato;
    NodoSimple* siguiente;
};
//Nodo utilizado para historial
struct NodoDoble {
    int valor;
    string estructura;
    int orden;
    NodoDoble* anterior;
    NodoDoble* siguiente;
};
//Nodo creado para arbol BST
struct NodoBST {
    int dato;
    NodoBST* izquierda;
    NodoBST* derecha;
};
//Funciones para insertar
void insertarPila(NodoSimple*& pila, int valor);
void insertarCola(NodoSimple*& frente, NodoSimple*& fin, int valor);
void insertarListaSimple(NodoSimple*& lista, int valor);
void insertarListaDoble(NodoDoble*& historial, int valor, string estructura, int orden);
//Funciones para mostrar lista e historial
void mostrarLista(NodoSimple* lista, string nombre);
void mostrarHistorial(NodoDoble* historial);
//Funcion para eliminar magnitudes menores a 10
int eliminarMagnitudMenor10(NodoSimple*& lista);
//Funciones para el funcionamiento del arbol
void insertarBST(NodoBST*& raiz, int valor);
void construirBSTDesdeLista(NodoBST*& raiz, NodoSimple* lista);
void inorden(NodoBST* raiz);
void preorden(NodoBST* raiz);
void postorden(NodoBST* raiz);
bool buscarBST(NodoBST* raiz, int valor);
//Funciones para liberar la memoria
void liberarLista(NodoSimple*& lista);
void liberarHistorial(NodoDoble*& historial);
void liberarBST(NodoBST*& raiz);
//Funciones para reorganizar
void vaciarPilaALista(NodoSimple*& pila, NodoSimple*& listaAux);
void vaciarColaALista(NodoSimple*& frente, NodoSimple*& fin, NodoSimple*& listaAux);

int main() {
	//Punteros principales del programa
    NodoSimple* pila = NULL;
    NodoSimple* colaFrente = NULL;
    NodoSimple* colaFin = NULL;
    NodoSimple* negativos = NULL;

    NodoDoble* historial = NULL;
    NodoBST* arbol = NULL;

    int opcion;
    int orden = 0;
	//Variables inicializadas en cero para la clasificacion de los datos, es importante iniciarlas en cero
    int pares = 0, impares = 0, cantNegativos = 0, ceros = 0;
    int totalValidos = 0;
    int mayor = 0, menor = 0;
    bool hayValores = false;
    bool arbolConstruido = false;

    do {
        cout << "\nParcial 2 programacion Javier David Rodriguez Rosales 9941-24-71\n";
        cout << "1. Ingresar N numeros\n";
        cout << "2. Mostrar pila\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Mostrar lista de negativos\n";
        cout << "5. Mostrar historial\n";
        cout << "6. Construir y mostrar BST\n";
        cout << "7. Eliminar negativos segun condicion\n";
        cout << "8. Buscar un valor en el BST\n";
        cout << "9. Mostrar estadisticas\n";
        cout << "10. Reorganizar estructuras\n";
        cout << "11. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
	//Condicion para validar el menu, evita ingresar opciones invalidas y si se ingresa lanza un mensaje 
        while (opcion < 1 || opcion > 11) {
            cout << "Opcion invalida. Ingrese otra opcion: ";
            cin >> opcion;
        }
	//Construccion del menu completo mediante un switch
        switch (opcion) {
        //Funcion para ingresar numeros
        case 1: {
        int n, valor;
        cout << "Cuantos numeros desea ingresar: ";
        cin >> n;
	//En el while se condiciona a que el valor ingresado debe ser mayor a cero
             while (n <= 0) {
                    cout << "N debe ser mayor que 0. Ingrese nuevamente: ";
                    cin >> n;
                }

            for (int i = 1; i <= n; i++) {
            cout << "Ingrese numero " << i << ": ";
            cin >> valor;
			//Se condiciona para que no sea posible ingresar el valor cero
                if (valor == 0) {
                    ceros++;
                    cout << "El cero fue rechazado.\n";} 
                    else {
                    orden++;
                    totalValidos++;
			//Primeros datos para mayor y menor
                if (!hayValores) {
                    mayor = valor;
                    menor = valor;
                    hayValores = true;} 
					else {
                if (valor > mayor) mayor = valor;
                if (valor < menor) menor = valor;}
			//Funcion para numero par y positivo y que se agregue a la cola
                if (valor > 0 && valor % 2 == 0) {
                    insertarCola(colaFrente, colaFin, valor);
                    insertarListaDoble(historial, valor, "COLA", orden);
                    pares++;}
			//Funcion para numero impar y positivo para agrefarlo a pila 
                else if (valor > 0 && valor % 2 != 0) {
                    insertarPila(pila, valor);
                    insertarListaDoble(historial, valor, "PILA", orden);
                    impares++;}
			//Funcion para numero negativo y sea agregado a la lista simple 
                    else {
                    insertarListaSimple(negativos, valor);
                    insertarListaDoble(historial, valor, "LISTA SIMPLE", orden);
                    cantNegativos++;
                        }
                    }
                }
			//Funcion que hace que al ingresar nuevos datos se reinicia el arbol BST
                arbolConstruido = false;
                liberarBST(arbol);
                break;
            }
			//Opcion para mostrar la pila
            case 2:
                mostrarLista(pila, "PILA");
                break;
			//Opcion para mostrar la lista de la cola
            case 3:
                mostrarLista(colaFrente, "COLA");
                break;
			//Opcion para mostrar la lista de negativos
            case 4:
                mostrarLista(negativos, "LISTA DE NEGATIVOS");
                break;
			//Opcion para mostrar el historial
            case 5:
                mostrarHistorial(historial);
                break;
			//Opcion para construir el arbol
            case 6:
                liberarBST(arbol);
                arbol = NULL;

                construirBSTDesdeLista(arbol, pila);
                construirBSTDesdeLista(arbol, colaFrente);

                if (arbol == NULL) {
                    cout << "No hay numeros positivos para construir el BST.\n";
                } else {
                    arbolConstruido = true;
                    cout << "\nBST construido correctamente.\n";

                    cout << "InOrden: ";
                    inorden(arbol);

                    cout << "\nPreOrden: ";
                    preorden(arbol);

                    cout << "\nPostOrden: ";
                    postorden(arbol);
                    cout << endl;
                }
                break;
			//Opcion para eliminar negativos
            case 7: {
                cout << "\nLista original:\n";
                mostrarLista(negativos, "NEGATIVOS");

                int eliminados = eliminarMagnitudMenor10(negativos);
                cantNegativos -= eliminados;
                totalValidos -= eliminados;

                cout << "\nLista resultante:\n";
                mostrarLista(negativos, "NEGATIVOS");

                cout << "Nodos eliminados: " << eliminados << endl;
                break;
            }
			//Opcion para buscar en el arbol
            case 8: {
                if (!arbolConstruido || arbol == NULL) {
                    cout << "Primero debe construir el BST.\n";
                } else {
                    int buscado;
                    cout << "Ingrese valor a buscar: ";
                    cin >> buscado;

                    if (buscarBST(arbol, buscado)) {
                        cout << "El valor SI existe en el BST.\n";
                    } else {
                        cout << "El valor NO existe en el BST.\n";
                    }
                }
                break;
            }
			//Opcion para clasificacion de datos
            case 9:
                cout << "Pares positivos: " << pares << endl;
                cout << "Impares positivos: " << impares << endl;
                cout << "Negativos: " << cantNegativos << endl;
                cout << "Ceros rechazados: " << ceros << endl;
                cout << "Total de valores validos: " << totalValidos << endl;

                if (hayValores) {
                    cout << "Mayor valor ingresado: " << mayor << endl;
                    cout << "Menor valor ingresado: " << menor << endl;
                } else {
                    cout << "No hay valores validos ingresados.\n";
                }
                break;
			//Reorganizacion
            case 10: {
                NodoSimple* listaPila = NULL;
                NodoSimple* listaCola = NULL;

                vaciarPilaALista(pila, listaPila);
                vaciarColaALista(colaFrente, colaFin, listaCola);

                cout << "\nDatos vaciados desde la pila:\n";
                mostrarLista(listaPila, "LISTA AUXILIAR PILA");

                cout << "\nDatos vaciados desde la cola:\n";
                mostrarLista(listaCola, "LISTA AUXILIAR COLA");
			//Reconstruir el arbol
                liberarBST(arbol);
                arbol = NULL;

                construirBSTDesdeLista(arbol, listaPila);
                construirBSTDesdeLista(arbol, listaCola);

                if (arbol == NULL) {
                    cout << "No se pudo reconstruir el BST porque no hay datos.\n";
                    arbolConstruido = false;
                } else {
                    arbolConstruido = true;
                    cout << "\nBST reconstruido con datos de pila y cola.\n";
                    cout << "InOrden: ";
                    inorden(arbol);
                    cout << endl;
                }

                liberarLista(listaPila);
                liberarLista(listaCola);
                break;
            }

            case 11:
                cout << "Liberando memoria y saliendo...\n";
                break;
        }

    } while (opcion != 11);
	//Liberacion de memoria
    liberarLista(pila);
    liberarLista(colaFrente);
    liberarLista(negativos);
    liberarHistorial(historial);
    liberarBST(arbol);

    return 0;
}
//Funciones para insertar los datos
//Funcion para insertar en pila
void insertarPila(NodoSimple*& pila, int valor) {
    NodoSimple* nuevo = new NodoSimple;
    nuevo->dato = valor;
    nuevo->siguiente = pila;
    pila = nuevo;
}
//Insertar en cola
void insertarCola(NodoSimple*& frente, NodoSimple*& fin, int valor) {
    NodoSimple* nuevo = new NodoSimple;
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (frente == NULL) {
        frente = nuevo;
        fin = nuevo;
    } else {
        fin->siguiente = nuevo;
        fin = nuevo;
    }
}
//Insertar al final en la lista simple
void insertarListaSimple(NodoSimple*& lista, int valor) {
    NodoSimple* nuevo = new NodoSimple;
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        NodoSimple* aux = lista;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}
//Insertar historial en la lista
void insertarListaDoble(NodoDoble*& historial, int valor, string estructura, int orden) {
    NodoDoble* nuevo = new NodoDoble;
    nuevo->valor = valor;
    nuevo->estructura = estructura;
    nuevo->orden = orden;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    if (historial == NULL) {
        historial = nuevo;
    } else {
        NodoDoble* aux = historial;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
        nuevo->anterior = aux;
    }
}
//Funcion para mostrar
void mostrarLista(NodoSimple* lista, string nombre) {
    if (lista == NULL) {
        cout << nombre << " vacia.\n";
        return;
    }

    cout << nombre << ": ";
    while (lista != NULL) {
        cout << lista->dato << " -> ";
        lista = lista->siguiente;
    }
    cout << "NULL\n";
}
//Funcion para mostrar historial
void mostrarHistorial(NodoDoble* historial) {
    if (historial == NULL) {
        cout << "Historial vacio.\n";
        return;
    }

    cout << "\n===== HISTORIAL =====\n";
    while (historial != NULL) {
        cout << historial->orden << ". "
             << historial->valor << " -> "
             << historial->estructura << endl;

        historial = historial->siguiente;
    }
}
//Funcion para eliminar negativos
int eliminarMagnitudMenor10(NodoSimple*& lista) {
    int eliminados = 0;

    while (lista != NULL && lista->dato > -10 && lista->dato < 0) {
        NodoSimple* temp = lista;
        lista = lista->siguiente;
        delete temp;
        eliminados++;
    }

    NodoSimple* actual = lista;

    while (actual != NULL && actual->siguiente != NULL) {
        if (actual->siguiente->dato > -10 && actual->siguiente->dato < 0) {
            NodoSimple* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            eliminados++;
        } else {
            actual = actual->siguiente;
        }
    }

    return eliminados;
}
//Funcion arbol BST
void insertarBST(NodoBST*& raiz, int valor) {
    if (raiz == NULL) {
        raiz = new NodoBST;
        raiz->dato = valor;
        raiz->izquierda = NULL;
        raiz->derecha = NULL;
    } else if (valor < raiz->dato) {
        insertarBST(raiz->izquierda, valor);
    } else {
        insertarBST(raiz->derecha, valor);
    }
}
//Funcion para construir el arbol BST
void construirBSTDesdeLista(NodoBST*& raiz, NodoSimple* lista) {
    while (lista != NULL) {
        if (lista->dato > 0) {
            insertarBST(raiz, lista->dato);
        }
        lista = lista->siguiente;
    }
}
//Ordenar arbol Inorden
void inorden(NodoBST* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        cout << raiz->dato << " ";
        inorden(raiz->derecha);
    }
}
//Ordenar arbol Preorden
void preorden(NodoBST* raiz) {
    if (raiz != NULL) {
        cout << raiz->dato << " ";
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}
//Ordenar arbol Postorden
void postorden(NodoBST* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        cout << raiz->dato << " ";
    }
}
//Funcion para buscar en el arbol
bool buscarBST(NodoBST* raiz, int valor) {
    if (raiz == NULL) {
        return false;
    }

    if (raiz->dato == valor) {
        return true;
    }

    if (valor < raiz->dato) {
        return buscarBST(raiz->izquierda, valor);
    } else {
        return buscarBST(raiz->derecha, valor);
    }
}
//Funcion para liberar memoria
void liberarLista(NodoSimple*& lista) {
    while (lista != NULL) {
        NodoSimple* temp = lista;
        lista = lista->siguiente;
        delete temp;
    }
}
//Funcio para liberar historial
void liberarHistorial(NodoDoble*& historial) {
    while (historial != NULL) {
        NodoDoble* temp = historial;
        historial = historial->siguiente;
        delete temp;
    }
}
//Funcion para liberar arbol BST
void liberarBST(NodoBST*& raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->izquierda);
        liberarBST(raiz->derecha);
        delete raiz;
        raiz = NULL;
    }
}
//Funcion para limpiar pila
void vaciarPilaALista(NodoSimple*& pila, NodoSimple*& listaAux) {
    while (pila != NULL) {
        NodoSimple* temp = pila;
        int valor = temp->dato;
        pila = pila->siguiente;
        delete temp;

        insertarListaSimple(listaAux, valor);
    }
}
//Funcion para limpiar cola
void vaciarColaALista(NodoSimple*& frente, NodoSimple*& fin, NodoSimple*& listaAux) {
    while (frente != NULL) {
        NodoSimple* temp = frente;
        int valor = temp->dato;
        frente = frente->siguiente;
        delete temp;

        insertarListaSimple(listaAux, valor);
    }

    fin = NULL;
}