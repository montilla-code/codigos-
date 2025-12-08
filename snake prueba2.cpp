#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <string>

using namespace std;

// --- UTILS ---
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

const int WIDTH = 40;
const int HEIGHT = 20;

// Player/Leaderboard
string winners[100];
int winnersCount = 0;
string currentPlayerName;

// Snake
int snakeX[200];
int snakeY[200];
int snakeLength;
int dir; // 0=UP, 1=DOWN, 2=LEFT, 3=RIGHT

// Food/Level
int foodX, foodY;
int level;
int fruitsEaten;
int gameSpeed;
bool gameOver;
bool gameWin;

// Obstacles
int obsX[50];
int obsY[50];
int obsCount;

// Draws a 5x5 representation of a character, scaled to 'size'
void drawBigChar(char c, int startX, int startY, int size, int color) {
    setColor(color);
    
    // We define the 5x5 grid for each supported character
    // 1 means block, 0 means space
    int grid[5][5] = {0};

    // Uppercase conversion if needed (basic)
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
        default: 
             // Box as default
             for(int i=0;i<5;i++) for(int j=0;j<5;j++) grid[i][j]=1;
             break;
    }

    // Drawing with scaling
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            // Map current scaled pixel (i, j) to original 5x5 grid (origI, origJ)
            int origI = (i * 5) / size;
            int origJ = (j * 5) / size;
            
            if(grid[origI][origJ] == 1) {
                gotoxy(startX + j, startY + i);
                cout << (char)219;
            }
        }
    }
}

void drawString(string text, int x, int y, int size, int color) {
    int cursorX = x;
    for(int i = 0; i < text.length(); i++) {
        drawBigChar(text[i], cursorX, y, size, color);
        cursorX += size + 2; // Spacing between letters
    }
}

// --- ANIMATIONS ---
void animLose() {
    // Grow from n=5 to n=8 in 2 seconds (3 steps: 5,6,7,8 -> 4 frames)
    // 2000ms / 4 = 500ms per frame
    // 4 colors alternated: Red(12), White(15)
    
    for(int s = 5; s <= 8; s++) {
        system("cls");
        int col = (s % 2 == 0) ? 12 : 15; // Alternating
        
        // Improve centering roughly
        // String "YOU LOSE!": 9 chars
        // Width = 9 * (s + 2) roughly
        int totalWidth = 9 * (s + 2);
        int startX = (80 - totalWidth) / 2; // Assuming 80 width console
        if(startX < 0) startX = 5;
        int startY = 5;

        drawString("YOU LOSE!", startX, startY, s, col);
        Sleep(500);
    }
    Sleep(1000);
}

void animLevel(int lvl) {
    system("cls");
    string txt = "NIVEL " + intToString(lvl);
    // n=5, 3 seconds, interval? Implicitly maybe blink?
    // "intercalate between green and white... for 3 seconds"
    // Let's blink 6 times (500ms each)
    
    int len = txt.length();
    int totalWidth = len * (5 + 2);
    int startX = (80 - totalWidth) / 2;
    int startY = 5;

    for(int i=0; i<6; i++) {
        int col = (i % 2 == 0) ? 10 : 15; // Green(10), White(15)
        gotoxy(startX, startY); // Redraw at same pos
        drawString(txt, startX, startY, 5, col);
        Sleep(500);
    }
}

void animWin() {
    system("cls");
    // "Final Win" - maybe special?
    // "You Win!"
    int s = 6;
    int totalWidth = 8 * (s + 2);
    int startX = (80 - totalWidth) / 2;
    
    drawString("YOU WIN!", startX, 5, s, 14); // Yellow
    Sleep(3000);
}

// --- LOGIC ---
bool isObstacle(int x, int y) {
    for(int i=0; i<obsCount; i++) {
        if(obsX[i] == x && obsY[i] == y) return true;
    }
    return false;
}

bool isSnake(int x, int y) {
    for(int i=0; i<snakeLength; i++) {
        if(snakeX[i] == x && snakeY[i] == y) return true;
    }
    return false;
}

void spawnFood() {
    bool valid = false;
    while(!valid) {
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        valid = true;
        if(isSnake(foodX, foodY)) valid = false;
        if(isObstacle(foodX, foodY)) valid = false;
    }
}

void spawnObstacles(int count) {
    obsCount = 0;
    while(obsCount < count) {
        int rX = rand() % WIDTH;
        int rY = rand() % HEIGHT;
        
        bool conflict = false;
        if(isSnake(rX, rY)) conflict = true;
        // Check food (though food spawns after? Safe to check)
        if(rX == foodX && rY == foodY) conflict = true; 
        
        // Don't spawn too close to center start?
        if(rX > 10 && rX < 30 && rY > 5 && rY < 15 && level == 1) conflict = true; // Safe zone for lvl 1

        if(!conflict) {
            obsX[obsCount] = rX;
            obsY[obsCount] = rY;
            obsCount++;
        }
    }
}

