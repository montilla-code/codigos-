#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <string>

using namespace std;

// Funciones varias y utilidades
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 100;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

string intToString(int n) {
    if (n == 0) return "0";
    string s = "";
    while (n > 0) {
        char c = '0' + (n % 10);
        s = c + s;
        n /= 10;
    }
    return s;
}

const int ANCHO = 40;
const int ALTO = 20;

// Clasificacion de jugadores
string ganadores[100];
int conteoGanadores = 0;
string nombreJugadorActual;

// Base de la serpiente
int serpienteX[200];
int serpienteY[200];
int longitudSerpiente;
int direccion; // Variable para controlar la direccion de la serpiente

// Variables para la comida y niveles
int comidaX, comidaY;
int nivel;
int frutasComidas;
int velocidadJuego;
bool juegoTerminado;
bool juegoGanado;

// Variables para los obstaculos
int obstaculoX[50];
int obstaculoY[50];
int conteoObstaculos;

// Para dibujar el YOULOSE y YOUWIN
void dibujarGranCaracter(char c, int startX, int startY, int size, int color) {
    setColor(color);
    
    // Ya todo lo que viene es para armarlo, el tamaño, etc
    int grid[5][5] = {0};
    if(c >= 'a' && c <= 'z') c -= 32;

    switch(c) {
        case 'Y':
            grid[0][0]=1; grid[0][4]=1;
            grid[1][0]=1; grid[1][4]=1;
            grid[2][1]=1; grid[2][2]=1; grid[2][3]=1;
            grid[3][2]=1; grid[4][2]=1;
            break;
        case 'O':
        case '0':
            for(int i=0;i<5;i++) { grid[i][0]=1; grid[i][4]=1; }
            grid[0][1]=1; grid[0][2]=1; grid[0][3]=1;
            grid[4][1]=1; grid[4][2]=1; grid[4][3]=1;
            break;
        case 'U':
            for(int i=0;i<5;i++) { grid[i][0]=1; grid[i][4]=1; }
            grid[4][1]=1; grid[4][2]=1; grid[4][3]=1;
            break;
        case 'L':
            for(int i=0;i<5;i++) grid[i][0]=1;
            grid[4][1]=1; grid[4][2]=1; grid[4][3]=1; grid[4][4]=1;
            break;
        case 'S':
        case '5':
            for(int i=0;i<5;i++) { grid[0][i]=1; grid[2][i]=1; grid[4][i]=1; }
            grid[1][0]=1; grid[3][4]=1;
            break;
        case 'E':
            for(int i=0;i<5;i++) { grid[0][i]=1; grid[2][i]=1; grid[4][i]=1; }
            for(int i=0;i<5;i++) grid[i][0]=1;
            break;
        case '!':
            for(int i=0;i<3;i++) grid[i][2]=1;
            grid[4][2]=1;
            break;
        case 'W':
             for(int i=0;i<5;i++) { grid[i][0]=1; grid[i][4]=1; }
             grid[3][1]=1; grid[3][3]=1; grid[2][2]=1;
             break;
        case 'I':
        case '1':
             for(int i=0;i<5;i++) grid[i][2]=1;
             break;
        case 'N':
             for(int i=0;i<5;i++) { grid[i][0]=1; grid[i][4]=1; }
             grid[1][1]=1; grid[2][2]=1; grid[3][3]=1;
             break;
        case 'V':
             grid[0][0]=1; grid[0][4]=1;
             grid[1][0]=1; grid[1][4]=1;
             grid[2][0]=1; grid[2][4]=1;
             grid[3][1]=1; grid[3][3]=1;
             grid[4][2]=1;
             break;
        case '2':
             for(int i=0;i<5;i++) { grid[0][i]=1; grid[2][i]=1; grid[4][i]=1; }
             grid[1][4]=1; grid[3][0]=1;
             break;
        case '3':
             for(int i=0;i<5;i++) { grid[0][i]=1; grid[2][i]=1; grid[4][i]=1; }
             grid[1][4]=1; grid[3][4]=1;
             break;
        case '4':
             grid[0][0]=1; grid[1][0]=1; grid[2][0]=1;
             grid[2][1]=1; grid[2][2]=1; grid[2][3]=1; grid[2][4]=1;
             grid[0][4]=1; grid[1][4]=1; grid[3][4]=1; grid[4][4]=1;
             break;
        case '6':
             for(int i=0;i<5;i++) { grid[0][i]=1; grid[2][i]=1; grid[4][i]=1; }
             grid[1][0]=1; grid[3][0]=1; grid[3][4]=1;
             break;
        case '7':
             for(int i=0;i<5;i++) grid[0][i]=1;
             grid[1][4]=1; grid[2][3]=1; grid[3][2]=1; grid[4][1]=1;
             break;
        case '8':
             for(int i=0;i<5;i++) { grid[0][i]=1; grid[2][i]=1; grid[4][i]=1; }
             grid[1][0]=1; grid[1][4]=1;
             grid[3][0]=1; grid[3][4]=1;
             break;
        case '9':
             for(int i=0;i<5;i++) { grid[0][i]=1; grid[2][i]=1; grid[4][i]=1; }
             grid[1][0]=1; grid[1][4]=1; grid[3][4]=1;
             break;
        case 'P':
             for(int i=0;i<5;i++) grid[i][0]=1;
             grid[0][1]=1; grid[0][2]=1; grid[0][3]=1;
             grid[1][4]=1; 
             grid[2][1]=1; grid[2][2]=1; grid[2][3]=1;
             break;
        case 'R':
             for(int i=0;i<5;i++) grid[i][0]=1;
             grid[0][1]=1; grid[0][2]=1; grid[0][3]=1; grid[0][4]=1;
             grid[1][4]=1; 
             grid[2][1]=1; grid[2][2]=1; grid[2][3]=1; grid[2][4]=1;
             grid[3][2]=1; grid[3][3]=1;
             grid[4][4]=1;
             break;
        case 'D':
             for(int i=0;i<5;i++) grid[i][0]=1;
             grid[0][1]=1; grid[0][2]=1; grid[0][3]=1;
             grid[1][4]=1; grid[2][4]=1; grid[3][4]=1;
             grid[4][1]=1; grid[4][2]=1; grid[4][3]=1;
             break;
        case 'T':
             for(int i=0;i<5;i++) grid[i][2]=1;
             for(int i=0;i<5;i++) grid[0][i]=1;
             break;
        case 'G':
             for(int i=0;i<5;i++) { grid[0][i]=1; grid[4][i]=1; }
             grid[1][0]=1; grid[2][0]=1; grid[3][0]=1;
             grid[2][3]=1; grid[2][4]=1;
             grid[3][4]=1;
             break;
        case 'A':
             for(int i=0;i<5;i++) { grid[i][0]=1; grid[i][4]=1; }
             grid[0][1]=1; grid[0][2]=1; grid[0][3]=1;
             grid[2][1]=1; grid[2][2]=1; grid[2][3]=1;
             break;
        default: 
             // Como predeterminado una caja o cuadrado pues
             for(int i=0;i<5;i++) for(int j=0;j<5;j++) grid[i][j]=1;
             break;
    }

    // Las letras va escalando
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            // El mapa
            int origI = (i * 5) / size;
            int origJ = (j * 5) / size;
            
            if(grid[origI][origJ] == 1) {
                gotoxy(startX + j, startY + i);
                cout << (char)219;
            }
        }
    }
}

