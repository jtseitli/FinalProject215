// Final Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

const int sizegridCell = 10;
const int gridWidth = 90;
const int gridHeight = 90;

void gridLoad(int grid[gridWidth][gridHeight]) {
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            int cellvalueRandom = (1 & rand());
            if (cellvalueRandom == 0) {
                grid[i][j] = 0;
            }
            else {
                grid[i][j] = 1;
            }
        }
    }
}


int numCellLive(int grid[gridWidth][gridHeight], int x, int y) {
    int num = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int cellnextX = x + i;
            int cellnextY = y + j;
            if (cellnextX >= 0 && cellnextX < gridWidth && cellnextY >= 0 && cellnextY < gridHeight && !(i == 0 && j == 0)) {
                num = num + grid[cellnextX][cellnextY];
            }
        }
    }
    return num;
}

int cellNextAlive(0);

void gridUpdated(int grid[gridWidth][gridHeight]) {
    int gridNew[gridWidth][gridHeight] = { 0 };

    for (int i = 0; i < gridWidth; i++) {
        for (int u = 0; u < gridHeight; u++) {
            int cellnextAlive = numCellLive(grid, i, u);
            if (grid[i][u]) {
                if (cellnextAlive == 2 || cellnextAlive == 3) {
                    gridNew[i][u] = 1;
                }
                else {
                    gridNew[i][u] = 0;
                }
            }
            else {
                if (cellnextAlive == 3) {
                    gridNew[i][u] = 1;
                }
                else {
                    gridNew[i][u] = 0;
                }
            }
        }
    }

    for (int i = 0; i < gridWidth; i++) {
        for (int u = 0; u < gridHeight; u++) {
            grid[i][u] = gridNew[i][u];
        }
    }
}


void gridDisplay(RenderWindow& window, int grid[gridWidth][gridHeight]) {
    RectangleShape pixelStart(Vector2f(sizegridCell, sizegridCell));
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            pixelStart.setPosition(i * sizegridCell, j * sizegridCell);
            if (grid[i][j]) {
                pixelStart.setFillColor(Color::Black);
            }
            else {
                pixelStart.setFillColor(Color::White);
            }
            window.draw(pixelStart);
        }
    }
}



int main() {
    RenderWindow window(VideoMode(gridWidth * sizegridCell, gridHeight * sizegridCell), "Josh's Game of Death");

    int grid[gridHeight][gridHeight] = { 0 };

    gridLoad(grid);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();

            }
        }


        window.clear();
        gridUpdated(grid);
        gridDisplay(window, grid);
        window.display();
    }


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file