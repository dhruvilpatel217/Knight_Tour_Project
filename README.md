# ♞ Knight's Tour – Console Game in C++

> An interactive terminal-based puzzle game built using C++, where a knight traverses the chessboard visiting each square exactly once without repetition.

---

## 🎯 Project Objective

The goal is to simulate and play the classic **Knight’s Tour** problem, allowing users to manually navigate a knight across an `N x N` chessboard. The system ensures move validity, real-time board rendering, and win/loss state detection.

---

## 🧠 Key Features

- ♞ **Algorithmic Puzzle Logic**: Implements knight pathfinding using Warnsdorff’s heuristic.
- 📏 **Dynamic Board Sizes**: Supports board sizes ranging from `5x5` to `10x10`.
- 🎮 **Interactive Console Gameplay**: Real-time visual feedback and keyboard-controlled movement.
- 🎲 **Randomized Starting Points**: Each game starts from a valid random position on the board.
- 🖌️ **Terminal UI with Color**: Uses ANSI escape sequences to display styled boards and instructions.
- 📈 **Endgame Visualizer**: Optionally reveals the full computed knight tour after gameplay.

---

## 🛠️ Technologies Used

- **Object-Oriented Programming (OOP)**: Modular class-based structure used to encapsulate gameplay logic and game state management.
- **Data Structures & Algorithms (DSA)**: Implements Warnsdorff’s Rule, a greedy heuristic for pathfinding; uses recursion alternatives and efficient lookups.
- **Terminal Control**: Uses ANSI escape sequences for colored output, grid drawing, and cursor positioning across platforms.
- **Non-blocking Input Handling**: Real-time keyboard input captured via `_getch()` for interactive gameplay without pausing the game loop.
- **Randomized Game Initialization**: Selects a valid starting position randomly from precomputed tours, ensuring variability each playthrough.

---

## 📦 File Structure

```
KnightTourGame/
├── KnightTourFinalCode(main).cpp     # Entry point: handles design, rules, and game lifecycle
├── knight_tour_helper.cpp            # Implements Warnsdorff’s heuristic and precomputes valid paths
├── knight_tour_helper.h              # Declares helper functions and global variables
├── KnightTourPlayGame.cpp            # Manages interactive gameplay, movement, and board drawing
├── KnightTourPlayGame.h              # Exposes play and print functions for the game
└── README.md                         # Project overview and instructions (this file)
```
---

## 🚀 Future Enhancements

- 🌐 Web-based version 
- 🖼️ GUI-based board with drag-and-drop moves
- 📱 Mobile adaptation with touch controls
- 🧠 AI auto-solver mode vs. player mode
- 📊 Enhanced move tracking and statistics

---

## 📥 Getting Started

### 1. Clone the Repository
```
git clone https://github.com/yourusername/KnightTourGame.git
cd KnightTourGame
```
### 2. Compile the Code
```
g++ main.cpp knight_tour_helper.cpp KnightTourPlayGame.cpp -o knighttour
```
### 3. Run the Game
```
./knighttour
```
