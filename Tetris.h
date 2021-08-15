#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>
#include <string>
#include <limits.h>
#include "Player.h"
#include <time.h>
using namespace sf;
using namespace std;

/*Tetris class :
	*The original code was developed by Fam Trinliin
	* his YouTube channel(see the following URL) : https ://www.youtube.com/watch?v=zH_omFPqMO4&list=PLB_ibvUSN7mzUffhiay5g5GUHyJRO4DYr.
	*we use the concepts of electronic gameand competetive game here
*/
class Tetris {

public:
	//Size of the screen
	static const int WIDTH = 480;
	static const int HEIGHT = 480;
	//Positions (GRID)
	static const int MAXLIN = 20;
	static const int MAXCOL = 20;
	//Picture representation
	static const int DIM = 4;
	// Number of blocks
	static const int NFIG = 18;
	static const int NCOLOR = 16;
	// Pixel size
	static const int PIX = 18;
	// Array of blocks
	const int BLOCKDIMX = 2;
	const int BLOCKDIMY = 4;
	int dx = 0;

	


private:
	const int figures[NFIG][DIM] = {
		0,0,0,0, // A single block
		0,0,1,1, // 2 block side by side
		0,0,2,2, // 2 blocks vertical
		0,0,1,3, // 3 bloacks-2 blocks side by sdie a block below the secodn one it
		0,0,2,3, // 3- mobcls- L shaped
		0,0,2,4, //3 block vertical
		1,1,0,2, //3 blocks 1,0,2
		2,3,4,5, // 4 blocks
		2,4,5,7, // 4-s kind of block shape
		3,5,4,6, // 4- opposite of s block shape
		3,5,4,7, // 4-E shape without the up and bottom line (10)
		2,3,5,7, // 4-upside down L
		3,5,7,6, // 4- l shaped
		1,3,5,7, // 4-a vertical line of 4 block
		2,4,6,7, // 4-L shaped  opposite
		1,2,4,6, // 4 blocks
		1,2,5,7, // 4 blocks
		7,4,2,0 // 4 blcoks(18)
	};
	// Points per block
	const int points[NFIG] = {
		// Define the points for each block.
		// Ex: 1 (in the case of 0,0,0,0) ...
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		2,
		2,
		3,
		3,
		3,
		3,
		1,
		3
	};
	// The block
	struct Block {
		int x, y;
	}
	posX[DIM] = { 0, 0, 0, 0 },
	posY[DIM] = { 0, 0, 0, 0 };

	inline bool nextMovement(int space[MAXLIN][MAXCOL]) {
		for (int i = 0; i < DIM; i++)
			if (posX[i].x < 0 || posX[i].x >= MAXCOL || posX[i].y >= MAXLIN) {
				return true;
			}
			else if (space[posX[i].y][posX[i].x]) {
				return true;
			}
		return false;
	}
	void checksFill(int space[MAXLIN][MAXCOL]) {
		int k = MAXLIN - 1;
		for (int i = MAXLIN - 1; i > 0; i--) {
			int count = 0;
			for (int j = 0; j < MAXCOL; j++) {
				if (space[i][j]) {
					count++;
				}
				space[k][j] = space[i][j];
			}
			if (count < MAXCOL)
				k--;
		}
	}
	void horizontalMovement(int space[MAXLIN][MAXCOL], int dx) {
		for (int i = 0; i < DIM; i++) {
			// TODO: Update posX and posY
			posY[i] = posX[i];
			posX[i].x += dx;
		}
		if (nextMovement(space))
			for (int i = 0; i < DIM; i++)
				// TODO: Update posX
				posX[i] = posY[i];
	}
	void rotationalMovement(int space[MAXLIN][MAXCOL]) {
		Block p = posX[1]; // Central position
		for (int i = 0; i < DIM; i++) {
			//update
			int x = posX[i].y - p.y;
			int y = posX[i].x - p.x;
			posX[i].x = p.x - x;
			posX[i].y = p.y + y;
		}
		if (nextMovement(space))
			for (int i = 0; i < DIM; i++)
				posX[i] = posY[i];
	}
	void downMovement() {
		for (int i = 0; i < DIM; i++) {
			posX[i].y += 1;
		}
	}
	int createBlock(int space[MAXLIN][MAXCOL], int colorNum) {
		int currentBlock;
		int poX, poY;
		// Updates all positions to create a new block
		for (int i = 0; i < DIM; i++) {
			poY = posY[i].y;
			poX = posY[i].x;
			space[poY][poX] = colorNum;

		}
		currentBlock = rand() % NFIG;
		return currentBlock;
	}
	void updateBlock(int currentBlock, int dx) {
		for (int i = 0; i < DIM; i++) {
			int poX, poY;

			for (int i = 0; i < DIM; i++) {
				poX = figures[currentBlock][i] % 2 + dx;
				poY = figures[currentBlock][i] / 2;
				posX[i].x = poX;
				posX[i].y = poY;
			}
		}
	}
public:
	inline int play(float& currentTimeout, int currentTurn, Player player, int limTimeout) {
		// Game Model
		int model[MAXLIN][MAXCOL] = { 0 };
		// Timeout
		Clock clock;
		// Default delay
		float delay = 0.3f / currentTurn; // Accelerate the game according to the current turn
		// Boolean variables for execution
		bool rotate = false;
		bool stop = false;
		bool isFinished = false;
		bool endGame = false;
		float timer = 0;
		int totpoints = 1;
		int dx = 0;
		int colorNum = 1;
		int currentBlock = 0;
		string title = "Tetris - " + player.getName() + " Turn: " + to_string(currentTurn);
		Text text;

		// Window definition
		RenderWindow window(VideoMode(WIDTH, HEIGHT), title);
		// Texture to be used
		Texture t1, t2;
		t1.loadFromFile("tiles.png"); // Tiles to compose blocks
		t2.loadFromFile("tetris1.png"); // Background
		Sprite space(t1), background(t2);

		while (window.isOpen() && !isFinished && !endGame) {
			// Start and updates the timer
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			// Event evaluation
			Event e;
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed) {
					window.close();
				}
				// Test keyboard
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboard::Up) {
						rotate = true;;
						break;
					}
					else if (e.key.code == Keyboard::Down) {
						delay = 0.05f / currentTurn;
						stop = false;
						break;
					}
					else if (e.key.code == Keyboard::Left) {
						dx = -1;
						break;
					}
					else if (e.key.code == Keyboard::Right) {
						dx = 1;
						break;
					}

