#include "KinematicWanderSteering.h"
#include "KinematicUnit.h"
#include "Game.h"

KinematicWanderSteering::KinematicWanderSteering(KinematicUnit *pMover)
:mpMover(pMover)
{
	mApplyDirectly = true;
}

Steering* KinematicWanderSteering::getSteering()
{
	std::cout << "tfw you fix the professor's code by changing a * to a +" << std::endl;
	mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
	mAngular = mpMover->getOrientation() + ( genRandomBinomial() * 0.5 );
	return this;
}