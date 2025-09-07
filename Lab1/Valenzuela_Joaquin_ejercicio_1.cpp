#include <iostream>
#include <string>
using namespace std;

struct Patient{
    string name;
    int age;
    float weight;
    float height;
};

int main(){

    Patient patients[3];

    patients[0].name = "Manuel";
    patients[0].age = 32;
    patients[0].weight = 70.5;
    patients[0].height = 1.75;

    patients[1].name = "Ines";
    patients[1].age = 88;
    patients[1].weight = 62.0;
    patients[1].height = 1.60;

    patients[2].name = "Jose";
    patients[2].age = 16;
    patients[2].weight = 55.2;
    patients[2].height = 1.70;

    for(int i=0; i<3; i++){
        cout << "Paciente " << i+1 << endl;
        cout << patients[i].name << endl;
        cout << patients[i].age << " años" << endl;
        cout << patients[i].weight << " kg" << endl;
        cout << patients[i].height << " m" << endl;
        cout << "------" << endl;
    }

    return 0;
}
