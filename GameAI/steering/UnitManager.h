#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <vector>
#include "Trackable.h"

class Kinematic;
class KinematicUnit;
class GraphicsBuffer;

class UnitManager : public Trackable
{
	private :
		// a vector of all the units in the scene
		std::vector <KinematicUnit*> mpUnits;
		std::vector <KinematicUnit*> mpWalls;

	public :
		UnitManager();
		~UnitManager();

		void AddUnit(KinematicUnit* uni, int AItype);
		void AddUnit(KinematicUnit* uni);
		void RemoveRandomUnit();
		KinematicUnit* GetUnit(int id);

		void UnitUpdate(float t);
		void UnitDraw(GraphicsBuffer* buffer);
};

#endif