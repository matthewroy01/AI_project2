#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Trackable.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class UIManager : public Trackable
{
	private :
		bool Init();

		// the font
		ALLEGRO_FONT* mpFont;

	public :
		UIManager();
		~UIManager();

		void doUI();
};

#endif