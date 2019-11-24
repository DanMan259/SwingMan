#pragma once

#include <SDL.h>
#include <SDL_Mixer.h>
#include <map>
#include <string>
#include "GameWindow.h"

//forward declarations
class GameWindow;

using namespace std;

/*
 * This class is responsible for handling
 * all of the audio in the game
 */
class SoundMixer {
public:

	/*
	 * Default constructer
	 * Loads in all of the music and also plays the first music sequence
	 */
	SoundMixer();

	/*
	 * Destructor
	 */
	~SoundMixer();


	/*
	 * @param window the game window
	 * @param the name of the sound
	 *
	 * Plays a wav file
	 */
	void playSound(GameWindow* window, const string& path);

	/*
	 * @param name the name of the music
	 *
	 * Plays a mp3 file
	 */
	void playMusic(const string& path);

	/*
	 * @param mute which indicates if the music should be turned off or not
	 */
	void muteMusic(const bool& mute);

private:

	/*
	 * Initiliazes the SDL_Mixer library
	 */
	void initiliaze();

	/*
	 * @param name the sound name which is how this sound will be accessed
	 * @param path the path of the sound
	 * Adds a sound to the sounds map
	 */
	bool addSound(const string& name, const string& path);

	/*
	 * @param name the music name which is how this music will be accessed
	 * @param music the music of the sound
	 * Adds a music to the music map
	 */
	bool addMusic(const string& name, const string& music);

	/*
	 * The sounds map
	 */
	map<string, Mix_Chunk*> sounds;

	/*
	 * The music map
	 */
	map<string, Mix_Music*> music;


};
