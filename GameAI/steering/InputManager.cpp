#include "InputManager.h"

#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "UnitCreateArriveMessage.h"
#include "UnitCreateSeekMessage.h"
#include "UnitDeleteRandomMessage.h"
#include "Game.h"
#include "GraphicsSystem.h"

InputManager::InputManager()
{
	mAdown = false;
	mSdown = false;
	mDdown = false;

	if (!init())
	{
		// something wasn't installed
	}
}

InputManager::~InputManager()
{
	// delete the font
	al_destroy_font(mpFont);
	mpFont = NULL;
}

bool InputManager::init()
{
	if (!al_install_keyboard())
	{
		printf("Keyboard not installed!\n");
		return false;
	}

	if (!al_install_mouse())
	{
		printf("Mouse not installed!\n");
		return false;
	}

	al_init_font_addon();
	if (!al_init_ttf_addon())
	{
		printf("ttf font addon not initted properly!\n");
		return false;
	}

	// install font
	al_init_font_addon();
	if (!al_init_ttf_addon())
	{
		printf("ttf font addon not initted properly!\n");
		return false;
	}

	//actually load the font
	mpFont = al_load_ttf_font("cour.ttf", 20, 0);
	if (mpFont == NULL)
	{
		printf("ttf font file not loaded properly!\n");
		return false;
	}

	return true;
}

void InputManager::Update()
{
	//left mouse click
	al_get_mouse_state(&mouseState);
	if (al_mouse_button_down(&mouseState, 1))
	{
		Vector2D pos(mouseState.x, mouseState.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//create mouse text
	std::stringstream mousePos;
	mousePos << mouseState.x << ":" << mouseState.y;

	//write text at mouse position
	al_draw_text(mpFont, al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());

	GRAPHICS_SYSTEM->swap();

	//get current keyboard state
	al_get_keyboard_state(&keyState);

	//if 'escape' key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		GET_GAME->setShouldExit(true);
	}

	//if 'a' key is pressed create a random unit that arrives to the player's position
	if (al_key_down(&keyState, ALLEGRO_KEY_A) && !mAdown)
	{
		mAdown = true;
		GameMessage* pMessage = new UnitCreateArriveMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 's' key is pressed create a random unit that seeks to the player's position
	if (al_key_down(&keyState, ALLEGRO_KEY_S) && !mSdown)
	{
		mSdown = true;
		GameMessage* pMessage = new UnitCreateSeekMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 's' key is pressed delete a random unit
	if (al_key_down(&keyState, ALLEGRO_KEY_D) && !mDdown)
	{
		mDdown = true;
		GameMessage* pMessage = new UnitDeleteRandomMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	// check to see if you're still pressing the button so you can't create or delete a unit by just holding the key
	if (!al_key_down(&keyState, ALLEGRO_KEY_A)) { mAdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_S)) { mSdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_D)) { mDdown = false; }
}