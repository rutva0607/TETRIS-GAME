# Tetris Game in C++

## Overview
This is a simple console-based Tetris game written in C++ using the Windows API for rendering. It features a playable grid, multiple tetromino shapes, real-time user input, scoring, and a high score tracking system. The game is played directly in the terminal with smooth graphics using colored tetrominoes.

## Features
- **Fully functional Tetris gameplay**: Move, rotate, and drop tetrominoes.
- **Colored blocks**: Different colors for each shape using Windows console attributes.
- **Score tracking**: Increases as you clear lines.
- **High Score retention**: Keeps track of the highest score achieved in a session.
- **Intuitive controls**: Supports both arrow keys and WASD for movement.
- **Hard drop feature**: Pressing spacebar instantly places the tetromino at the lowest available position.

## Controls
- **Left Arrow / A** → Move tetromino left
- **Right Arrow / D** → Move tetromino right
- **Down Arrow / S** → Move tetromino down faster
- **Up Arrow / W** → Rotate tetromino
- **Spacebar** → Hard drop (instantly places the piece at the lowest point)

## How to Play
1. **Run the executable**: Start the game and enter your name.
2. **Control falling tetrominoes**: Move and rotate them to fit within the playing grid.
3. **Clear lines**: Fill an entire row to remove it and earn points.
4. **Game over**: If tetrominoes stack up to the top, the game ends.
5. **Restart or Exit**: After the game ends, press `R` to restart or `X` to exit.

## Data Structures Used
- **2D Array (`char grid[HEIGHT][WIDTH]`)**: Represents the game board where tetrominoes are placed.
- **Vector of Vectors (`vector<vector<vector<int>>> tetrominoes`)**: Stores different tetromino shapes in a structured format, allowing for easy rotation and retrieval.
- **Struct (`struct Tetromino`)**: Holds the current tetromino's shape and position on the grid, encapsulating relevant data for movement and rotation.
- **Windows API (`HANDLE hConsole`)**: Used for console output manipulation, such as cursor positioning and color changes.
- **Integer Variables (`int score`, `int highScore`)**: Keep track of the player's current score and highest score achieved in a session.
- **Boolean (`bool exitGame`)**: Determines whether the game should continue running or exit.
- **Keyboard Input Handling (`_kbhit()`, `_getch()`)**: Used to detect and process user key presses in real-time.
- **Time Management (`DWORD lastFallTime`)**: Keeps track of the timing for automatic tetromino falling.

## Requirements
- Windows OS (for console functions such as `SetConsoleCursorPosition` and `SetConsoleTextAttribute`)
- C++ Compiler (G++ or MSVC)
- Console-based execution environment

## Installation & Compilation
### Using g++ (MinGW)
```sh
 g++ tetris.cpp -o tetris.exe -std=c++11 -static-libstdc++ -static-libgcc
```
### Using MSVC
```sh
cl tetris.cpp /Fe:tetris.exe
```
### Running the Game
```sh
./tetris.exe
```

## Future Enhancements
- Implement ghost pieces to show where the current tetromino will land.
- Add music and sound effects.
- Store high scores persistently across sessions.
- Implement different difficulty levels with increasing drop speeds.

## Author
- Developed by Our Group
- Feel free to modify and enhance this project!

## License
This project is open-source and available under the MIT License.

