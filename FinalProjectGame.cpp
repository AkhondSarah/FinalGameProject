/*
* FILE:			FinalProjectGame.cpp
* PURPORE:		This houses the main method, and deals with calling the different game functions
* AUTHOR(S):	Nhi Banh 		ID: 	040 932 192 Lab section: 301
*				Neil Bender		ID:		040 882 737 Lab section : 302
*				Akhond Sarah Mesbah	ID:	041 009 466 Lab section : 303
* PROFESSOR:	Paulo Sousa
* Lab Instructor: Dr. Frank Emanuel
* COURSE:		CST8219 C++ Programming
* Assignment: Final Project ( Implementing a Real Game and Multiple Scenario )
* Due Date: 14 August 2021
*/
using namespace std;

//  FinalProjectGame.cpp : This file contains the main functions, program execution begind from here
#include <iostream>
#include "GameController.h"
using namespace sf;
using namespace std;
//Boolean value to print message on console
const bool ISDEBUG = true;

int main() {
	// Main Controller
	GameController controler = GameController();
	// user answer (by keyboard)
	int answer = -1;
	// defines the end of the game
	bool final = false;
	// Current turn
    int numTurns = 1;
	//Current timeout
	long timeout = 0;
	// Num players
	int numPlayers = 0;
	//Initialization
	numTurns = 1;
	timeout = 0;
	controler.setTimeout(timeout);
	controler.setNumTurns(numTurns);
	// Main menu
	while(!final) {
		answer = controler.openGame();// Function to be detailed later
		if (answer == 0) {
			final = true;
		}
		else if (answer == 1) {
			// Electronic Game
		    // Creates list of one player
			int numPlayers = 1;
			vector<Player> list = controler.createPlayersList(numPlayers);
			controler.setPlayerList(list);
			// Debug message
			if (ISDEBUG) {
				cout << "---------------------------" << endl;
				cout << "- ELECTRONIC GAME ........." << endl;
				cout << "* Timeout = " << to_string(GameController::MAXTIMEOUT) << endl;
				cout << "* Round by points = " << to_string(GameController::LIMITEDTIME) << endl;
				cout << "---------------------------" << endl;
			}
			// Game execution
			controler.tetrisElectronic();
		    controler.showResults();
		}
		else if (answer == 2) {
			// Competetive Game
			int numPlayers = 2;
			vector<Player> list = controler.createPlayersList(numPlayers);
			controler.setPlayerList(list);
			controler.tetrisCompetitive(numPlayers);
			controler.showResults();
		}
		else if (answer == 3) {
			// Mixed Game
			int numPlayers = 3;
			vector<Player> list = controler.createPlayersList(numPlayers);
			controler.setPlayerList(list);
			controler.tetrisMixed(numPlayers);
			controler.showResults();
		}	
	}
}
