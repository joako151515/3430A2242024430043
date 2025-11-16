#include <iostream>
#include <cstdlib>

using namespace std;

int Menu()
{
    int op;
    do {
        cout << "\n----- Menu -----\n";
        cout << "1) Ingresar arreglo\n";
        cout << "2) Buscar (secuencial)\n";
        cout << "3) Buscar (binaria)\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        cin >> op;
    } while(op < 0 || op > 3);
    return op;
}

// ordenamiento simple 
void Ordenar(int A[], int n)
{
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            if(A[j] < A[i]){
                int aux = A[i];
                A[i] = A[j];
                A[j] = aux;
            }
        }
    }
}

// busqueda secuencial normal
int BuscarSecuencial(int A[], int n, int x)
{
    for(int i = 0; i < n; i++){
        if(A[i] == x){
            return i;
        }
    }
    return -1;
}

// busqueda binaria del Tema 8
int BuscarBinaria(int A[], int n, int x)
{
    int izq = 0;
    int der = n - 1;
    int medio;

    while(izq <= der){
        medio = (izq + der) / 2;

        if(A[medio] == x){
            return medio;
        }
        if(x < A[medio]){
            der = medio - 1;
        } else {
            izq = medio + 1;
        }
    }

    return -1;
}

int main()
{
    int n;
    int arreglo[200];
    int opcion;
    int valor;
    bool cargado = false;

    opcion = Menu();

    while(opcion != 0)
    {
        switch(opcion)
        {
            case 1:
                cout << "Cantidad de elementos (max 200): ";
                cin >> n;
                if(n < 1 || n > 200){
                    cout << "Error en el valor\n";
                    break;
                }

                for(int i = 0; i < n; i++){
                    cout << "A[" << i << "]: ";
                    cin >> arreglo[i];
                }

                cargado = true;
                Ordenar(arreglo, n); // requerido para binaria
                cout << "Arreglo cargado y ordenado\n";
                break;

            case 2:
                if(!cargado){
                    cout << "Primero cargue el arreglo\n";
                    break;
                }

                cout << "Valor a buscar: ";
                cin >> valor;

                {
                    int pos = BuscarSecuencial(arreglo, n, valor);
                    if(pos == -1){
                        cout << "No se encontro\n";
                    } else {
                        cout << "Encontrado en la posicion " << pos << "\n";
                    }
                }
                break;

            case 3:
                if(!cargado){
                    cout << "Primero cargue el arreglo\n";
                    break;
                }

                cout << "Valor a buscar: ";
                cin >> valor;

                {
                    int pos = BuscarBinaria(arreglo, n, valor);
                    if(pos == -1){
                        cout << "No se encontro\n";
                    } else {
                        cout << "Encontrado en la posicion " << pos << "\n";
                    }
                }
                break;
        }

        opcion = Menu();
    }

    return 0;
}
