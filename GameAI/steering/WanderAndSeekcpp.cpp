#include "WanderAndSeek.h"
#include "KinematicUnit.h"
#include "Game.h"

WanderAndSeek::WanderAndSeek(KinematicUnit *pMover, KinematicUnit* pTarget, bool shouldFlee, int i)
	:mpMover(pMover)
	,mShouldFlee(shouldFlee)
	,mpTarget(pTarget)
{
	mApplyDirectly = true;
}

Steering* WanderAndSeek::getSteering()
{
	//if (getDistance() < 500)
	//{
	//	mLinear = mpTarget->getPosition() - mpMover->getPosition();

	//	//inside the satisfaction radius?
	//	if (mLinear.getLengthSquared() < 10 * 10)
	//	{
	//		mLinear = gZeroVector2D;
	//		mAngular = mpMover->getOrientation();
	//		return this;
	//	}

	//	//calc how long we'd like it to take to get there
	//	mLinear /= 1;

	//	float maxVelocity = mpMover->getMaxVelocity();//for efficiency

	//	if (mLinear.getLengthSquared() > maxVelocity * maxVelocity)//velocity too great?
	//	{
	//		//cap the velocity
	//		mLinear.normalize();
	//		mLinear *= maxVelocity;
	//	}

	//	mAngular = Kinematic::getOrientationFromVelocity(mpMover->getOrientation(), mLinear);
	//}
	//else
	//{
	//	// wander
	//	mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
	//	mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
	//}
	return this;
}

int WanderAndSeek::getDistance()
{
	return std::sqrt((mpMover->getPosition().getX() - mpTarget->getPosition().getX()) * (mpMover->getPosition().getX() - mpTarget->getPosition().getX())) +
		   ((mpMover->getPosition().getY() - mpTarget->getPosition().getY()) * (mpMover->getPosition().getY() - mpTarget->getPosition().getY()));
}