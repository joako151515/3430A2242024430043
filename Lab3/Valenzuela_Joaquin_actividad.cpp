#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// actividad 1: cola dinamica de estudiantes


// estructura estudiante
struct NodoEstudiante {
    string nombre;
    string carrera;
    float promedio;
    NodoEstudiante* siguiente;
};

// cola: necesitamos frente y final
struct Cola {
    NodoEstudiante* frente;
    NodoEstudiante* final;
};

// inicializar cola
void inicializarCola(Cola& cola) {
    cola.frente = nullptr;
    cola.final = nullptr;
}

// verificar si la cola esta vacia
bool esColaVacia(Cola cola) {
    return cola.frente == nullptr;
}

// insertar estudiante en la cola (encolar)
void insertarCola(Cola& cola, string nombre, string carrera, float promedio) {
    NodoEstudiante* nuevo = new NodoEstudiante();
    nuevo->nombre = nombre;
    nuevo->carrera = carrera;
    nuevo->promedio = promedio;
    nuevo->siguiente = nullptr;

    if (esColaVacia(cola)) {
        cola.frente = nuevo;
        cola.final = nuevo;
    } else {
        cola.final->siguiente = nuevo;
        cola.final = nuevo;
    }
    cout << "estudiante " << nombre << " agregado a la cola\n";
}

// eliminar estudiante de la cola (desencolar)
bool eliminarCola(Cola& cola, string& nombre, string& carrera, float& promedio) {
    if (esColaVacia(cola)) return false;

    NodoEstudiante* aux = cola.frente;
    nombre = aux->nombre;
    carrera = aux->carrera;
    promedio = aux->promedio;

    cola.frente = aux->siguiente;
    if (cola.frente == nullptr) cola.final = nullptr;

    delete aux;
    return true;
}

// mostrar contenido de la cola
void mostrarCola(Cola cola) {
    if (esColaVacia(cola)) {
        cout << "la cola esta vacia\n";
        return;
    }
    cout << "\ncontenido de la cola:\n";
    int i = 1;
    NodoEstudiante* actual = cola.frente;
    while (actual != nullptr) {
        cout << i << ". " << actual->nombre << " | "
             << actual->carrera << " | promedio: "
             << actual->promedio << endl;
        actual = actual->siguiente;
        i++;
    }
}


// actividad 2: lista dinamica de residuos proteicos


// estructura residuo
struct NodoResiduo {
    string resn;   // nombre del residuo
    string resid;  // id numerico del residuo
    string chain;  // cadena a la que pertenece
    NodoResiduo* siguiente;
};

