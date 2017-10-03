#include "UnitManager.h"

#include "KinematicUnit.h"
#include <cstdlib>
#include "Game.h"

UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{
	// delete all units in the vector
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		if (mpUnits[i] != NULL)
		{
			delete mpUnits[i];
		}
	}
}

void UnitManager::AddUnit(KinematicUnit* uni, int AItype)
{
	// add the new unit
	mpUnits.push_back(uni);

	switch (AItype)
	{
		case 0:
		{
			// do nothing! this is the player
			break;
		}
		case 1:
		{
			// dynamic arrive

			// when user hits the 'A' key, add a unit exactly 200 pixels away from the player's location
			// this new unit tries to ARRIVE at the player's current location

			mpUnits[mpUnits.size() - 1]->dynamicArrive(GetUnit(0));
			break;
		}
		case 2:
		{
			// dynamic seek

			// when user hits the 'S' key, add a unit exactly 200 pixels away from the player's location
			// this new unit tries to SEEK at the player's current location

			mpUnits[mpUnits.size() - 1]->dynamicSeek(GetUnit(0));
			break;
		}
	}
}

void UnitManager::RemoveRandomUnit()
{
	//delete unit

	// when user hits the 'D' key, delete a random unit (not the player)
	// when all units (besides the player) are deleted, exit the game

	srand(time(NULL));
	unsigned int seed;

	if (mpUnits.size() > 1)
	{
		seed = rand() % (mpUnits.size() - 1) + 1;
	}
	else
	{
		KinematicUnit* tmp = mpUnits[0];
		mpUnits.erase(mpUnits.begin());
		delete tmp;

		GET_GAME->setShouldExit(true);

		return;
	}

	KinematicUnit* tmp = mpUnits[seed];
	mpUnits.erase(mpUnits.begin() + seed);
	delete tmp;
}

KinematicUnit* UnitManager::GetUnit(int id)
{
	// return the unit at the specfied id
	if (mpUnits[id] != NULL)
	{
		return mpUnits[id];
	}
	else
	{
		return NULL;
	}
}

void UnitManager::UnitDraw(GraphicsBuffer* buffer)
{
	// draw all units
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->draw(buffer);
	}
}

void UnitManager::UnitUpdate(float t)
{
	// update all units
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->update(t);
	}
}