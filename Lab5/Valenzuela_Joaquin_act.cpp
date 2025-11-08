#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

// estructura del nodo
typedef struct NODO {
    NODO* izq;
    NODO* der;
    string go;
    string funcion;
    float score;
    int FE;
} NODO;

// prototipos
void InsercionBalanceado(NODO** nodocabeza, bool* BO, string go, string funcion, float score);
void Busqueda(NODO* nodo, string go);
void Restructura1(NODO** nodocabeza, bool* BO);
void Restructura2(NODO** nodocabeza, bool* BO);
void Borra(NODO** aux1, NODO** otro1, bool* BO);
void EliminacionBalanceado(NODO** nodocabeza, bool* BO, string go);
void GenerarGrafo(NODO* p);
void PreOrden(NODO*, ofstream& fp);
void LeerArchivo(NODO** raiz, const char* nombreArchivo);
int Menu();

// funcion principal
int main() {
    int opcion;
    string codigo;
    string nombre;
    float valor;
    bool inicio;
    NODO* raiz = nullptr;

    LeerArchivo(&raiz, "funciones_GO.csv");

    opcion = Menu();

    while (opcion) {
        switch (opcion) {
            case 1:
                cout << "Codigo GO: ";
                cin >> codigo;
                cout << "Funcion: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Score: ";
                cin >> valor;
                inicio = false;
                InsercionBalanceado(&raiz, &inicio, codigo, nombre, valor);
                GenerarGrafo(raiz);
                break;

            case 2:
                cout << "Buscar codigo GO: ";
                cin >> codigo;
                Busqueda(raiz, codigo);
                break;

            case 3:
                cout << "Eliminar codigo GO: ";
                cin >> codigo;
                inicio = false;
                EliminacionBalanceado(&raiz, &inicio, codigo);
                GenerarGrafo(raiz);
                break;

            case 4:
                GenerarGrafo(raiz);
                cout << "Grafo generado (grafo.png)\n";
                break;

            case 0:
                return 0;
        }
        opcion = Menu();
    }
    return 0;
}

// menu
int Menu() {
    int Op;
    do {
        cout << "\n------ MENU ------\n";
        cout << "1) Insertar nuevo termino GO\n";
        cout << "2) Buscar termino GO\n";
        cout << "3) Eliminar termino GO\n";
        cout << "4) Mostrar grafo\n";
        cout << "0) Salir\n\n";
        cout << "Opcion: ";
        cin >> Op;
    } while (Op < 0 || Op > 4);
    return Op;
}

// lectura del archivo CSV
void LeerArchivo(NODO** raiz, const char* nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se encontro el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    bool inicio;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        char buffer[200];
        strcpy(buffer, linea.c_str());
        char* token = strtok(buffer, ",");
        if (!token) continue;
        string go = token;

        token = strtok(NULL, ",");
        if (!token) continue;
        string funcion = token;

        token = strtok(NULL, ",");
        if (!token) continue;
        float score = atof(token);

        inicio = false;
        InsercionBalanceado(raiz, &inicio, go, funcion, score);
    }
    archivo.close();
    GenerarGrafo(*raiz);
}

