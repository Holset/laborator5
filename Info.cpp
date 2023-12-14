/**
 * @file SnakeGame.cpp
 * @brief Implementation of the SnakeGame class
 * 
 * This file contains the implementation of the SnakeGame class, which represents
 * a simple console-based Snake game.
 * 
 * @author Your Name
 * @date 2023
 */

#include "SnakeGame.h"

/**
 * @brief Constructs a SnakeGame object and initializes the game.
 * 
 * This constructor initializes the map, snake, and other game-related variables.
 */
SnakeGame::SnakeGame() : map(20 * 20), food(4), running(true) {
    initMap();
}

/**
 * @brief Runs the SnakeGame, handling the game loop.
 * 
 * This method runs the main game loop, where it waits for user input,
 * updates the game state, and prints the map.
 */
void SnakeGame::run() {
    while (running) {
        if (_kbhit()) {
            changeDirection(_getch());
        }
        update();
        clearScreen();
        printMap();
        Sleep(400);
    }

    cout << "\t\tGame Over!" << endl << "\t\tYour score is: " << food << endl;
    cin.ignore();
}

// ... (other methods)

/**
 * @brief Clears the console screen.
 * 
 * This method clears the console screen for a clean display of the game.
 */
void SnakeGame::clearScreen() {
    system("cls");
}

/**
 * @brief Returns the character representation of a map cell.
 * 
 * This method returns the character representation of a given map cell
 * based on its value (e.g., snake body, wall, or food).
 * 
 * @param cell The MapCell to get the character for.
 * @return The character representation of the map cell.
 */
char SnakeGame::getMapValue(const MapCell& cell) {
    if (cell.value > 0) return 'o';
    switch (cell.value) {
    case -1: return 'X';
    case -2: return 'O';
    default: return ' ';
    }
}

/**
 * @brief Prints the current state of the game map to the console.
 * 
 * This method prints the current state of the game map to the console,
 * displaying the snake, food, and walls.
 */
void SnakeGame::printMap() {
    for (int x = 0; x < mapwidth; ++x) {
        for (int y = 0; y < mapheight; ++y) {
            cout << getMapValue(map[x + y * mapwidth]) << ' ';
        }
        cout << endl;
    }
}

/**
 * @brief Initializes the game map with walls, snake head, and initial food.
 * 
 * This method initializes the game map with walls, places the snake head
 * at the center, and generates the initial food.
 */
void SnakeGame::initMap() {
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[headxpos + headypos * mapwidth].value = 1;

    for (int x = 0; x < mapwidth; ++x) {
        map[x].value = -1;
        map[x + (mapheight - 1) * mapwidth].value = -1;
    }

    for (int y = 0; y < mapheight; y++) {
        map[0 + y * mapwidth].value = -1;
        map[(mapwidth - 1) + y * mapwidth].value = -1;
    }

    generateFood();
}

/**
 * @brief Updates the game state by moving the snake and handling collisions.
 * 
 * This method updates the game state by moving the snake in the current direction,
 * checking for collisions with walls or food, and generating new food if eaten.
 */
void SnakeGame::update() {
    switch (direction) {
    case 0: move(-1, 0);
        break;
    case 1: move(0, 1);
        break;
    case 2: move(1, 0);
        break;
    case 3: move(0, -1);
        break;
    }

    for (int i = 0; i < map.size(); i++) {
        if (map[i].value > 0) map[i].value--;
    }
}

/**
 * @brief Moves the snake head to a new location.
 * 
 * This method moves the snake head to a new location based on the given
 * direction and checks for collisions with food or walls.
 * 
 * @param dx The change in x-coordinate.
 * @param dy The change in y-coordinate.
 */
void SnakeGame::move(int dx, int dy) {
    int newx = headxpos + dx;
    int newy = headypos + dy;

    if (map[newx + newy * mapwidth].value == -2) {
        food++;
        generateFood();
    } else if (map[newx + newy * mapwidth].value != 0) {
        running = false;
    }

    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos * mapwidth].value = food + 1;
}

/**
 * @brief Changes the direction of the snake based on user input.
 * 
 * This method changes the direction of the snake based on the user input.
 * It prevents the snake from moving directly opposite to its current direction.
 * 
 * @param key The key pressed by the user.
 */
void SnakeGame::changeDirection(char key) {
    switch (key) {
    case 'w':
        if (direction != 2) direction = 0;
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 4) direction = 2;
        break;
    case 'a':
        if (direction != 5) direction = 3;
        break;
    }
}

/**
 * @brief Generates new food on the game map.
 * 
 * This method generates new food on the game map at a random location
 * that is not occupied by the snake or walls.
 */
void SnakeGame::generateFood() {
    int x = 0;
    int y = 0;
    do {
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;
    } while (map[x + y * mapwidth].value != 0);

    map[x + y * mapwidth].value = -2;
}
