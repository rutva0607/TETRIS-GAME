#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;
const int WIDTH = 15;   
const int HEIGHT = 25;  
char grid[HEIGHT][WIDTH];
int score = 0;
int highScore = 0;
HANDLE hConsole;


vector<vector<vector<int>>> tetrominoes = {
    // I shape (ID = 1)
    {{1, 1, 1, 1}},
    // O shape (ID = 2)
    {{2, 2}, {2, 2}},
    // T shape (ID = 3)
    {{0, 3, 0}, {3, 3, 3}},
    // S shape (ID = 4)
    {{0, 4, 4}, {4, 4, 0}},
    // Z shape (ID = 5)
    {{5, 5, 0}, {0, 5, 5}},
    // J shape (ID = 6)
    {{6, 0, 0}, {6, 6, 6}},
    // L shape (ID = 7)
    {{0, 0, 7}, {7, 7, 7}}
};

struct Tetromino {
    vector<vector<int>> shape;
    int x, y;
};

Tetromino currentTetromino;
void initializeGrid() {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            grid[i][j] = '.';
}


void setCursorPosition(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, pos);
}


void setColorForCell(char c) {
    switch (c) {
        case '1': 
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case '2': 
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        case '3':
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case '4': 
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case '5':
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case '6': 
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case '7': 
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        default:  
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
    }
}

string showTitleScreen() {
    system("cls");

    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==========================================\n";

    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "|            WELCOME TO TETRIS           |\n";

   
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==========================================\n";

    
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "|   Prepare for the ultimate challenge!  |\n";

    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==========================================\n\n\n";

    
    cout << "Enter your name: ";
    string userName;
    getline(cin, userName);
    if(userName.empty())
        userName = "Player";

    cout << "\nHello, " << userName << "!\n";
    cout << "Press any key to start the game...\n";
    _getch();
    system("cls");
    return userName;
}

void printGrid(const Tetromino &currentTetromino) {
    
    char temp[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            temp[i][j] = grid[i][j];

    
    for (int i = 0; i < currentTetromino.shape.size(); i++) {
        for (int j = 0; j < currentTetromino.shape[i].size(); j++) {
            if (currentTetromino.shape[i][j])
                temp[currentTetromino.y + i][currentTetromino.x + j] = char('0' + currentTetromino.shape[i][j]);
        }
    }

    
    setCursorPosition(0, 0);

 
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\n";

    for (int i = 0; i < HEIGHT; i++) {
        cout << "#";
        for (int j = 0; j < WIDTH; j++) {
            if (temp[i][j] == '.') {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << '.';
            } else {
                setColorForCell(temp[i][j]);
                cout << '#';
            }
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "#\n";
    }
    
    
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\n";

    
    cout << "Score: " << score << "    |    High Score: " << highScore << "\n";

    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "\nControls:\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  Arrow Keys or WASD: Move / Rotate\n"
         << "  Spacebar: Hard Drop\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}


bool canMove(int dx, int dy, const vector<vector<int>> &shape) {
    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j]) {
                int newX = currentTetromino.x + j + dx;
                int newY = currentTetromino.y + i + dy;
                if(newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT)
                    return false;
                if(grid[newY][newX] != '.')
                    return false;
            }
        }
    }
    return true;
}

void rotateTetromino() {
    int rows = currentTetromino.shape.size();
    int cols = currentTetromino.shape[0].size();
    vector<vector<int>> rotated(cols, vector<int>(rows, 0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            rotated[j][rows - 1 - i] = currentTetromino.shape[i][j];
    if (canMove(0, 0, rotated))
        currentTetromino.shape = rotated;
}

void placeTetromino() {
    for (int i = 0; i < currentTetromino.shape.size(); i++)
        for (int j = 0; j < currentTetromino.shape[i].size(); j++)
            if (currentTetromino.shape[i][j])
                grid[currentTetromino.y + i][currentTetromino.x + j] = char('0' + currentTetromino.shape[i][j]);
}

void clearLines() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == '.') {
                full = false;
                break;
            }
        }
        if (full) {
            for (int row = i; row > 0; row--)
                for (int col = 0; col < WIDTH; col++)
                    grid[row][col] = grid[row - 1][col];
            for (int col = 0; col < WIDTH; col++)
                grid[0][col] = '.';
            score += 100;
            i++; 
        }
    }
}

void spawnTetromino() {
    currentTetromino.shape = tetrominoes[rand() % tetrominoes.size()];
    currentTetromino.x = WIDTH / 2 - currentTetromino.shape[0].size() / 2;
    currentTetromino.y = 0;
    while (_kbhit()) _getch();
    
}

void handleInput() {
    while (_kbhit()) {
        int ch = _getch();
        if (ch == 224) {  
            int arrow = _getch();
            if (arrow == 75 && canMove(-1, 0, currentTetromino.shape))
                currentTetromino.x--;
            else if (arrow == 77 && canMove(1, 0, currentTetromino.shape))
                currentTetromino.x++;
            else if (arrow == 80 && canMove(0, 1, currentTetromino.shape))
                currentTetromino.y++;
            else if (arrow == 72)
                rotateTetromino();
        } else {
            if (ch == 'a' || ch == 'A') {
                if (canMove(-1, 0, currentTetromino.shape))
                    currentTetromino.x--;
            } else if (ch == 'd' || ch == 'D') {
                if (canMove(1, 0, currentTetromino.shape))
                    currentTetromino.x++;
            } else if (ch == 's' || ch == 'S') {
                if (canMove(0, 1, currentTetromino.shape))
                    currentTetromino.y++;
            } else if (ch == 'w' || ch == 'W') {
                rotateTetromino();
            } else if (ch == 32) { 
                while (canMove(0, 1, currentTetromino.shape))
                    currentTetromino.y++;
            }
        }
    }
    Sleep(50);
}

int runGameSession() {
    system("cls"); 
    initializeGrid();
    score = 0;
    spawnTetromino();
    if (!canMove(0, 0, currentTetromino.shape)) {
        printGrid(currentTetromino);
        return score;
    }
    DWORD lastFallTime = GetTickCount();
    int fallSpeed = 500; 

    while (true) {
        printGrid(currentTetromino);
        handleInput();
        DWORD now = GetTickCount();
        if (now - lastFallTime >= fallSpeed) {
            if (canMove(0, 1, currentTetromino.shape))
                currentTetromino.y++;
            else {
                placeTetromino();
                clearLines();
                spawnTetromino();
                if (!canMove(0, 0, currentTetromino.shape)) {
                    printGrid(currentTetromino);
                    return score;
                }
            }
            lastFallTime = now;
        }
        Sleep(30);
    }
}

int main() {
    srand((unsigned)time(0));
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    string userName = showTitleScreen();
    bool exitGame = false;
    while (!exitGame) {
        int finalScore = runGameSession();
        if (finalScore > highScore)
            highScore = finalScore;
        
        cout << "\nGame Over, " << userName << "!\n";
        cout << "Your Score: " << finalScore << "\n";
        cout << "High Score: " << highScore << "\n\n";
        cout << "Press [R] to Restart or [X] to Exit.\n";
        
        bool validChoice = false;
        while (!validChoice) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 'R' || ch == 'r')
                    validChoice = true;
                else if (ch == 'X' || ch == 'x') {
                    validChoice = true;
                    exitGame = true;
                }
            }
            Sleep(50);
        }
        system("cls");
    }
    
    system("cls");
    cout << "Thanks for playing TETRIS, " << userName << "!\n";
    cout << "Final High Score: " << highScore << "\n";
    system("pause");
    return 0;
}
