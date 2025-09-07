#include <iostream>
#include <string>
using namespace std;

struct Patient {
    string name;
    int age;
    float weight;
    float height;
};

int main(){

    Patient p1;
    p1.name = "Manuel";
    p1.age = 32;
    p1.weight = 70.5;
    p1.height = 1.75;

    Patient p2;
    p2.name = "Ines";
    p2.age = 88;
    p2.weight = 62.0;
    p2.height = 1.60;

    Patient p3;
    p3.name = "Jose";
    p3.age = 16;
    p3.weight = 55.2;
    p3.height = 1.70;

    cout << "Paciente 1:" << endl;
    cout << p1.name << endl;
    cout << p1.age << " años" << endl;
    cout << p1.weight << " kg" << endl;
    cout << p1.height << " m" << endl;
    cout << endl;

    cout << "Paciente 2:" << endl;
    cout << p2.name << endl;
    cout << p2.age << " años" << endl;
    cout << p2.weight << " kg" << endl;
    cout << p2.height << " m" << endl;
    cout << endl;

    cout << "Paciente 3:" << endl;
    cout << p3.name << endl;
    cout << p3.age << " años" << endl;
    cout << p3.weight << " kg" << endl;
    cout << p3.height << " m" << endl;

    return 0;
}
