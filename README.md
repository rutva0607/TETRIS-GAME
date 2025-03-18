# Tetris Game🟥🟥🟥🟥

## Created By
- **Rutva Mehta**
- **Khush Hingrajiya**
- **Manthan Kanetiya**
- **Vikas Bhabhor**

## Overview
This is a simple console-based Tetris game written in C++ using the Windows API for rendering. It features a playable grid, multiple tetromino shapes, real-time user input, scoring, and a high score tracking system. The game is played directly in the terminal with smooth graphics using colored tetrominoes.

## Features
- **Fully functional Tetris gameplay**: Move, rotate, and drop tetrominoes.
- **Colored blocks**: Different colors for each shape using Windows console attributes.
- **Score tracking**: Increases as you clear lines.
- **High Score retention**: Keeps track of the highest score achieved in a session.
- **Intuitive controls**: Supports both arrow keys and WASD for movement.
- **Hard drop feature**: Pressing spacebar instantly places the tetromino at the lowest available position.
- **Next piece preview**: Displays the upcoming tetromino to plan ahead.
- **Hold piece feature**: Allows swapping the current tetromino with a saved one.
- **Adjustable speed levels**: Increases difficulty as the player progresses.
- **Pause and Resume**: Players can pause the game and resume later.

## Controls
- **Left Arrow / A** → Move tetromino left
- **Right Arrow / D** → Move tetromino right
- **Down Arrow / S** → Move tetromino down faster
- **Up Arrow / W** → Rotate tetromino
- **Spacebar** → Hard drop (instantly places the piece at the lowest point)
- **P** → Pause/Resume game
- **C** → Hold current piece and swap it later

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
- **Queue (`queue<Tetromino> nextPieces`)**: Stores upcoming tetrominoes for preview and better gameplay experience.
- **Set (`set<int> clearedRows`)**: Keeps track of rows that need to be removed after a tetromino is placed.
- **Stack (`stack<Tetromino> holdPiece`)**: Allows the player to store a tetromino and swap it later.
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

## Known Issues
- **Performance lag on large consoles**: The game may experience frame rate drops on high-resolution terminals due to excessive console output operations.
- **Keyboard input delay**: Rapid key presses might not always register due to the way `_kbhit()` and `_getch()` are used.
- **Incomplete line clearing animation**: When multiple lines are cleared at once, the visual update might appear abrupt.
- **No persistent high scores**: High scores reset after the game is closed.
- **Limited OS compatibility**: The game relies on Windows API functions, making it incompatible with Linux or macOS without modifications.
- **No smooth animations**: Tetromino movements can appear choppy since the game updates the entire console screen at once.
- **Holding feature limitations**: Players cannot hold and swap the same piece multiple times in quick succession.

## Future Enhancements
- Implement ghost pieces to show where the current tetromino will land.
- Add music and sound effects.
- Store high scores persistently across sessions.
- Implement different difficulty levels with increasing drop speeds.
- Improve rendering for smoother animations.
- Add multiplayer support for competitive play.
- Optimize performance for better response time.



## License
This project is open-source and free to use for educational and personal projects.

Enjoy the game!
