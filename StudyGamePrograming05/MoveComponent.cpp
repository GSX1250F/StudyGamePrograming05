#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner) 
	,mVelocity(Vector2::Zero)		// ���i�ړ����x
	,mRotSpeed(0.0f)				// ��]���x
	,mMass(1.0f)					// ����
	,mMoveForce(Vector2::Zero)		// �d�S�ɂ������
	,mRotForce(0.0f)				// ��]�����̗�F +������CCW
	,mMoveResist(0.0f)				// �d�S���x��R��(%)
	,mRotResist(0.0f)				// ��]���x��R��(%)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	// �ʒu�ƌ������X�V
	mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltatime);		//x = xo + vt
	mOwner->SetRotation(mOwner->GetRotation() + mRotSpeed * deltatime);		//�� = ��o + ��t

	// ���x�Ɗp���x���X�V
	SetVelocity(mVelocity + GetMoveAccel() * deltatime);	//v = vo + at
	SetRotSpeed(mRotSpeed + GetRotAccel() * deltatime);		//�� = ��o + bt
}

Vector2 MoveComponent::GetMoveAccel() const
{
	if (!Math::NearZero(mMass))
	{
		Vector2 accel = mMoveForce * (1 / mMass);    //�d�S�����x�̌v�Z�@F=ma  a=F*(1/m)
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
		// ��]�����x�̌v�Z�@��]�����x = �g���N / �������[�����g
		float accel = GetTorque() / GetImoment();		//��]�����x�̌v�Z Fr=Ia  a=Fr/I
		//��R�� = ����*��R�W��    ���� = -����*��R�W��*���a/�������[�����g
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
	// �������[�����g�v�Z�@��2�����ɂ����ẮA��l���x�̉~�Ƃ���B I=0.5*����*���a^2
	return 0.5f * mMass * mOwner->GetRadius() * mOwner->GetRadius();
}

float MoveComponent::GetTorque() const
{
	// �g���N�v�Z�@�g���N=��]�����̗� * ���a
	return mRotForce * mOwner->GetRadius();
}