// insercion balanceada AVL
void InsercionBalanceado(NODO** nodocabeza, bool* BO, string go, string funcion, float score) {
    NODO* nodo = *nodocabeza;
    NODO* nodo1;
    NODO* nodo2;

    if (nodo != nullptr) {
        if (go < nodo->go) {
            InsercionBalanceado(&(nodo->izq), BO, go, funcion, score);
            if (*BO) {
                switch (nodo->FE) {
                    case 1:
                        nodo->FE = 0;
                        *BO = false;
                        break;
                    case 0:
                        nodo->FE = -1;
                        break;
                    case -1:
                        nodo1 = nodo->izq;
                        if (nodo1->FE <= 0) {
                            nodo->izq = nodo1->der;
                            nodo1->der = nodo;
                            nodo->FE = 0;
                            nodo = nodo1;
                        } else {
                            nodo2 = nodo1->der;
                            nodo->izq = nodo2->der;
                            nodo2->der = nodo;
                            nodo1->der = nodo2->izq;
                            nodo2->izq = nodo1;
                            if (nodo2->FE == -1)
                                nodo->FE = 1;
                            else
                                nodo->FE = 0;
                            if (nodo2->FE == 1)
                                nodo1->FE = -1;
                            else
                                nodo1->FE = 0;
                            nodo = nodo2;
                        }
                        nodo->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else if (go > nodo->go) {
            InsercionBalanceado(&(nodo->der), BO, go, funcion, score);
            if (*BO) {
                switch (nodo->FE) {
                    case -1:
                        nodo->FE = 0;
                        *BO = false;
                        break;
                    case 0:
                        nodo->FE = 1;
                        break;
                    case 1:
                        nodo1 = nodo->der;
                        if (nodo1->FE >= 0) {
                            nodo->der = nodo1->izq;
                            nodo1->izq = nodo;
                            nodo->FE = 0;
                            nodo = nodo1;
                        } else {
                            nodo2 = nodo1->izq;
                            nodo->der = nodo2->izq;
                            nodo2->izq = nodo;
                            nodo1->izq = nodo2->der;
                            nodo2->der = nodo1;
                            if (nodo2->FE == 1)
                                nodo->FE = -1;
                            else
                                nodo->FE = 0;
                            if (nodo2->FE == -1)
                                nodo1->FE = 1;
                            else
                                nodo1->FE = 0;
                            nodo = nodo2;
                        }
                        nodo->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else {
            cout << "El termino ya existe en el arbol\n";
        }
    } else {
        nodo = new NODO();
        nodo->izq = nullptr;
        nodo->der = nullptr;
        nodo->go = go;
        nodo->funcion = funcion;
        nodo->score = score;
        nodo->FE = 0;
        *BO = true;
    }

    *nodocabeza = nodo;
}

// busqueda de un termino
void Busqueda(NODO* nodo, string go) {
    if (nodo != nullptr) {
        if (go < nodo->go)
            Busqueda(nodo->izq, go);
        else if (go > nodo->go)
            Busqueda(nodo->der, go);
        else
            cout << "Codigo: " << nodo->go << " | Funcion: " << nodo->funcion << " | Score: " << nodo->score << endl;
    } else {
        cout << "El codigo no se encuentra en el arbol\n";
    }
}

// reestructuras
void Restructura1(NODO** nodocabeza, bool* BO) {
    NODO *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    if (*BO) {
        switch (nodo->FE) {
            case -1:
                nodo->FE = 0;
                break;
            case 0:
                nodo->FE = 1;
                *BO = false;
                break;
            case 1:
                nodo1 = nodo->der;
                if (nodo1->FE >= 0) {
                    nodo->der = nodo1->izq;
                    nodo1->izq = nodo;
                    nodo->FE = 0;
                    nodo1->FE = 0;
                    nodo = nodo1;
                } else {
                    nodo2 = nodo1->izq;
                    nodo->der = nodo2->izq;
                    nodo2->izq = nodo;
                    nodo1->izq = nodo2->der;
                    nodo2->der = nodo1;
                    if (nodo2->FE == 1)
                        nodo->FE = -1;
                    else
                        nodo->FE = 0;
                    if (nodo2->FE == -1)
                        nodo1->FE = 1;
                    else
                        nodo1->FE = 0;
                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }
    *nodocabeza = nodo;
}

void Restructura2(NODO** nodocabeza, bool* BO) {
    NODO *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    if (*BO) {
        switch (nodo->FE) {
            case 1:
                nodo->FE = 0;
                break;
            case 0:
                nodo->FE = -1;
                *BO = false;
                break;
            case -1:
                nodo1 = nodo->izq;
                if (nodo1->FE <= 0) {
                    nodo->izq = nodo1->der;
                    nodo1->der = nodo;
                    nodo->FE = 0;
                    nodo1->FE = 0;
                    nodo = nodo1;
                } else {
                    nodo2 = nodo1->der;
                    nodo->izq = nodo2->der;
                    nodo2->der = nodo;
                    nodo1->der = nodo2->izq;
                    nodo2->izq = nodo1;
                    if (nodo2->FE == -1)
                        nodo->FE = 1;
                    else
                        nodo->FE = 0;
                    if (nodo2->FE == 1)
                        nodo1->FE = -1;
                    else
                        nodo1->FE = 0;
                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }
    *nodocabeza = nodo;
}

// eliminacion
void Borra(NODO** aux1, NODO** otro1, bool* BO) {
    NODO *aux, *otro;
    aux = *aux1;
    otro = *otro1;
    if (aux->der != nullptr) {
        Borra(&(aux->der), &otro, BO);
        Restructura2(&aux, BO);
    } else {
        otro->go = aux->go;
        otro->funcion = aux->funcion;
        otro->score = aux->score;
        aux = aux->izq;
        *BO = true;
    }
    *aux1 = aux;
    *otro1 = otro;
}

void EliminacionBalanceado(NODO** nodocabeza, bool* BO, string go) {
    NODO *nodo, *otro;
    nodo = *nodocabeza;
    if (nodo != nullptr) {
        if (go < nodo->go) {
            EliminacionBalanceado(&(nodo->izq), BO, go);
            Restructura1(&nodo, BO);
        } else if (go > nodo->go) {
            EliminacionBalanceado(&(nodo->der), BO, go);
            Restructura2(&nodo, BO);
        } else {
            otro = nodo;
            if (otro->der == nullptr) {
                nodo = otro->izq;
                *BO = true;
                delete otro;
            } else if (otro->izq == nullptr) {
                nodo = otro->der;
                *BO = true;
                delete otro;
            } else {
                Borra(&(otro->izq), &otro, BO);
                Restructura1(&nodo, BO);
                delete otro;
            }
        }
    } else {
        cout << "El codigo no se encuentra en el arbol\n";
    }
    *nodocabeza = nodo;
}

// generar grafo con graphviz
void GenerarGrafo(NODO* ArbolInt) {
    if (!ArbolInt) return;
    ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=lightblue];\n";
    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz -> \"" << ArbolInt->go << "\";\n";
    PreOrden(ArbolInt, fp);
    fp << "}\n";
    fp.close();
    system("dot -Tpng -ografo.png grafo.txt");
}

// recorrido preorden
void PreOrden(NODO* a, ofstream& fp) {
    if (a != nullptr) {
        fp << "\"" << a->go << "\" [label=\"" << a->go << "\\n" << a->funcion << "\\n" << a->score << "\\nFE=" << a->FE << "\"];\n";
        if (a->izq != nullptr)
            fp << "\"" << a->go << "\" -> \"" << a->izq->go << "\";\n";
        else
            fp << "\"" << a->go << "\" -> \"" << a->go << "i\" [shape=point];\n";
        if (a->der != nullptr)
            fp << "\"" << a->go << "\" -> \"" << a->der->go << "\";\n";
        else
            fp << "\"" << a->go << "\" -> \"" << a->go << "d\" [shape=point];\n";

        PreOrden(a->izq, fp);
        PreOrden(a->der, fp);
    }
}
