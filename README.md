# Zenless Zone Zero - Hollow Deep Dive Simulation

This project is a C++ simulation of the "Hollow Deep Dive" (HDD) system from the game *Zenless Zone Zero*. It replicates the core grid-based exploration and puzzle mechanics found in the game.

## Game Concepts

### What is a Hollow?
In the world of *Zenless Zone Zero*, **Hollows** are supernatural disasters that appear as expanding black spherical dimensions. They swallow up everything in their vicinity and are filled with a corruptive substance called **Ether**. Inside a Hollow, the laws of physics are distorted, and the environment is chaotic and ever-changing. Those who enter a Hollow without protection risk corruption, turning into mindless monsters known as **Ethereals**. Despite the danger, Hollows are explored for the valuable Ether resources they contain.

### What is a Bangboo?
**Bangboos** are small, rabbit-like intelligent robotic assistants. Originally created to help citizens with daily tasks, they have been adapted for Hollow exploration. In the HDD system, a "Proxy" (the player character) does not physically enter the Hollow's most dangerous depths directly but instead projects their consciousness into a Bangboo. This allows the Proxy to navigate the hazardous environment remotely and guide their team of Agents safely.

### Exploration Mechanics (Hollow Deep Dive)
The **Hollow Deep Dive (HDD)** system is the interface used to explore Hollows. In this simulation, the gameplay focuses on the "TV Mode" or grid-based exploration aspect:

*   **Grid-Based Movement**: The Hollow is represented as a grid of tiles (often visualized as CRT television screens in the original game). The player controls a Bangboo to move across this grid one step at a time.
*   **Fog of War**: Much of the Hollow is unknown. As the Bangboo moves, adjacent tiles are revealed, simulating the exploration of the distorted dimension.
*   **Collecting Items**: The grid contains various resources and items (like Gear Coins or Ether droplets) that the player must collect to progress or achieve high scores.
*   **Avoiding Obstacles**: The Hollow is treacherous. Players must navigate around obstacles, traps, and blocked paths. Some tiles may trigger events or battles (simulated or abstractly represented).
*   **Puzzles**: The layout often forms a maze or puzzle, requiring strategic movement to reach the exit or objective without running out of resources or health.

## Project Structure

```
├── data/
│   └── level.txt
├── include/
│   ├── blockEntity.h
│   ├── entity.h
│   ├── fairy.h
│   ├── hollow.h
│   ├── movableEntity.h
│   └── utils.h
├── src/
│   ├── blockEntity.cpp
│   ├── hollow.cpp
│   ├── main.cpp
│   └── movableEntity.cpp
├── tests/
│   └── main_test.cpp
├── public_cases/
├── .gitignore
├── Makefile
└── README.md
```

*   `src/`: Contains the source code (`.cpp` files) for the game logic and entities.
    *   `main.cpp`: The entry point of the game. It initializes the game using `Fairy` and starts the game loop.
    *   `hollow.cpp`: Implements the `Hollow` class, which manages the game grid, entity registration, and movement logic.
    *   `blockEntity.cpp`: Implements the logic for static block entities like Walls, Doors, Switches, and Portals.
    *   `movableEntity.cpp`: Implements the logic for movable entities like the BangBoo (player), Boxes, and Stones.
*   `include/`: Contains the header files (`.h`) defining the classes and structures.
    *   `hollow.h`: Defines the `Hollow` class, representing the game world/grid.
    *   `entity.h`: Defines the base `Entity` class for all game objects.
    *   `movableEntity.h`: Defines `MovableEntity` and its subclasses (`BangBoo`, `Box`, `Stone`).
    *   `blockEntity.h`: Defines `BlockEntity` and its subclasses (`Wall`, `Door`, `Switch`, `Goal`, `Portal`, etc.).
    *   `fairy.h`: Defines the `Fairy` class, which acts as a helper to load levels and manage the game session (simulating the AI assistant "Fairy" from the game).
    *   `utils.h`: Defines utility structures like `Location` and enums like `Direction`.
*   `data/`: Contains level data files.
    *   `level.txt`: The default level configuration file defining the grid layout and entity positions.
*   `public_cases/`: Contains test cases and expected outputs for validation.
*   `tests/`: Contains unit tests for the project.
    *   `main_test.cpp`: The entry point for running unit tests.

## How to Build and Run

You can build the project using the provided `Makefile` (if you have `make` installed), the included `make.bat` script (for Windows), or manually using `g++`.

### Prerequisites
*   A C++ compiler (supporting C++11 or later, e.g., g++)
*   (Optional) Make

### Option 1: Using Make (Recommended for Linux/Mac/WSL)
To build the main game executable:
```bash
make game
```

To build the test suite:
```bash
make game_test
```

To clean up build artifacts:
```bash
make clean
```

### Option 2: Using make.bat (For Windows)
If you are on Windows and do not have `make` installed, you can use the provided batch script which emulates the make commands.
In PowerShell or Command Prompt:

To build the game:
```powershell
.\make game
```

To build the test suite:
```powershell
.\make game_test
```

To clean:
```powershell
.\make clean
```

### Option 3: Manual Compilation (g++)
If you prefer to compile manually:

**Build the Game:**
```bash
g++ -std=c++11 -Iinclude src/main.cpp src/hollow.cpp src/blockEntity.cpp src/movableEntity.cpp -o game
```

**Build the Test Suite:**
```bash
g++ -std=c++11 -Iinclude tests/main_test.cpp src/hollow.cpp src/blockEntity.cpp src/movableEntity.cpp -o game_test
```

### Running the Game
After building, you can run the game using:
```bash
./game
# or on Windows
.\game.exe
```
