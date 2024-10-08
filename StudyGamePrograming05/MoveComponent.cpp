#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner) 
	,mVelocity(Vector2::Zero)		// 並進移動速度
	,mRotSpeed(0.0f)				// 回転速度
	,mMass(1.0f)					// 質量
	,mMoveForce(Vector2::Zero)		// 重心にかかる力
	,mRotForce(0.0f)				// 回転方向の力F +方向はCCW
	,mMoveResist(0.0f)				// 重心速度抵抗率(%)
	,mRotResist(0.0f)				// 回転速度抵抗率(%)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	// 位置と向きを更新
	mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltatime);		//x = xo + vt
	mOwner->SetRotation(mOwner->GetRotation() + mRotSpeed * deltatime);		//Θ = Θo + ωt

	// 速度と角速度を更新
	SetVelocity(mVelocity + GetMoveAccel() * deltatime);	//v = vo + at
	SetRotSpeed(mRotSpeed + GetRotAccel() * deltatime);		//ω = ωo + bt
}

Vector2 MoveComponent::GetMoveAccel() const
{
	if (!Math::NearZero(mMass))
	{
		Vector2 accel = mMoveForce * (1 / mMass);    //重心加速度の計算　F=ma  a=F*(1/m)
		accel -= mVelocity * mMoveResist * 0.01f * (1 / mMass);
		return accel;
	}
	else
	{
		return Vector2::Zero;
	}
}

float MoveComponent::GetRotAccel() const
{
	if (!Math::NearZero(GetImoment()))
	{
		// 回転加速度の計算　回転加速度 = トルク / 慣性モーメント
		float accel = GetTorque() / GetImoment();		//回転加速度の計算 Fr=Ia  a=Fr/I
		//抵抗力 = 速さ*抵抗係数    減速 = -速さ*抵抗係数*半径/慣性モーメント
		accel -= mRotSpeed * mOwner->GetRadius() * mRotResist / GetImoment();
		return accel;
	}
	else
	{
		return 0.0f; 
	}
}

float MoveComponent::GetImoment() const
{
	// 慣性モーメント計算　※2次元においては、一様密度の円板とする。 I=0.5*質量*半径^2
	return 0.5f * mMass * mOwner->GetRadius() * mOwner->GetRadius();
}

float MoveComponent::GetTorque() const
{
	// トルク計算　トルク=回転方向の力 * 半径
	return mRotForce * mOwner->GetRadius();
}