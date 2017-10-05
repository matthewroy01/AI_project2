#include "KinematicWanderSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include <math.h>

KinematicWanderSteering::KinematicWanderSteering(KinematicUnit *pMover, KinematicUnit *pTarget, bool shouldFlee, float targetRadius)
:mpMover(pMover),
mpTarget(pTarget),
mShouldFlee(shouldFlee)
{
	mApplyDirectly = true;
	mTargetRadius = targetRadius;
	mShouldFlee = false;
}

Steering* KinematicWanderSteering::getSteering()
{
	Vector2D direction;
	float distance;

	if (mShouldFlee)
	{
		direction = (mpTarget->getPosition() - mpMover->getPosition()) * -1;
		distance = direction.getLength();
	}
	else
	{
		direction = mpTarget->getPosition() - mpMover->getPosition();
		distance = direction.getLength();
	}

	if (distance < 400)
	{
		mLinear = mpTarget->getPosition() - mpMover->getPosition();

		////inside the satisfaction radius?
		//if (mLinear.getLengthSquared() < mTargetRadius * mTargetRadius)
		//{
		//	mLinear = gZeroVector2D;
		//	mAngular = mpMover->getOrientation();
		//	return this;
		//}

		////calc how long we'd like it to take to get there
		//mLinear /= 1.0f;

		//float maxVelocity = mpMover->getMaxVelocity();//for efficiency

		//if (mLinear.getLengthSquared() > maxVelocity * maxVelocity)//velocity too great?
		//{
		//	//cap the velocity
		//	mLinear.normalize();
		//	mLinear *= maxVelocity;
		//}

		float targetSpeed = 0.0f;

		//are we outside slow radius?
		if (distance > 100)
		{
			targetSpeed = mpMover->getMaxVelocity();
		}
		else
		{
			targetSpeed = (mpMover->getMaxVelocity() * distance) / 100;
		}

		//combine speed and direction to get targetVelocity
		Vector2D targetVelocity = direction;
		targetVelocity.normalize();
		targetVelocity *= targetSpeed;

		//set acceleration
		mLinear = targetVelocity - mpMover->getVelocity();
		mLinear /= 1.0f;

		//check if too fast
		if (mLinear.getLength() > mpMover->getMaxAcceleration())
		{
			//cut down to max
			mLinear.normalize();
			mLinear *= mpMover->getMaxAcceleration();
		}

		mAngular = Kinematic::getOrientationFromVelocity(mpMover->getOrientation(), mLinear);
	}
	else
	{
		// wander
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() + (genRandomBinomial() * MAX_WANDER_ROTATION);
		mpMover->setOrientation(mAngular);
	}

	return this;
}