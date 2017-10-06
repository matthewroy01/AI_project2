#pragma once

#include "Steering.h"

class KinematicUnit;

const float WAS_MAX_WANDER_ROTATION = 0.5f;

class WanderAndSeek : public Steering
{
public:
	WanderAndSeek(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee, int targetRadius);
	~WanderAndSeek() {};

	virtual Steering* getSteering();
	float getDistance();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	bool mShouldFlee;
	int mTargetRadius;

	bool mIsFleeing = false;
};