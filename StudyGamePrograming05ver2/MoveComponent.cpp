#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner) 
	,mVelocity(Vector3::Zero)		// 並進移動速度
	,mRotSpeed(Vector3::Zero)				// 回転速度
	,mMass(1.0f)					// 質量
	,mMoveForce(Vector3::Zero)		// 重心にかかる力
	,mRotForce(Vector3::Zero)				// 回転方向の力F +方向はCCW
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
	// Actorの位置と方向を更新
	Vector3 gVelocity = Vector3::Transform(mVelocity, mOwner->GetRotation());
	mOwner->SetPosition(mOwner->GetPosition() + gVelocity * deltatime);

	if (!Math::NearZero(mRotSpeed.x))
	{
		// x軸周り回転
		Quaternion rot = mOwner->GetRotation();
		// 回転を変化させるクォータニオンを作成
		Quaternion inc(Vector3::UnitX, mRotSpeed.x * deltatime);
		// もとのrotと増分のクォータニオンを結合
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mRotSpeed.y))
	{
		// y軸周り回転
		Quaternion rot = mOwner->GetRotation();
		// 回転を変化させるクォータニオンを作成
		Quaternion inc(Vector3::UnitY, mRotSpeed.y * deltatime);
		// もとのrotと増分のクォータニオンを結合
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mRotSpeed.z))
	{
		// Z軸周り回転
		Quaternion rot = mOwner->GetRotation();
		// 回転を変化させるクォータニオンを作成
		Quaternion inc(Vector3::UnitZ, mRotSpeed.z * deltatime);
		// もとのrotと増分のクォータニオンを結合
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}

	// 速度と角速度を更新
	SetVelocity(mVelocity + GetMoveAccel() * deltatime);	//v = vo + at
	SetRotSpeed(mRotSpeed + GetRotAccel() * deltatime);		//ω = ωo + bt
}

Vector3 MoveComponent::GetMoveAccel() const
{
	if (!Math::NearZero(mMass))
	{
		Vector3 accel = mMoveForce * (1 / mMass);    //重心加速度の計算　F=ma  a=F*(1/m)
		accel -= mVelocity * mMoveResist * 0.01f * (1 / mMass);
		return accel;
	}
	else
	{
		return Vector3::Zero;
	}
}

Vector3 MoveComponent::GetRotAccel() const
{
	if (!Math::NearZero(GetImoment()))
	{
		// 回転加速度の計算　回転加速度 = トルク / 慣性モーメント
		Vector3 accel = GetTorque() * (1.0f / GetImoment());		//回転加速度の計算 Fr=Ia  a=Fr/I
		//抵抗力 = 速さ*抵抗係数    減速 = -速さ*抵抗係数*半径/慣性モーメント
		accel -= mRotSpeed * mOwner->GetRadius() * mRotResist * (1.0f / GetImoment());
		return accel;
	}
	else
	{
		return Vector3::Zero; 
	}
}

float MoveComponent::GetImoment() const
{
	// 慣性モーメント計算　※2次元においては、一様密度の円板とする。 I=0.5*質量*半径^2
	return 0.5f * mMass * mOwner->GetRadius() * mOwner->GetRadius();
}

Vector3 MoveComponent::GetTorque() const
{
	// トルク計算　トルク=回転方向の力 * 半径
	return mRotForce * mOwner->GetRadius();
}