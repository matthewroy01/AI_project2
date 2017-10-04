#pragma once

#include "Steering.h"

class KinematicUnit;

class WanderAndSeek :public Steering
{
public:
	WanderAndSeek(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee, int i);
	~WanderAndSeek() {};

	virtual Steering* getSteering();
	int getDistance();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	bool mShouldFlee;
};