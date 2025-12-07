#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <windows.h>

using namespace std;

enum Direccion { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

struct Posicion {
    int x, y;
    bool operator==(Posicion p) { return x == p.x && y == p.y; }
};

const int ANCHO = 20, ALTO = 15;
vector<Posicion> serpiente;
Direccion dir = DERECHA;
Posicion comida;
int score = 0;
bool juego = true;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ocultarCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 100;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void iniciar() {
    serpiente.clear();
    // Serpiente de 4 segmentos
    serpiente.push_back({10, 7});
    serpiente.push_back({9, 7});
    serpiente.push_back({8, 7});
    serpiente.push_back({7, 7});
    
    dir = DERECHA;
    score = 0;
    
    // Comida aleatoria
    srand(time(NULL));
    do {
        comida = {rand() % ANCHO, rand() % ALTO};
    } while(false); // En realidad aquí verificarías que no esté en la serpiente
}

void dibujarMarco() {
    system("cls");
    
    // Marco
    for(int i = 0; i < ANCHO + 2; i++) cout << "#";
    cout << endl;
    
    for(int y = 0; y < ALTO; y++) {
        cout << "#";
        for(int x = 0; x < ANCHO; x++) {
            Posicion p = {x, y};
            char c = ' ';
            
            if(p == serpiente[0]) c = 'O';
            else {
                bool esCuerpo = false;
                for(int i = 1; i < serpiente.size(); i++) {
                    if(p == serpiente[i]) {
                        c = 'o';
                        esCuerpo = true;
                        break;
                    }
                }
                if(!esCuerpo && p == comida) c = '*';
            }
            
            cout << c;
        }
        cout << "#" << endl;
    }
    
    for(int i = 0; i < ANCHO + 2; i++) cout << "#";
    cout << endl;
    
    cout << "\nScore: " << score << "  Longitud: " << serpiente.size() << endl;
    cout << "Controles: WASD  (La serpiente se mueve sola)" << endl;
}

void mover() {
    Posicion cabeza = serpiente[0];
    
    if(dir == ARRIBA) cabeza.y--;
    else if(dir == ABAJO) cabeza.y++;
    else if(dir == IZQUIERDA) cabeza.x--;
    else cabeza.x++;
    
    // Comer
    if(cabeza == comida) {
        score += 10;
        // Nueva comida
        comida = {rand() % ANCHO, rand() % ALTO};
    } else {
        serpiente.pop_back();
    }
    
    serpiente.insert(serpiente.begin(), cabeza);
}

void input() {
    if(_kbhit()) {
        char tecla = _getch();
        if(tecla == 'w' && dir != ABAJO) dir = ARRIBA;
        else if(tecla == 's' && dir != ARRIBA) dir = ABAJO;
        else if(tecla == 'a' && dir != DERECHA) dir = IZQUIERDA;
        else if(tecla == 'd' && dir != IZQUIERDA) dir = DERECHA;
        else if(tecla == 'q') juego = false;
    }
}

bool colision() {
    Posicion cabeza = serpiente[0];
    
    // Bordes
    if(cabeza.x < 0 || cabeza.x >= ANCHO || cabeza.y < 0 || cabeza.y >= ALTO)
        return true;
    
    // Consigo misma
    for(int i = 1; i < serpiente.size(); i++)
        if(cabeza == serpiente[i]) return true;
    
    return false;
}

int main() {
    ocultarCursor();
    iniciar();
    
    while(juego) {
        dibujarMarco();
        input();  // Solo cambia dirección
        mover();  // Se mueve automáticamente
        
        if(colision()) {
            cout << "\nGAME OVER! Score: " << score << endl;
            cout << "¿Jugar otra vez? (s/n): ";
            char opcion;
            cin >> opcion;
            if(opcion == 's') iniciar();
            else juego = false;
        }
        
        Sleep(200); // Controla la velocidad
    }
    
    return 0;
}
