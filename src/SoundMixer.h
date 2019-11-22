#pragma once

#include <SDL.h>
#include <SDL_Mixer.h>
#include <map>
#include <string>

using namespace std;

class SoundMixer {
public:

	SoundMixer();

	~SoundMixer();


	void playSound(const string& path);

	void playMusic(const string& path);

	void muteMusic();



private:

	void initiliaze();

	bool addSound(const string& name, const string& path);

	bool addMusic(const string& name, const string& music);

	map<string, Mix_Chunk*> sounds;

	map<string, Mix_Music*> music;


};