void setupLevel(int lvl) {
    // Reset Snake to center
    snakeLength = 1; // "grow in a character each time it reaches the goal" -> implied starts small?
    // "Small snake" usually 3. Let's start with 3.
    snakeLength = 3;
    snakeX[0] = WIDTH/2; snakeY[0] = HEIGHT/2;
    snakeX[1] = WIDTH/2-1; snakeY[1] = HEIGHT/2;
    snakeX[2] = WIDTH/2-2; snakeY[2] = HEIGHT/2;
    
    dir = 3; // Right

    // Difficulty
    // Speed: Lower is faster. Lvl 1=150, Lvl 5=50.
    // Obstacles: Lvl 1: 3, ... Lvl 5: 15
    gameSpeed = 160 - (lvl * 25); 
    if(gameSpeed < 40) gameSpeed = 40;
    
    int obsToSpawn = lvl * 3; 

    spawnFood(); // Food first
    spawnObstacles(obsToSpawn);
    
    fruitsEaten = 0;
}

void drawGame() {
    gotoxy(0,0);
    setColor(7); // White
    
    // Top Border
    for(int i=0; i<WIDTH+2; i++) cout << "#";
    cout << endl;
    
    for(int i=0; i<HEIGHT; i++) {
        cout << "#"; // Left
        for(int j=0; j<WIDTH; j++) {
            if(i == snakeY[0] && j == snakeX[0]) {
                setColor(10); cout << "O"; // Head
            } else if(i == foodY && j == foodX) {
                setColor(12); cout << "*"; // Food
            } else if(isSnake(j, i)) {
                setColor(2); cout << "o"; // Body
            } else if(isObstacle(j, i)) {
                setColor(8); cout << "X"; // Obstacle
            } else {
                cout << " ";
            }
            setColor(7);
        }
        cout << "#" << endl; // Right
    }
    
    // Bottom Border
    for(int i=0; i<WIDTH+2; i++) cout << "#";
    cout << endl;
    
    cout << "Jugador: " << currentPlayerName << " | Nivel: " << level << "/5" << " | Meta: " << fruitsEaten << "/5" << endl;
}

void input() {
    if(_kbhit()) {
        char k = _getch();
        if(k == 'w' && dir != 1) dir = 0;
        if(k == 's' && dir != 0) dir = 1;
        if(k == 'a' && dir != 3) dir = 2;
        if(k == 'd' && dir != 2) dir = 3;
    }
}

void logic() {
    // Tail follow
    for(int i = snakeLength-1; i > 0; i--) {
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }
    
    // Move Head
    if(dir == 0) snakeY[0]--;
    if(dir == 1) snakeY[0]++;
    if(dir == 2) snakeX[0]--;
    if(dir == 3) snakeX[0]++;
    
    // Collision Wall
    if(snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
        gameOver = true;
    }
    // Collision Self
    for(int i=1; i<snakeLength; i++) {
        if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) gameOver = true;
    }
    // Collision Obstacle
    if(isObstacle(snakeX[0], snakeY[0])) gameOver = true;
    
    // Eat Food
    if(snakeX[0] == foodX && snakeY[0] == foodY) {
        snakeLength++;
        fruitsEaten++;
        if(fruitsEaten >= 5) {
            // Level Complete
            if(level == 5) {
                gameWin = true;
                gameOver = true; // Stop loop
            } else {
                level++;
                animLevel(level);
                setupLevel(level);
            }
        } else {
            spawnFood();
        }
    }
}

// --- LEADERBOARD ---
void sortAndShowWinners() {
    system("cls");
    setColor(7);
    cout << "=== CLASIFICACION ===" << endl;
    cout << "1. Por orden alfabetico" << endl;
    cout << "2. Por longitud" << endl;
    cout << "Opcion: ";
    int mode; cin >> mode;
    
    string tempWins[100];
    for(int i=0; i<winnersCount; i++) tempWins[i] = winners[i];
    
    // Bubble Sort
    for(int i=0; i<winnersCount-1; i++) {
        for(int j=0; j<winnersCount-i-1; j++) {
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
    for(int i=0; i<winnersCount; i++) {
        cout << (i+1) << ". " << tempWins[i] << endl; 
    }
    cout << "\nPresiona cualquier tecla..." << endl;
    _getch();
}

int main() {
    srand(time(NULL));
    hideCursor();
    
    bool appRunning = true;
    while(appRunning) {
        system("cls");
        cout << "--- Snake 5 Niveles ---" << endl;
        cout << "Ingresa tu nombre: ";
        cin >> currentPlayerName;
        
        level = 1;
        gameOver = false;
        gameWin = false;
        
        setupLevel(level);
        
        while(!gameOver) {
            drawGame();
            input();
            logic();
            Sleep(gameSpeed);
        }
        
        if(gameWin) {
            animWin();
            winners[winnersCount] = currentPlayerName;
            winnersCount++;
            sortAndShowWinners();
        } else {
            animLose();
        }
        
        system("cls");
        cout << "Jugar otra vez? (y/n): ";
        char c; cin >> c;
        if(c != 'y' && c != 'Y') appRunning = false;
    }
    
    return 0;
}

