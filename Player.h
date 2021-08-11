#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
* Player class to be used in the tetris (Final project) Game
* The attributes: name, points and isCurrentPlsyer are used to define the behavious of the players
*/

class Player {

private:
         string name; //Name of the player
         int points;  //Points of the player
         bool isCurrentPlayer; // Identify if they can play or not

public:

    static const int DEFAULT_POINTS = 0;

    // Constructors

    /*
    * sets points
    */
    inline Player setPoints(int newPoints) {
        points = newPoints;
        return *this;
    }

    /*
   * sets name
   */
    inline Player setName(string newName) {
        name = newName;
        return *this;
    }

    /*
  * sets iscurrentPlayer
  */
    inline Player setisCurrentPlayer(bool newisCurrentPlayer) {
        isCurrentPlayer = newisCurrentPlayer;
        return *this;
    }

    /*
    * Gets points
    */
    inline int getPoints() {
        return points;
    }

    /*
    * Gets name
    */
    inline string getName() {
        return name;
    }

    /*
    * Gets isCurrentPlayer
    */
    inline bool getisCurrentPlayer() {
        return isCurrentPlayer;
    }


};
