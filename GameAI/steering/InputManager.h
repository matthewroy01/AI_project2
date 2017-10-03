#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Trackable.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <sstream>
#include <stdio.h>

class Game;

class InputManager : public Trackable
{
	private :
		// bools that keep track of whether or not a key is still being pressed (sort of a way to cheat in "al_key_up")
		bool mAdown, mSdown, mDdown;

		// mouse and keyboard state
		ALLEGRO_MOUSE_STATE mouseState;
		ALLEGRO_KEYBOARD_STATE keyState;

		// the mouse position
		std::stringstream mousePos;

		// the font
		ALLEGRO_FONT* mpFont;

	public :
		InputManager();
		~InputManager();

		bool init();

		void Update(); 
		
		inline ALLEGRO_FONT* getFont() const { return mpFont; };
};

#endif