void dibujarCadena(string text, int x, int y, int size, int color) {
    int cursorX = x;
    for(int i = 0; i < text.length(); i++) {
        dibujarGranCaracter(text[i], cursorX, y, size, color);
        cursorX += size + 2; // Para que haya espacio entre las letras
    }
}

// Aqui empiezan las animaciones, de que crezca entre intervalos y cambie de color entre rojo y blanco
void animacionPerder() {
    
    for(int s = 5; s <= 8; s++) {
        system("cls");
        int col = (s % 2 == 0) ? 12 : 15; // Aqui va alternando
        
        // Aqui sale el YOULOSE si obviamente pierdes
        int totalWidth = 9 * (s + 2);
        int startX = (80 - totalWidth) / 2; // Assuming 80 width console
        if(startX < 0) startX = 5;
        int startY = 5;

        dibujarCadena("YOULOSE!", startX, startY, s, col);
        Sleep(500);
    }
    Sleep(1000);
}

void animacionNivel(int lvl) {
    system("cls");
    string txt = "NIVEL" + intToString(lvl);
    // Este va intercalando entre colores, no crece
    
    int len = txt.length();
    int totalWidth = len * (5 + 2);
    int startX = (80 - totalWidth) / 2;
    int startY = 5;

    for(int i=0; i<6; i++) {
        int col = (i % 2 == 0) ? 10 : 15; // Los colorcitos
        gotoxy(startX, startY); // Dibuja otra vez en la misma posicion
        dibujarCadena(txt, startX, startY, 5, col);
        Sleep(500);
    }
}

