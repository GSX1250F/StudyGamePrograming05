#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner) 
	,mVelocity(Vector3::Zero)		// ���i�ړ����x
	,mRotSpeed(Vector3::Zero)				// ��]���x
	,mMass(1.0f)					// ����
	,mMoveForce(Vector3::Zero)		// �d�S�ɂ������
	,mRotForce(Vector3::Zero)				// ��]�����̗�F +������CCW
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
	// Actor�̈ʒu�ƕ������X�V
	Vector3 gVelocity = Vector3::Transform(mVelocity, mOwner->GetRotation());
	mOwner->SetPosition(mOwner->GetPosition() + gVelocity * deltatime);

	if (!Math::NearZero(mRotSpeed.x))
	{
		// x�������]
		Quaternion rot = mOwner->GetRotation();
		// ��]��ω�������N�H�[�^�j�I�����쐬
		Quaternion inc(Vector3::UnitX, mRotSpeed.x * deltatime);
		// ���Ƃ�rot�Ƒ����̃N�H�[�^�j�I��������
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mRotSpeed.y))
	{
		// y�������]
		Quaternion rot = mOwner->GetRotation();
		// ��]��ω�������N�H�[�^�j�I�����쐬
		Quaternion inc(Vector3::UnitY, mRotSpeed.y * deltatime);
		// ���Ƃ�rot�Ƒ����̃N�H�[�^�j�I��������
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mRotSpeed.z))
	{
		// Z�������]
		Quaternion rot = mOwner->GetRotation();
		// ��]��ω�������N�H�[�^�j�I�����쐬
		Quaternion inc(Vector3::UnitZ, mRotSpeed.z * deltatime);
		// ���Ƃ�rot�Ƒ����̃N�H�[�^�j�I��������
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}

	// ���x�Ɗp���x���X�V
	SetVelocity(mVelocity + GetMoveAccel() * deltatime);	//v = vo + at
	SetRotSpeed(mRotSpeed + GetRotAccel() * deltatime);		//�� = ��o + bt
}

Vector3 MoveComponent::GetMoveAccel() const
{
	if (!Math::NearZero(mMass))
	{
		Vector3 accel = mMoveForce * (1 / mMass);    //�d�S�����x�̌v�Z�@F=ma  a=F*(1/m)
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
		// ��]�����x�̌v�Z�@��]�����x = �g���N / �������[�����g
		Vector3 accel = GetTorque() * (1.0f / GetImoment());		//��]�����x�̌v�Z Fr=Ia  a=Fr/I
		//��R�� = ����*��R�W��    ���� = -����*��R�W��*���a/�������[�����g
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
	// �������[�����g�v�Z�@��2�����ɂ����ẮA��l���x�̉~�Ƃ���B I=0.5*����*���a^2
	return 0.5f * mMass * mOwner->GetRadius() * mOwner->GetRadius();
}

Vector3 MoveComponent::GetTorque() const
{
	// �g���N�v�Z�@�g���N=��]�����̗� * ���a
	return mRotForce * mOwner->GetRadius();
}