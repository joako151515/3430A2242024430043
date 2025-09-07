#include <iostream>
#include <string>
using namespace std;

struct Patient{
    string name;
    int age;
    float weight;
    float height;
    Patient *next;
};

Patient* createPatient(string n, int a, float w, float h){
    Patient *nuevo = new Patient;
    nuevo->name = n;
    nuevo->age = a;
    nuevo->weight = w;
    nuevo->height = h;
    nuevo->next = NULL;
    return nuevo;
}

void addPatient(Patient **head, Patient *nuevo){
    if(*head==NULL){
        *head = nuevo;
    } else {
        Patient *aux = *head;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = nuevo;
    }
}

void printPatients(Patient *head){
    Patient *aux = head;
    while(aux != NULL){
        cout << "Nombre: " << aux->name << endl;
        cout << "Edad: " << aux->age << " años" << endl;
        cout << "Peso: " << aux->weight << " kg" << endl;
        cout << "Altura: " << aux->height << " m" << endl;
        cout << "=========" << endl;
        aux = aux->next;
    }
}

void freePatients(Patient *head){
    Patient *aux = head;
    while(aux != NULL){
        Patient *sig = aux->next;
        delete aux;
        aux = sig;
    }
}

int main(){
    Patient *head = NULL;

    addPatient(&head, createPatient("Manuel", 32, 70.5, 1.75));
    addPatient(&head, createPatient("Ines", 88, 62.0, 1.60));
    addPatient(&head, createPatient("Jose", 16, 55.2, 1.70));

    printPatients(head);

    freePatients(head);

    return 0;
}
