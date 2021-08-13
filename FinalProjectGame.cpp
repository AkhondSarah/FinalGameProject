// FinalProjectGame.cpp : Defines the entry point for the application.
//
using namespace std;

//  FinalProjectGame.cpp : This file contains the main functions, program execution begind from here
#include <iostream>
#include "GameController.h"

using namespace sf;
using namespace std;


//Boolean value to print message on console
const bool ISDEBUG = true;

int main()
{
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
			//controler.tetrisCompetetive();

		}
		else if (answer == 3) {
			//controler.tetrisMixed();

		}
			
	}
}
