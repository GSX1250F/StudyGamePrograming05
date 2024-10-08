#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner) : Component(owner)
{
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetRadius();
}

const Vector3& CircleComponent::GetCenter() const
{
	return  mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// ２つのCircleComponentの中心間距離の2乗を計算
	float distSq = (a.GetCenter() - b.GetCenter()).LengthSq();

	// ２つのCircleComponentの半径の和の2乗を計算 
	float sumRadiusSq = (a.GetRadius() + b.GetRadius()) * (a.GetRadius() + b.GetRadius());

	// 中心間距離 <= 半径の和 のとき、衝突したと判定
	if (distSq <= sumRadiusSq)
	{
		return true;
	}
	else 
	{
		return false; 
	}
}