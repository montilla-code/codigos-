#include<iostream>
/*realice un programa que permita al usuario registrar cedulas y le de la posibilidad de 
saber si hay alguna cedula repetida. El usuario debe decir que cedula se debe buscar*/
#include<string>
using namespace std;

int main(){
	
	int Ci [10];
	int CiB = 0;
	int CiR = 0;	
	for(int i = 0; i < 10 ; i++){
	cout<<"ingrese su numero de Cedula : ";
	cin>>Ci[i];
	}
	
	cout<<"que cedula estas buscando : ";
	cin>>CiB;
	

for(int j = 0; j < 10; j++){
	if(Ci[j]==CiB){
		CiR = CiR + 1;
	}
	
}
	cout<<"la cedula se repite : "<<CiR<<" veces"<<endl;


	return 0;
}