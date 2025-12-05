/* Realice un programa que permita al usuario registrar diez temperaturas y muestre en pantalla cual es la mas baja, 
cual es la mas alta y cuanto da la sumatoria de todas las temperaturas*/
#include<iostream>
using namespace std;
int main(){
int temp[10]; int temp_alta=0; int temp_menor=0; int temp_total=0;

for(int i=0; i<10; i++){
cout<<"Registre las temperaturas en grados celsius: ";
cin>>temp[i];
}


temp_alta = temp[0]; temp_menor = temp[0];
	
for (int j = 1; j < 10; j++) {
        if (temp[j] < temp_menor) {
            temp_menor = temp[j];
        }
        if (temp[j] > temp_alta) {
            temp_alta = temp[j];
        }
    }

cout<<"La temperatura mas alta es: "<<temp_alta<<endl;
cout<<"La temperatura mas baja es: "<<temp_menor<<endl;


	return 0;	
}

