/*
Realice un programa que permita al usuario registrar
Los precios de un numero N de productos y los ordene de menor a mayor
Y de mayor a menor use el metodo Burbuja.
*/

#include <iostream>
#include<string>
using namespace std;

int main(){
	int N;int aux;int k = 0;
	cout<<"Ingrese la cantidad de productos que desea registrar: ";
	cin>>N;
		int Productos [N];
	for(int i = 0; i < N; i++){
	
		cout<<"Ingrese el precio de los productos: ";
		cin>>Productos[i];	
		}
		
	 for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-1-i; j++) {
            if (Productos[j] > Productos[j+1]) {
                aux = Productos[j];
                Productos[j] = Productos[j+1];
                Productos[j+1] = aux;
            }
        }
    }
	cout<<"Tus precios en orden son: "<<endl;
    for (int k = 0; k < N; k++) {
        cout << Productos[k] << endl;
    }

    return 0;
	}



