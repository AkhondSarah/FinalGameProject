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

/*
* Tetris class:
* The original code was developed by Fam Trinliin
* his YouTube channel (see the following URL):  https://www.youtube.com/watch?v=zH_omFPqMO4&list=PLB_ibvUSN7mzUffhiay5g5GUHyJRO4DYr.
* we use the concepts of electronic game  and competetive game here
*/

// TETRIS Game - Source

class Tetris {
public:
	// Size of the screen
	static const int WIDTH = 480;
	static const int HEIGHT = 480;
	//Positions (GRID)
	static const int MAXLIN = 20;
	static const int MAXCOL = 20;
	//Picture representation 
	static const int DIM = 4;
	//Number of blocks
	static const int NFIG = 18;
	//Number of color
	static const int NCOLOR = 16;
	//Pixel size
	static const int PIX = 18;
	//Array of blocks
	const int BLOCKDIMX = 2;
	const int BLOCKDIMY = 4;

private:
	// List of figures
	const int figures[NFIG][DIM] =
	{
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
		1,
		2,
		2,
		3,
		3,
		3,
		3,
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
		4,

	};
	struct Block {
		int x, y;
	}
	posX[DIM] = { 0, 0, 0, 0 },
		posY[DIM] = { 0, 0, 0, 0 };

public:
	inline bool nextMovement(int space[MAXLIN][MAXCOL]) {
		for (int i = 0; i < DIM; i++)
			if (posX[i].x < 0 || posX[i].x >= MAXCOL || posX[i].y >= MAXLIN) {
				return false;
			}
			else if (space[posX[i].y][posX[i].x]) {
				return false;
			}
		return true;
	};
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
			if (count < MAXCOL) {
				k--;
			}
		}
	}
	void horizontalMovement(int space[MAXLIN][MAXCOL], int dx) {
		for (int i = 0; i < DIM; i++) {
			posX[i] = posY[i];
			posX[i].x += dx;
		}
		if (nextMovement(space)) {
			for (int i = 0; i < DIM; i++) {
				posX[i] = posY[i];
			}
		}
	}
	void rotationalMovement(int space[MAXLIN][MAXCOL]) {
		Block p = posX[1]; //Central position
		for (int i = 0; i < DIM; i++) {
			int x = posX[i].y - p.y;
			int y = posX[i].x - p.x;
			posX[i].x = p.x - x;
			posX[i].y = p.y + y;
		}
		if (nextMovement(space)) {
			for (int i = 0; i < DIM; i++) {
				posX[i] = posY[i];
			}
		}
	}
	void downMovement() {
		for (int i = 0; i < DIM; i++) {
			posX[i].y += 1;
			posY[i].y += 1;
		}
	}
	int createBlock(int space[MAXLIN][MAXCOL], int colorNum) {
		int currentBlock;
		// Updates all positions to create a new block
		for (int i = 0; i < DIM; i++) {
			space[posX[i].y][posX[i].x] = colorNum;
		}
		currentBlock = rand() % NFIG;
		//for (int i = 0; i < DIM; i++) {
		//	posX[i].x = figures[currentBlock][i] % 2;
		//	posX[i].y = figures[currentBlock][i] % 2;
		//}
		return currentBlock;
	}
	void updateBlock(int currentBlock, int dx) {
		for (int i = 0; i < DIM; i++) {
			posX[i].x = figures[currentBlock][i];
			posX[i].x += dx;
			posX[i].y = figures[currentBlock][i];
		}
	}
	inline int play(long curTimeout, int curTurn, Player player, int limTimeout) {

		// Game Model
		int model[MAXLIN][MAXCOL] = { 0 };
		// Timeout
		Clock clock;
		// Default delay
		float delay = 0.3f / curTimeout;// Accelerate the game according to the current turn
		// Boolean variables for execution
		bool rotate = false;
		bool stop = false;
		int totpoints = player.getPoints();
		string playername = player.getName();
		bool isFinished = false;
		bool endGame = false;
		float timer = 0; 
		int dx;
		int colorNum = 1;
		string title;
		Text text;
		
		
		//Window definition
		RenderWindow window(VideoMode(WIDTH, HEIGHT), "Tetris");
		// Texture to be used
		Texture t1, t2;
		t1.loadFromFile("tiles.png"); // Tiles tocompose blocks
		t2.loadFromFile("tetris1.png"); //Background
		Sprite space(t1), background(t2);
		//Main loop: While the window is not closed and there is possibility to continue playing 
		while (window.isOpen() && !isFinished && !endGame) {
			//Start and updates the timer
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
		}
		//Event evalution
		Event e;
		while (window.pollEvent(e)) {
			//TODO: Check the events that user can do (movemoents)
			//TODO: Include an option to "freeze": when space bar is pressed
			//TODO:Also include an option when "Escape" ends the game
		} // While: Keyboard event 
		//TODO: Invoke functions that comes from user actions
		//Clock update 
		if (timer > delay && !stop) {
			//TODO: Action independent from user
			//Movements from block
			if (nextMovement(model)) {
				//TODO: Create the block (createBlock)
				//TODO: Generate the new color (use rand ove NCOLOR)
				// TODO: Calculate the variation dx
				// TODO: Update the block (updateBlock)
				// TODO: Update the total of points (from currentBlock)	
			}
			// TODO: Update the timeout
			// TODO: Check if you can end the game according to the timeout
			// TODO: Reinitialize the timer.
		}
		// Update data if game is not finished
		if (!endGame) {
			// TODO: Check if the last level is complete (checksFill).
			// Update from movement (and clock)
			dx = 0;
			rotate = 0;
			delay = 0.3f / curTurn; // The delay will be shorter when number of turns increases
			// Cleaning the window
			window.clear(Color::Black);
			window.draw(background);
			// Refresh of all blocks
			for (int i = 0; i < MAXLIN; i++){
				for (int j = 0; j < MAXCOL; j++) {
					if (model[i][j] == 0) {
						continue;
					}
					// Tetris renderization
					space.setTextureRect(IntRect(model[i][j] * PIX, 0, PIX, PIX));
					space.setPosition((float)j * PIX, (float)i * PIX);
					space.move(28, 31); // positional adjustment
					window.draw(space);
				}
			}
			// New block renderization
			for (int i = 0; i < DIM; i++) {
				space.setTextureRect(IntRect(colorNum * PIX, 0, PIX, PIX));
				space.setPosition((float)posX[i].x * PIX, (float)posX[i].y * PIX);
				space.move(28, 31); // positional adjustment
				window.draw(space);
			}
			// TODO: Evaluate the next movement (nextMovement).
			// Update message in the game
			title = "Turn: " + to_string(curTurn) + " - Player: " + playername +
				", Points: " + to_string(totpoints) + " - Timeout: " + to_string((long)curTimeout);
			text.setString(title);
			window.draw(text);
			window.display();
		} // If not end
		//return value
		return totpoints;
	} // Main loop
	
	
};