/*

	Realice un programa que permita al usuario guardar 10 nombres
	y los ordene alfabeticamente. use el metodo de insercion

*/

#include <iostream>
#include<string>
using namespace std;

int main(){
	string nombres[10];
    string aux;
    int pos;
	for(int i = 0; i < 10; i++){
	
		cout<<"Ingrese el nombre: ";
		cin>>nombres[i];	
		}
		
	 for (int i = 1; i < 10; i++) {
	 	pos = i;
	 	aux = nombres[i];
        while((pos > 0) && (nombres[pos-1]> aux)){
        	nombres[pos] = nombres[pos-1];
        	pos--;
		}nombres[pos] = aux;
    }
    
	cout<<"Tus nombres ordenados alfabeticamente son:  "<<endl;
    for (int k = 0; k < 10; k++) {
        cout << nombres[k] << endl;
    }

    return 0;
	}



