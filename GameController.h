#pragma once

//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <time.h>
#include <vector>
#include <iostream>
#include <string>
#include <limits.h>
#include "Player.h"
#include "Tetris.h"

using namespace sf;
using namespace std;


class GameController {

public:

	enum GAMETYPE {ELECTRONIC, COMPETETIVE, MIXED};

	// Game constants
	static const long MAXTIMEOUT = 30;
	static const long MAXTURNS = 3;
	static const long MAXPLAYERS = 3;
	// Sentinel to test each turn by until this value (0 = no limit)
	static const int LIMITEDTIME = 10;

private:

	//Players
	vector<Player> playersList;

	//Game timeout
	long timeout = 0;

	//Number of turns
	int numTurns = 0;

public:

	/*
	* Sets timeout
	*/

	inline GameController setTimeout(long newTimeout) {
		timeout = newTimeout;
		return *this;
	}

	/*
	* Sets numTurns
	*/
	inline GameController setNumTurns(int newNumTurns) {
		numTurns = newNumTurns;
		return *this;
	}

	/*
	* Sets playerList
	*/
	inline GameController setPlayerList(vector<Player> newPlayersList) {
		playersList = newPlayersList;
		return *this;
	}

	/*
	* Gets timeout
	*/
    inline long getTimeout() {
		return timeout;
	}

	/*
	* Gets numTurns
	*/
	inline int getNumTurns() {
		return numTurns;
	}

	
	/*
	* Gets playerList
	*/
	inline vector<Player> getPlayersList() {
		return playersList;
	}
	/*
	* Creates playerList
	* - Param: Number of players
	*/
	inline vector<Player> createPlayersList(int nPlayers) {
		vector<Player> list;

		// starts the player list (directly)
		for (int i = 0; i < nPlayers; i++) {
			Player player;
			player = Player("Player_" + to_string(i));
			list.push_back(player);

		}
		return list;
	}
	/*
	* openGame: Prints the screen for Game
	* - Return:
	*  Kind of game to play
	* 
	*/
	inline int openGame() {
		// Main screen : Title and dimension
		//neil you're gonn ahve to work out this part

		string gametitle = "Tetris Results"; 
		RenderWindow window(VideoMode(Tetris::WIDTH, Tetris::HEIGHT), gametitle); 
		Texture t1; 
		t1.loadFromFile("tetris2.png"); 
		Sprite background(t1);
		// Basic loop; renderization
		int returnValue = -1;
		while (window.isOpen() && returnValue == -1) {
			Event e;
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed) {
					returnValue = 0;
					window.close();
				}
				//Test Keyboard
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboards::Num0) {
						returnValue = 0;
						break;
					}// if
					else if (e.key.code == Keyboard::Num1) {
						returnValue = 1;
					}//else if
					else if (e.key.code == Keyboard::Num2) {
						//DONT KNOW WHAT TO DO
					}
				}//if(keyboard
			}//while
		}//while
		window.clear();
		window.draw(background); 
		window.display();
	}//opengame()
	/*
	* tetrisElectronics: implementation for one-single playerof Tetrisexecution
	* - Return:
	*  Kind of game to play
	*
	*/
	inline void tetrisElectronic() {
		//INCOMPLETE
		
		int curTurn;
		Player player;
		int currentPoints;
		int timer;
		int currPlayer = 0;
		Tetris game = new Tetris();
		while (timer <= timeout) {
			// Update the current timeout
			long curTimeout = getTimeout();
			// Execute the Tetris, returning the points for this player
			currentPoints = game.play(player, curTimeout, curTurn, GameController::LIMITEDTIME);
			// TODO: Later, update the timeout and set it (chose the better strategy to update
			setTimeout(curTimeout);
			// TODO: Remember to update also the player...
			playersList[currPlayer].setPoints();
			
		}
	}
	
		inline void tetrisCompetitive() {
			int curTurn;
			Player player;
			int currentPoints;
			int timer;
			while (curTurn <= numTurns) {
				// Initialization of players
				int currPlayer = 0;
				while (currPlayer < numPlayers) {
					player = list.at(currPlayer);
					// Execute the Tetris, returning the points for this player
					currentPoints = game.play(player, curTimeout, curTurn, GameController::LIMITEDTIME);
					// Updates the points
					list.at(currPlayer).setPoints(currentPoints);
					currPlayer++;
				} 
				// Turn update
				setNumTurns(curTurn);
				curTurn++;}
		}
};



