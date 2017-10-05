#pragma once

#include "Steering.h"

class KinematicUnit;

const float MAX_WANDER_ROTATION = 0.5f;

class KinematicWanderSteering:public Steering
{
public:
	KinematicWanderSteering( KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee, float targetDisance);
	~KinematicWanderSteering(){};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	bool mShouldFlee;
	float mTargetRadius;
};