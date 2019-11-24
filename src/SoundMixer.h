#pragma once

#include <SDL.h>
#include <SDL_Mixer.h>
#include <map>
#include <string>
#include "GameWindow.h"

class GameWindow;

using namespace std;

class SoundMixer {
public:

	SoundMixer();

	~SoundMixer();


	void playSound(GameWindow* window, const string& path);

	void playMusic(const string& path);

	void muteMusic(const bool& mute);




private:

	void initiliaze();

	bool addSound(const string& name, const string& path);

	bool addMusic(const string& name, const string& music);

	map<string, Mix_Chunk*> sounds;

	map<string, Mix_Music*> music;


};
