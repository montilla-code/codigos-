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

// Función para leer el carácter en la posición actual
char leerChar(int x, int y){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    CHAR_INFO ci;
    COORD bufferSize = {1,1};
    COORD bufferCoord = {0,0};
    SMALL_RECT readRegion = {x,y,x,y};
    ReadConsoleOutput(hcon, &ci, bufferSize, bufferCoord, &readRegion);
    return ci.Char.AsciiChar;
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
void bordes2(int x, int y, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(i==n-1){
                gotoxy(x+j, y+i); cout<<"*";
            }
        }
    }
}
void bordetotal(int x, int y, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(j==n-1){
                gotoxy(x+j, y+i); cout<<"*";
            }
        }
    }
}
void bordes4(int x, int y, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(j==0){
                gotoxy(x+j, y+i); cout<<"*";
            }
        }
    }
}
void pared1(int x, int y, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(j==n/2 && i>=n/2){
                gotoxy(x+j, y+i); cout<<"*";
            }
        }
    }
}
void pared2(int x, int y, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(i ==n/2 && j<=n/2){
                gotoxy(x+j, y+i); cout<<"*";
            }
        }
    }
}
void pared3(int x, int y, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(i ==0 && j>=n/2){
                gotoxy(x+j, y+i); cout<<"*";
            }
        }
    }
}
void pared4(int x, int y, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(j ==n/2 && i<=n/2){
                gotoxy(x+j, y+i); cout<<"*";
            }
        }
    }
}

int main(){
    bordes1(5,5, 20);
    bordes2(5,5, 20);
    bordes4(5,5, 20);
    pared1(3,5, 20);
    pared2(5, 2, 20);
    pared3(4, 9, 20);
    pared4(11, 5, 5);
    bordetotal(5,5, 20);

    // Personaje que se mueve
    int x = 21, y = 6; // posición inicial
    gotoxy(x,y); cout<<"O";

    // Meta
    int mx = 6, my = 23; 
    gotoxy(mx,my); cout<<"M";

    char tecla;
    while(true){
        tecla = getch();
        gotoxy(x,y); cout<<" "; // borra el anterior

        if(tecla == 72) y--;        // flecha arriba
        else if(tecla == 80) y++;   // flecha abajo
        else if(tecla == 75) x--;   // flecha izquierda
        else if(tecla == 77) x++;   // flecha derecha
        else if(tecla == 27) break; // ESC para salir

        // Verificar colisión con paredes
        char c = leerChar(x,y);
        if(c == '*'){
            system("cls");
            cout<<"\n\n\tPELDITE\n\n";
            break;
        }

        // Verificar si llegó a la meta
        if(x == mx && y == my){
            system("cls");
            cout<<"\n\n\t¡GANASTE!\n\n";
            break;
        }

        gotoxy(x,y); cout<<"O"; // dibuja en nueva posición
    }

    return 0;
}


