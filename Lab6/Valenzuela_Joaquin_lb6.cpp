#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
    int N;
    int origen;

    // leer cantidad de nodos
    do {
        cout << "Cantidad de nodos (N > 2): ";
        cin >> N;
    } while (N <= 2);

    // crear matriz NxN
    int matriz[N][N];

    // leer matriz desde terminal
    cout << "\nIngrese la matriz de distancias (use -1 para no conexion):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "matriz[" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }

    // leer vertice origen
    do {
        cout << "\nVertice origen (0 a " << N-1 << "): ";
        cin >> origen;
    } while (origen < 0 || origen >= N);

    // arreglo de distancias
    int D[N];
    // arreglo de visitados
    bool V[N];

    // inicializar arreglos
    for (int i = 0; i < N; i++) {
        D[i] = matriz[origen][i];
        V[i] = false;
    }

    V[origen] = true;
    D[origen] = 0;

    // algoritmo de dijkstra
    for (int k = 0; k < N - 1; k++) {

        int minimo = 999999;
        int pos = -1;

        // buscar el nodo no visitado con menor distancia
        for (int i = 0; i < N; i++) {
            if (!V[i] && D[i] >= 0 && D[i] < minimo) {
                minimo = D[i];
                pos = i;
            }
        }

        if (pos == -1)
            break;

        V[pos] = true;

        // actualizar distancias
        for (int j = 0; j < N; j++) {
            if (matriz[pos][j] >= 0) {

                int nuevo = D[pos] + matriz[pos][j];

                if (D[j] == -1 || nuevo < D[j])
                    D[j] = nuevo;
            }
        }
    }

    // mostrar distancias finales
    cout << "\nDistancias minimas desde origen " << origen << ":\n";
    for (int i = 0; i < N; i++) {
        cout << "D[" << i << "] = " << D[i] << endl;
    }

    // generar archivo para graphviz
    ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "graph [rankdir=LR]\n";
    fp << "node [style=filled fillcolor=\"#00ff005f\"]\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriz[i][j] >= 0) {
                fp << i << " -> " << j << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");

    cout << "\nGrafo generado: grafo.png\n";

    return 0;
}
