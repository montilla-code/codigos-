/*realice un programa que permita al usuario registrar 10 temperaturas y muestre en 
pantalla la mas baja, cual es la mas alta, y cuanto da la sumatoria de todas las temperaturas registradas*/
#include<iostream>
#include<string>
using namespace std;

int main(){

int celsius [10];
int celsius_mas_bajo = 0;
int celsius_mas_alto = 0;
int celsius_total = 0;

	for(int i = 0; i < 10 ; i++){
	cout<<"ingrese la temperatura : ";
	cin>>celsius[i];
	}
	
	for(int j = 0; j < 10 ; j++){
		if(celsius_mas_bajo < celsius[j]){
			celsius_mas_bajo = celsius;
		}
		if(celsius_mas_alto > celsius[j]){
		celsius_mas_alto = celsius;
		}
	}
	for(int k = 0; k < 10 ; k++){
		
}



return 0;
}