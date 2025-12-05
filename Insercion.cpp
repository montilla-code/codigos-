#include <iostream>
using namespace std;

int main() {
    int pos = 0;
    int numeros[] = {8, 3, 4, 1, 6};
    int aux = 0;

    for (int i = 0; i < 5; i++) {
        pos = i;
        aux = numeros[i];
        while ((pos > 0) && (numeros[pos - 1] > aux)) {
            numeros[pos] = numeros[pos - 1];
            pos--;
        }
        numeros[pos] = aux;
    }

    // Mostrar el arreglo ordenado
    for (int i = 0; i < 5; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    return 0;
}