// insertar residuo al final
void insertarResiduo(NodoResiduo*& lista, string resn, string resid, string chain) {
    NodoResiduo* nuevo = new NodoResiduo();
    nuevo->resn = resn;
    nuevo->resid = resid;
    nuevo->chain = chain;
    nuevo->siguiente = nullptr;

    if (lista == nullptr) {
        lista = nuevo;
    } else {
        NodoResiduo* actual = lista;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// modificar resn de un residuo (mutacion)
bool modificarResiduo(NodoResiduo* lista, string idBuscado, string nuevoResn) {
    NodoResiduo* actual = lista;
    while (actual != nullptr) {
        if (actual->resid == idBuscado) {
            actual->resn = nuevoResn;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

// eliminar residuo en una posicion
bool eliminarResiduo(NodoResiduo*& lista, int posicion) {
    if (lista == nullptr || posicion < 1) return false;

    NodoResiduo* actual = lista;
    if (posicion == 1) {
        lista = actual->siguiente;
        delete actual;
        return true;
    }

    NodoResiduo* anterior = nullptr;
    int contador = 1;
    while (actual != nullptr && contador < posicion) {
        anterior = actual;
        actual = actual->siguiente;
        contador++;
    }

    if (actual == nullptr) return false;

    anterior->siguiente = actual->siguiente;
    delete actual;
    return true;
}

// mostrar lista de residuos
void mostrarLista(NodoResiduo* lista) {
    if (lista == nullptr) {
        cout << "la lista esta vacia\n";
        return;
    }
    cout << "\nsecuencia de residuos:\n";
    NodoResiduo* actual = lista;
    while (actual != nullptr) {
        cout << actual->resn << actual->resid << "(" << actual->chain << ") -> ";
        actual = actual->siguiente;
    }
    cout << "null\n";
}


void exportarGraphviz(NodoResiduo* lista, string nombreArchivo) {
    ofstream file(nombreArchivo);
    if (!file.is_open()) {
        cout << "no se pudo crear el archivo\n";
        return;
    }
    file << "digraph G {\n";
    file << "rankdir=LR;\n";
    file << "node [style=filled, fillcolor=yellow];\n";

    NodoResiduo* actual = lista;
    while (actual != nullptr && actual->siguiente != nullptr) {
        file << actual->resn << actual->resid
             << " -> " << actual->siguiente->resn
             << actual->siguiente->resid << ";\n";
        actual = actual->siguiente;
    }

    file << "}\n";
    file.close();

    cout << "archivo .dot generado: " << nombreArchivo << endl;
    // generar imagen con system call
    string comando = "dot -Tpng " + nombreArchivo + " -o " + nombreArchivo + ".png";
    system(comando.c_str());
}


// programa principal


int main(int argc, char* argv[]) {
    Cola cola;
    inicializarCola(cola);

    NodoResiduo* lista = nullptr;

    int opcion;
    do {
        cout << "\n=== menu laboratorio 3 ===\n";
        cout << "1. insertar estudiante en cola\n";
        cout << "2. eliminar estudiante de cola\n";
        cout << "3. mostrar cola\n";
        cout << "4. leer pdb y crear lista de residuos (argv)\n";
        cout << "5. mostrar lista de residuos\n";
        cout << "6. modificar residuo (mutacion)\n";
        cout << "7. eliminar residuo en posicion\n";
        cout << "8. exportar lista a graphviz\n";
        cout << "9. salir\n";
        cout << "opcion: ";
        cin >> opcion;
        cin.ignore();

        string nombre, carrera, resid, resn, chain, archivo;
        float promedio;
        int pos;

        switch (opcion) {
            case 1:
                cout << "nombre: ";
                getline(cin, nombre);
                cout << "carrera: ";
                getline(cin, carrera);
                cout << "promedio: ";
                cin >> promedio;
                cin.ignore();
                insertarCola(cola, nombre, carrera, promedio);
                break;
            case 2:
                if (eliminarCola(cola, nombre, carrera, promedio)) {
                    cout << "se elimino: " << nombre << " | "
                         << carrera << " | " << promedio << endl;
                } else {
                    cout << "cola vacia\n";
                }
                break;
            case 3:
                mostrarCola(cola);
                break;
            case 4:
                if (argc < 2) {
                    cout << "debes pasar el archivo pdb como argumento\n";
                } else {
                    ifstream pdb(argv[1]);
                    string linea;
                    while (getline(pdb, linea)) {
                        if (linea.substr(0, 4) == "ATOM") {
                            string atomName = linea.substr(12, 4);
                            if (atomName.find("CA") != string::npos) {
                                resn = linea.substr(17, 3);
                                chain = linea.substr(21, 1);
                                resid = linea.substr(22, 4);
                                insertarResiduo(lista, resn, resid, chain);
                            }
                        }
                    }
                    pdb.close();
                    cout << "lista de residuos creada desde pdb\n";
                }
                break;
            case 5:
                mostrarLista(lista);
                break;
            case 6:
                cout << "id del residuo a modificar: ";
                getline(cin, resid);
                cout << "nuevo resn: ";
                getline(cin, resn);
                if (modificarResiduo(lista, resid, resn))
                    cout << "residuo modificado\n";
                else
                    cout << "residuo no encontrado\n";
                break;
            case 7:
                cout << "posicion a eliminar: ";
                cin >> pos;
                if (eliminarResiduo(lista, pos))
                    cout << "residuo eliminado\n";
                else
                    cout << "posicion invalida\n";
                break;
            case 8:
                exportarGraphviz(lista, "proteina.dot");
                break;
            case 9:
                cout << "saliendo...\n";
                break;
            default:
                cout << "opcion invalida\n";
        }
    } while (opcion != 9);

    return 0;
}
