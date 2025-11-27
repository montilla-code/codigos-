#include<iostream>
#include<conio.h>
#include <windows.h>  
using namespace std;

void gotoxy(int x,int y){  
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}  
void bordes1(int x, int y, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(i==0){
                gotoxy(x+j, y+i); cout<<"*";
            }
        }
    }
}
int main(){
    bordes1(5,5, 20);
    
    return 0;
}
