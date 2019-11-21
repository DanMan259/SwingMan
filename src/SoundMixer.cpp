#include "SoundMixer.h"
#include <iostream>

SoundMixer::SoundMixer() {
	//all sounds
	addSound("coin", "res/coin_effect.wav");
	addSound("top", "res/top_effect.wav");
	addSound("explosion", "res/explosion_effect.wav");
	addSound("geyser", "res/geyser_effect.wav");
	addSound("bat", "res/bat_effect.wav");
	addSound("rope", "res/rope_effect.wav");
	//all music
	addMusic("music", "res/8bitmusic.mp3");

	this->initiliaze();
}


SoundMixer::~SoundMixer() {
//	map<string, Mix_Chunk*>::iterator it;
//
//	for ( it = sounds.begin(); it != sounds.end(); it++ )
//	{
//		Mix_FreeChunk(it->second);
//	}
//
//	map<string, Mix_Music*>::iterator it2;
//
//	for ( it2 = music.begin(); it2 != music.end(); it2++ )
//	{
//		Mix_FreeMusic(it2->second);
//	}

	Mix_CloseAudio();
}

void SoundMixer::initiliaze() {
	 //Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
	}

	playMusic("music");
}



void SoundMixer::playSound(const string& path) {
	Mix_Chunk* sound = sounds[path];

	if(sound == NULL) {
		cout << "unable to play: " << path << endl;
		return;
	}

	Mix_PlayChannel(-1, sound, 0);
}

void SoundMixer::playMusic(const string& path) {
	Mix_Music* m = music[path];

	if(m == NULL) {
		cout << "unable to play: " << path << endl;
		return;
	}

	Mix_VolumeMusic(MIX_MAX_VOLUME/3);
	Mix_PlayMusic(m, -1);
}


bool SoundMixer::addMusic(const string& name, const string& music) {
	Mix_Music* m = Mix_LoadMUS(music.c_str());
	if(m == nullptr) {
		cout << "Error loading: " << music << endl;
		return false;
	}

	this->music.insert(std::pair<std::string, Mix_Music*>(name, m));
	return true;
}

bool SoundMixer::addSound(const string& name, const string& sound) {
	Mix_Chunk* s = Mix_LoadWAV(sound.c_str());
	if(s == nullptr) {
		cout << "Error loading: " << sound << endl;
		return false;
	}

	this->sounds.insert(std::pair<std::string, Mix_Chunk*>(name, s));
	return true;
}

