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

float imc(Patient *p){
    return p->weight/(p->height*p->height);
}

void stats(Patient *head){
    int sumaEdad=0;
    float sumaPeso=0;
    int cont=0;
    Patient *aux=head;
    while(aux!=NULL){
        cout << aux->name << " tiene IMC= " << imc(aux) << endl;
        sumaEdad+=aux->age;
        sumaPeso+=aux->weight;
        cont++;
        aux=aux->next;
    }
    if(cont>0){
        cout << "Promedio edad: " << (float)sumaEdad/cont << " años" << endl;
        cout << "Promedio peso: " << (sumaPeso/cont) << " kg" << endl;
    }
}

int main(){
    Patient *head=NULL;
    addPatient(&head,createPatient("Manuel",32,70.5,1.75));
    addPatient(&head,createPatient("Ines",88,62.0,1.60));
    addPatient(&head,createPatient("Jose",16,55.2,1.70));

    stats(head);

    return 0;
}
