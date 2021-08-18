/*
* FILE:			FinalProjectGame.cpp
* PURPORE:		Contains the player list and all the player info
* AUTHOR(S):	Nhi Banh 		ID: 	040 932 192 Lab section: 301
*				Neil Bender		ID:		040 882 737 Lab section : 302
*				Akhond Sarah Mesbah	ID:	041 009 466 Lab section : 303
* PROFESSOR:	Paulo Sousa
* Lab Instructor: Dr. Frank Emanuel
* COURSE:		CST8219 C++ Programming
* Assignment: Final Project ( Implementing a Real Game and Multiple Scenario )
* Due Date: 14 August 2021
*/
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
    Player() {
        this->name = "NoName";
    }
    Player(std::string name) {
        this->name = name;
    }
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
