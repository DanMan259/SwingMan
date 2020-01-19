#pragma once

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/*
 * Handles the highscore functionality in the game
 */
class HighScore{
public:

	/*
	 * Default constructor
	 * Handles reading of text file
	 */
	HighScore();

	/*
	 * @return highScore
	 */
	int getHighScore();

	/*
	 * @param score to score
	 */
	void setHighScore(int score);

	/*
	 * Writes the highscore to the text file
	 */
	void writeHighScore();
private:

	/*
	 * The highscore of the game
	 */
	int HighestScore = 0;
};
