#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {

    int N;

    // leer cantidad de nodos
    do {
        cout << "Cantidad de nodos (N > 2): ";
        cin >> N;
    } while (N <= 2);

    // crear matriz NxN
    int matriz[N][N];

    cout << "\nIngrese la matriz de distancias (use -1 para no conexion):\n";

    // leer matriz desde terminal
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "matriz[" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }

    // arreglos para prim
    int L[N];      // costo minimo acumulado
    int padre[N];  // nodo anterior
    bool V[N];     // nodos visitados

    // inicializar arreglos
    for (int i = 0; i < N; i++) {
        L[i] = -1;
        padre[i] = -1;
        V[i] = false;
    }

    // comenzar desde el nodo 0
    L[0] = 0;

    // algoritmo de prim
    for (int k = 0; k < N; k++) {

        int minimo = 999999;
        int pos = -1;

        // elegir nodo no visitado de menor costo
        for (int i = 0; i < N; i++) {
            if (!V[i] && L[i] >= 0 && L[i] < minimo) {
                minimo = L[i];
                pos = i;
            }
        }

        if (pos == -1)
            break;

        V[pos] = true;

        // actualizar costos
        for (int j = 0; j < N; j++) {
            if (matriz[pos][j] >= 0 && !V[j]) {

                int costo = matriz[pos][j];

                if (L[j] == -1 || costo < L[j]) {
                    L[j] = costo;
                    padre[j] = pos;
                }
            }
        }
    }

    // mostrar conjunto L
    cout << "\nConjunto L (costos minimos):\n";
    for (int i = 0; i < N; i++) {
        cout << "L[" << i << "] = " << L[i] << "  padre=" << padre[i] << endl;
    }

    // generar grafo original
    ofstream fp("grafo_original.txt");
    fp << "graph G {\n";
    fp << "graph [rankdir=LR]\n";
    fp << "node [style=filled fillcolor=\"#00ff005f\"]\n";

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matriz[i][j] >= 0) {
                fp << i << " -- " << j << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    fp << "}\n";
    fp.close();
    system("dot -Tpng -ografo_original.png grafo_original.txt");

    // generar grafo de costo minimo
    ofstream fp2("grafo_minimo.txt");
    fp2 << "graph G {\n";
    fp2 << "graph [rankdir=LR]\n";
    fp2 << "node [style=filled fillcolor=\"#00ff005f\"]\n";

    for (int i = 1; i < N; i++) {
        if (padre[i] != -1) {
            fp2 << padre[i] << " -- " << i << " [label=" << L[i] << "];\n";
        }
    }

    fp2 << "}\n";
    fp2.close();
    system("dot -Tpng -ografo_minimo.png grafo_minimo.txt");

    cout << "\nGrafos generados:\n";
    cout << " - grafo_original.png\n";
    cout << " - grafo_minimo.png\n";

    return 0;
}