					else if (e.key.code == Keyboard::Space) {
						stop = !stop;
						break;
					}
					// Esc key
					else if (e.key.code == Keyboard::Escape) {
						isFinished = true;
						for (int i = 0; i < DIM; i++) {
							posY[i].y = 0;
							posX[i].x = 0;
							posY[i].x = 0;
							posX[i].y = 0;
						}
						break;
					}
				}
			} // While: Keyboard event

			//movements horizontal
			horizontalMovement(model, dx);
			//Rotational
			if (rotate)
				rotationalMovement(model);

			// Clock update
			if (timer > delay && !stop) {
				downMovement();
				if (nextMovement(model)) {
					currentBlock = createBlock(model, colorNum);
					colorNum = rand() % NCOLOR + 1;
					dx = 0;
					updateBlock(currentBlock, dx);
					totpoints += points[currentBlock];
				}

				currentTimeout += timer;
				cout << currentTimeout << endl;
				if (currentTimeout > limTimeout) {
					endGame = true;
					for (int i = 0; i < DIM; i++) {
						posX[i].x = 0;
						posX[i].y = 0;
						posY[i].x = 0;
						posY[i].y = 0;
					}

				}
				//set timer = 0
				timer = 0;

			}

			// Update data if game is not finished
			if (!endGame) {
				checksFill(model);
				// Update from movement (and clock)
				dx = 0;
				rotate = 0;
				delay = 0.3f / currentTurn; // The delay will be shorter when number of turns increases
				// Cleaning the window
				window.clear(Color::Black);
				window.draw(background);
				// Refresh of all blocks
				for (int i = 0; i < MAXLIN; i++)
					for (int j = 0; j < MAXCOL; j++) {
						if (model[i][j] == 0)
							continue;
						// Tetris renderization
						space.setTextureRect(IntRect(model[i][j] * PIX, 0, PIX, PIX));
						space.setPosition((float)j * PIX, (float)i * PIX);
						space.move(28, 31); // positional adjustment
						window.draw(space);
					}
				// New block renderization
				for (int i = 0; i < DIM; i++) {
					space.setTextureRect(IntRect(colorNum * PIX, 0, PIX, PIX));
					space.setPosition((float)posX[i].x * PIX, (float)posX[i].y * PIX);
				
					space.move(28, 31); // positional adjustment
					window.draw(space);
				}
	
				// Update message in the game
				title = "Turn: " + to_string(currentTurn) + " - Player: " + player.getName() +
					", Points: " + to_string(totpoints) + " - Timeout: " + to_string((long)currentTimeout);
				text.setString(title);
				window.draw(text);
				window.display();
			} // If not end
		} // Main loop
		 // Return value
		return totpoints;
	} // play funtion
};