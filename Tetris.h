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

// TETRIS gMAE - Source

class Tetris {

public:
	// SIze of the screen
	static const int WIDTH = 480;
	static const int HEIGHT = 480;

	//POSITIONS (GRID)
	static const int MAXLIN = 20;
	static const int MAXCOL = 20;

	//PICTURE REPRESENTAIION
	static const int DIM = 4;
	// NUMBER OF GEOMETRIC BLOACKS
	static const int NFIG = 18;
	//NUMBER OF COLOURS
	static const int NCOLOR = 16;
	//sIZE OF THE PIXEL
	static const int PIX = 18;

	//ARRAY OF POSSIBLE BLOCKA
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
		0,0,2,3,// 3- mobcls- L shaped
		0,0,2,4,//3 block vertical
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
			if (posX[i].x < 0 || posX[i].x >= MAXCOL ||
				posX[i].y >= MAXLIN){ }
				// TODO: Complete the return here
			else if (space[posX[i].y][posX[i].x]){}
				// TODO: Complete the return here
				// TODO: Complete the return here

	};

	void checksFill(int space[MAXLIN][MAXCOL]) {
		int k = MAXLIN - 1;
		for (int i = MAXLIN - 1; i > 0; i--) {
			int count = 0;
			for (int j = 0; j < MAXCOL; j++) {
				if (space[i][j])
					// TODO: Update the count here
					space[k][j] = space[i][j];
			}
			if (count < MAXCOL) {

			}
				// TODO: Update k here
		}
	}
	void horizontalMovement(int space[MAXLIN][MAXCOL], int dx) {
		for (int i = 0; i < DIM; i++) {
			// TODO: Update posX and posY
		}
		if (nextMovement(space))
			for (int i = 0; i < DIM; i++)
				// TODO: Update posX
			{ }
	}

	void rotationalMovement(int space[MAXLIN][MAXCOL]) {
		Block p = posX[1]; //Central position
		for (int i = 0; i < DIM; i++) {
			// TODO: Update posX
		}
		if (nextMovement(space))
			for (int i = 0; i < DIM; i++)
				// TODO: Update pos
			{ }
	}
	void downMovement() {
		for (int i = 0; i < DIM; i++) {
			// TODO: Update posX and posY
		}
	}
	int createBlock(int space[MAXLIN][MAXCOL], int colorNum) {
		int currentBlock;
		// Updates all positions to create a new block
		for (int i = 0; i < DIM; i++) {
			// TODO: Updates the color of space[posy]posx]
		}
		// TODO: Creates a new currentBlock randomly
		return currentBlock;
	}
	void updateBlock(int currentBlock, int dx) {
		for (int i = 0; i < DIM; i++) {
			// TODO: Updates the posXusing the figures in the position given by currentBlock
		}
	}
	inline int play( long currentTimeout, int currentTurn, Player player, int limTimeout) {

		// Game Model
		int model[MAXLIN][MAXCOL] = { 0 };
		// Timeout
		Clock clock;
		// Default delay
		float delay = 0.3f / currentTimeout;// Accelerate the game according to the current turn
	 // Boolean variables for execution
		bool rotate = false;
		bool stop = false;
		// TODO: Create variables to use information to be shown. Ex: points from
		return 1;
	}

};