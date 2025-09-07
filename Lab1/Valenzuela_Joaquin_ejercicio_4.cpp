#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Patient{
    string name;
    int age;
    float weight;
    float height;
    Patient *next;
};

Patient* createPatient(string n,int a,float w,float h){
    Patient *p=new Patient;
    p->name=n;
    p->age=a;
    p->weight=w;
    p->height=h;
    p->next=NULL;
    return p;
}

void addPatient(Patient **head,Patient *p){
    if(*head==NULL){
        *head=p;
    } else {
        Patient *aux=*head;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=p;
    }
}

void printPatients(Patient *head){
    Patient *aux=head;
    while(aux!=NULL){
        cout << aux->name << endl;
        cout << aux->age << " años" << endl;
        cout << aux->weight << " kg" << endl;
        cout << aux->height << " m" << endl;
        cout << "-----------" << endl;
        aux=aux->next;
    }
}

void loadFromFile(Patient **head,string file){
    ifstream in(file);
    if(!in.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
    string n; int a; float w,h;
    while(in >> n >> a >> w >> h){
        addPatient(head,createPatient(n,a,w,h));
    }
    in.close();
}

int main(){
    Patient *head=NULL;
    int opcion=0;

    do{
        cout << "\n1. Agregar paciente" << endl;
        cout << "2. Mostrar pacientes" << endl;
        cout << "3. Cargar desde archivo" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion==1){
            string n; int a; float w,h;
            cout << "Nombre: "; cin >> n;
            cout << "Edad: "; cin >> a;
            cout << "Peso: "; cin >> w;
            cout << "Altura: "; cin >> h;
            addPatient(&head,createPatient(n,a,w,h));
        } else if(opcion==2){
            printPatients(head);
        } else if(opcion==3){
            loadFromFile(&head,"pacientes.txt");
        }

    }while(opcion!=0);

    return 0;
}
