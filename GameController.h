#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
private:
	//Players
	vector<Player> playersList;
	//Game timeout
	long timeout = 0;
	//Number of turns
	int numTurns = 0;

	//RenderWindow* windowPtr;
	//string gametitle = "Tetris Game";
	//RenderWindow window;
public:
	enum GAMETYPE {ELECTRONIC, COMPETETIVE, MIXED};
	Font font;
	// Game constants
	static const long MAXTIMEOUT = 30;
	static const long MAXTURNS = 3;
	static const long MAXPLAYERS = 3;
	// Sentinel to test each turn by until this value (0 = no limit)
	static const int LIMITEDTIME = 10;
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
	*/
	inline int openGame() {
		// Main screen : Title and dimension
		string gametitle = "Tetris Game"; 
		RenderWindow window(VideoMode(Tetris::WIDTH, Tetris::HEIGHT), gametitle); 
		//window(VideoMode(Tetris::WIDTH, Tetris::HEIGHT), gametitle);
		//windowPtr = &window;
		Texture t1; 
		t1.loadFromFile("tetris0.png"); //currently png is in x64-Debug folder
		Sprite background;
		background.setTexture(t1);
		//window.draw(background);
		//window.display();
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
					if (e.key.code == Keyboard::Num0) {
						returnValue = 0;
						break;
					}// if
					else if (e.key.code == Keyboard::Num1) {
						returnValue = 1;
						break;
					}//else if
					else if (e.key.code == Keyboard::Num2) {
						returnValue = 2;
						break;
					}
					else if (e.key.code == Keyboard::Num3) {
						returnValue = 3;
						break;
					}
					else if (e.key.code == Keyboard::Escape) {
						//returns a value that will close the window
						returnValue = 0;
						break;
					}
				}//keyboard
			}//while
			window.clear();
			window.draw(background);
			window.display();
		}//while
		
		/*window.clear();
		window.draw(background); 
		window.display();*/
		return returnValue;
	}//opengame()
	
	/*
	Function Name: showResults
	Purpose: 
	Parameters: none
	Return Value: none
	*/
	inline void showResults() {
		vector<Player>listPlayers = getPlayersList();
		//modify the window
		string gametitle = "Tetris Results";
		RenderWindow window(VideoMode(Tetris::WIDTH, Tetris::HEIGHT), gametitle);
		Texture t3;
		t3.loadFromFile("tetris2.png"); //currently png is in x64-Debug folder
		Sprite background(t3);
		background.setTexture(t3);
		window.draw(background);
		//Set Font
		//Font font;
		font.loadFromFile("font/sansation.tff");

		//while(window.isOpen() && stop == false){
			//Event e;
			//while (window.pollEvent(e)) {}

		//display results for all players
		string results;
		Text text;
		int i;
		for (i = 0; i <= playersList.size(); i++) {
		//results = (listPlayers); //do I get all the players info or just their points here? use an iterator?
			results = "Name: " + playersList.at(i).getName();// +" Points: " + playersList.at(i).Player::getPoints();
			//Text text;
			text.setFont(font);
			text.setCharacterSize(14);
			text.setFillColor(Color::Yellow);
			text.setString(results);
			text.setPosition(40.f, 80.f);
			//window.draw(text);
		}

		//display winner info
		string winner;
		//get winner info
		Text champ;
		champ.setFont(font);
		champ.setCharacterSize(16);
		champ.setString(winner);
		champ.setPosition(40.f, 330.f);
		/*window.draw(champ);
		
		window.clear();
		window.draw(background);
		window.draw(text);
		window.draw(champ);
		window.display();*/

		//}//end of while isOpen
	}
	 
	 /*
	* tetrisElectronics: implementation for one-single playerof Tetrisexecution
	* - Return:
	*  Kind of game to play
	*/
	inline void tetrisElectronic() {
		int curTurn = 0;
		Player player;
		int currentPoints;
		std::clock_t startTime = std::clock();  //set the start time
		double timer = 0; // start timer at 0
		int currPlayer = 0;
		Tetris game = Tetris();

		while (timer <= GameController::MAXTIMEOUT) {
			// Update the current timeout
			long curTimeout = getTimeout();
			// Execute the Tetris, returning the points for this player
			currentPoints = game.play(curTimeout, curTurn, player, GameController::LIMITEDTIME);
			/*This will determine how many seconds have passed since playing.
			* Divides difference in clock values to how many clocks per second to generate how much time has passed.*/
			timer = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
			//set cfurrent timeout to the value of timer
			setTimeout((long)timer);
			//update players points
			playersList.at(currPlayer).setPoints(currentPoints);
			
			
		}
		
	}

	inline void tetrisCompetitive(int numPlayers) {
		int curTurn = 0;
		Player player;
		int currentPoints;
		int timer;
		Tetris game = Tetris();
		while (curTurn <= numTurns) {
			// Initialization of players
			int currPlayer = 0;
			while (currPlayer < numPlayers) {
				player = playersList.at(currPlayer);
				// Update the current timeout
				long curTimeout = getTimeout();
				// Execute the Tetris, returning the points for this player
				currentPoints = game.play( curTimeout, curTurn, player, GameController::LIMITEDTIME);
				// Updates the points
				playersList.at(currPlayer).setPoints(currentPoints);
				currPlayer++;
			} 
			// Turn update
			setNumTurns(curTurn);
			curTurn++;
		}
	}

	inline void tetrisMixed(int numberPlayers) {
		int curTurn = 0;
		Player player;
		int currentPoints;
		int numPlayers = numberPlayers; //numPlayers is given by the size of players’ list
		double timer = 0;
		Tetris game = Tetris();

		while (curTurn <= numTurns || timer <= GameController::MAXTIMEOUT) { //player is restricted by time or number of turns
			// Initialize a random player
			int currPlayer = rand() % numPlayers;
			while (currPlayer < numPlayers) { //not sure if this while loop is correct or needed
				player = playersList.at(currPlayer);
				// Update the current timeout
				long curTimeout = getTimeout();
				// Execute the Tetris, returning the points for this player
				currentPoints = game.play(curTimeout, curTurn, player, GameController::LIMITEDTIME);
				// Updates the points
				playersList.at(currPlayer).setPoints(currentPoints);
				currPlayer++;
			}
			// Turn update
			setNumTurns(curTurn);
			curTurn++;
		}
	}
};



