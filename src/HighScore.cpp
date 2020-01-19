#include "HighScore.h"

HighScore::HighScore() {
	string str;
	ifstream myfile ("res/HighScore.txt");
	int score;
	if (myfile.is_open()){
		while (!myfile.eof()){
			myfile >> str;
			score = stoi(str);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	this->HighestScore = score;

};
void HighScore::setHighScore(int score){
	if(this->HighestScore < score){
		this->HighestScore = score;
	}
}
int HighScore::getHighScore(){
	return this->HighestScore;
}

void HighScore::writeHighScore(){
	ofstream myfile ("res/HighScore.txt");
	  if (myfile.is_open())
	  {
	    myfile << this->HighestScore;
	    myfile.close();
	  }
}