void animacionGanar() {
    system("cls");
    // La animacion cuando ganas los 5 niveles
    int s = 6;
    int totalWidth = 8 * (s + 2);
    int startX = (80 - totalWidth) / 2;
    
    dibujarCadena("YOUWIN!", startX, 5, s, 14); // Yellow
    Sleep(3000);
}

// Aqui empiezan los obstaculos, la comida, etc
bool siObstaculo(int x, int y) {
    for(int i=0; i<conteoObstaculos; i++) {
        if(obstaculoX[i] == x && obstaculoY[i] == y) return true;
    }
    return false;
}

bool siSerpiente(int x, int y) {
    for(int i=0; i<longitudSerpiente; i++) {
        if(serpienteX[i] == x && serpienteY[i] == y) return true;
    }
    return false;
}

void generarComida() {
    bool valido = false;
    while(!valido) {
        comidaX = rand() % ANCHO;
        comidaY = rand() % ALTO;
        valido = true;
        if(siSerpiente(comidaX, comidaY)) valido = false;
        if(siObstaculo(comidaX, comidaY)) valido = false;
    }
}

void generarObstaculos(int count) {
    conteoObstaculos = 0;
    while(conteoObstaculos < count) {
        int rX = rand() % ANCHO;
        int rY = rand() % ALTO;
        
        bool conflicto = false;
        if(siSerpiente(rX, rY)) conflicto = true;
        // Revisa la comida
        if(rX == comidaX && rY == comidaY) conflicto = true; 
        
        if(rX > 10 && rX < 30 && rY > 5 && rY < 15 && nivel == 1) conflicto = true; // Safe zone for lvl 1

        if(!conflicto) {
            obstaculoX[conteoObstaculos] = rX;
            obstaculoY[conteoObstaculos] = rY;
            conteoObstaculos++;
        }
    }
}

void configurarNivel(int lvl) {
    // Resetea la serpiente en el centro
    longitudSerpiente = 1; // Esto es para que la serpiente vaya creciendo a medida que come
    /* La longitud con la que empieza la serpiente, 
	4 para que en los niveles mas alto no se haga tan complicado por la velocidad*/
    longitudSerpiente = 4;
    serpienteX[0] = ANCHO/2; serpienteY[0] = ALTO/2;
    serpienteX[1] = ANCHO/2-1; serpienteY[1] = ALTO/2;
    serpienteX[2] = ANCHO/2-2; serpienteY[2] = ALTO/2;
    
    direccion = 3; 

    /*Aqui empieza la dificultad
     La velocidad mientras mas baja es mas dificil. Lvl 1=150, Lvl 5=50.
    y los obstaculos: Lvl 1: 3 y Lvl 5: 15. Si tiene mala suerte se pueden juntar mal
	si no, quedan lejos */
    velocidadJuego = 150 - (lvl * 25); 
    if(velocidadJuego < 40) velocidadJuego = 40;
    
    int obsToSpawn = lvl * 3; 

    generarComida(); 
    generarObstaculos(obsToSpawn);
    
    frutasComidas = 0;
}

void dibujarJuego() {
    gotoxy(0,0);
    setColor(7); // Color blanco
    
    // El borde de arriba y colores
    for(int i=0; i<ANCHO+2; i++) cout << "#";
    cout << endl;
    
    for(int i=0; i<ALTO; i++) {
        cout << "#"; 
        for(int j=0; j<ANCHO; j++) {
            if(i == serpienteY[0] && j == serpienteX[0]) {
                setColor(10); cout << "O"; // La cabeza de la serpiente
            } else if(i == comidaY && j == comidaX) {
                setColor(12); cout << "*"; // La comida
            } else if(siSerpiente(j, i)) {
                setColor(2); cout << "o"; // El cuerpo, en minuscula para que se diferencie
            } else if(siObstaculo(j, i)) {
                setColor(8); cout << "X"; // Los obstaculos
            } else {
                cout << " ";
            }
            setColor(7);
        }
        cout << "#" << endl; 
    }
    
    // El borde de abajo
    for(int i=0; i<ANCHO+2; i++) cout << "#";
    cout << endl;
    
    cout << "Jugador: " << nombreJugadorActual << " | Nivel: " << nivel << "/5" << " | Meta: " << frutasComidas << "/5" << endl;
}

void entrada() {
    if(_kbhit()) {
        char k = _getch();
        if(k == 'w' && direccion != 1) direccion = 0;
        if(k == 's' && direccion != 0) direccion = 1;
        if(k == 'a' && direccion != 3) direccion = 2;
        if(k == 'd' && direccion != 2) direccion = 3;
    }
}

void logica() {
    // El funcionamiento de la cola
    for(int i = longitudSerpiente-1; i > 0; i--) {
        serpienteX[i] = serpienteX[i-1];
        serpienteY[i] = serpienteY[i-1];
    }
    
    // El movimiento de la cabeza
    if(direccion == 0) serpienteY[0]--;
    if(direccion == 1) serpienteY[0]++;
    if(direccion == 2) serpienteX[0]--;
    if(direccion == 3) serpienteX[0]++;
    
    // Si es que colisiona con un muro
    if(serpienteX[0] < 0 || serpienteX[0] >= ANCHO || serpienteY[0] < 0 || serpienteY[0] >= ALTO) {
        juegoTerminado = true;
    }
    // Si es que colisiona con si misma
    for(int i=1; i<longitudSerpiente; i++) {
        if(serpienteX[0] == serpienteX[i] && serpienteY[0] == serpienteY[i]) juegoTerminado = true;
    }
    // Y si es que colisiona con obstaculos
    if(siObstaculo(serpienteX[0], serpienteY[0])) juegoTerminado = true;
    
    // Si se come la fruta
    if(serpienteX[0] == comidaX && serpienteY[0] == comidaY) {
        longitudSerpiente++;
        frutasComidas++;
        if(frutasComidas >= 5) {
            // Cuando se termina el nivel
            if(nivel == 5) {
                juegoGanado = true;
                juegoTerminado = true; // Termina el bucle
            } else {
                nivel++;
                animacionNivel(nivel);
                configurarNivel(nivel);
            }
        } else {
            generarComida();
        }
    }
}

// La tabla de clasificacion
void ordenarYMostrarGanadores() {
    system("cls");
    setColor(7);
    cout << "=== CLASIFICACION ===" << endl;
    cout << "1. Por orden alfabetico" << endl;
    cout << "2. Por longitud" << endl;
    cout << "Opcion: ";
    int mode; cin >> mode;
    
    string tempWins[100];
    for(int i=0; i<conteoGanadores; i++) tempWins[i] = ganadores[i];
    
    // Bubble Sort
    for(int i=0; i<conteoGanadores-1; i++) {
        for(int j=0; j<conteoGanadores-i-1; j++) {
            bool swapNeeded = false;
            if(mode == 1) {
                if(tempWins[j] > tempWins[j+1]) swapNeeded = true;
            } else {
                // By length
                if(tempWins[j].length() < tempWins[j+1].length()) swapNeeded = true; // Descending
                else if(tempWins[j].length() == tempWins[j+1].length() && tempWins[j] > tempWins[j+1]) swapNeeded = true; // Alpha fallback
            }
            
            if(swapNeeded) {
                string temp = tempWins[j];
                tempWins[j] = tempWins[j+1];
                tempWins[j+1] = temp;
            }
        }
    }
    
    cout << "\n--- GANADORES ---\n";
    for(int i=0; i<conteoGanadores; i++) {
        cout << (i+1) << ". " << tempWins[i] << endl; 
    }
    cout << "\nPresiona cualquier tecla..." << endl;
    _getch();
}

int main() {
    srand(time(NULL));
    hideCursor();
    
    bool aplicacionCorriendo = true;
    while(aplicacionCorriendo) {
        system("cls");
        cout << "--- Snake 5 Niveles ---" << endl;
        cout << "Ingresa tu nombre: ";
        cin >> nombreJugadorActual;
        
        nivel = 1;
        juegoTerminado = false;
        juegoGanado = false;
        
        configurarNivel(nivel);
        
        while(!juegoTerminado) {
            dibujarJuego();
            entrada();
            logica();
            Sleep(velocidadJuego);
        }
        
        if(juegoGanado) {
            animacionGanar();
            ganadores[conteoGanadores] = nombreJugadorActual;
            conteoGanadores++;
            ordenarYMostrarGanadores();
        } else {
            animacionPerder();
        }
        
        system("cls");
        cout << "Jugar otra vez? (y/n): ";
        char c; cin >> c;
        if(c != 'y' && c != 'Y') aplicacionCorriendo = false;
    }
    
    return 0;
}


