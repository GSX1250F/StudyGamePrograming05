#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	//�R���X�g���N�^�BUpdate Order�͑��߁B
	MoveComponent(class Actor* owner , int updateOrder = 10);
	~MoveComponent();

	//Update���I�[�o�[���C�h
	void Update(float deltatime) override;

	// �P���ɓ������̂ɕK�v�ȃp�����[�^�̃Z�b�^�[���Q�b�^�[
	// ���i�ړ����x(Forward, Strafe, upward)
	void SetVelocity(Vector3 vel) { mVelocity = vel; }
	// ��]���x(yaw(z������),pitch(y������), roll(x������))
	void SetRotSpeed(Vector3 rotspeed) { mRotSpeed = rotspeed; }

	// �ÓT�����ɕK�v�ȃp�����[�^�̃Z�b�^�[���Q�b�^�[
	// ���i�ړ������x(Forward, Strafe, upward)
	Vector3 GetMoveAccel() const;
	// ��]�ړ������x(yaw(z������),pitch(y������), roll(x������))
	Vector3 GetRotAccel() const;

	// ����
	void SetMass(float v) { mMass = v; }
	//�d�S�ɂ������(Forward, Strafe, upward)
	void SetMoveForce(Vector3 v) { mMoveForce = v; }
	//��]�����̗�(roll(x������),pitch(y������), yaw(z������))
	void SetRotForce(Vector3 v) { mRotForce = v; }
	// �������[�����g
	float GetImoment() const;
	// �g���N
	Vector3 GetTorque() const;
	//���i�ړ��̒�R��
	void SetMoveResist(float v) { mMoveResist = v; }
	//��]�ړ��̒�R��
	void SetRotResist(float v) { mRotResist = v; }
	
private:
	// �P���ړ��p�����[�^
	Vector3 mVelocity;		// ���i�ړ����x
	Vector3 mRotSpeed;		// ��]���x

	// �j���[�g���͊w�p�����[�^
	float mMass;			// ����
	Vector3 mMoveForce;		// �d�S�ɂ������
	Vector3 mRotForce;		// ��]�����̗�F +������CCW
	float mMoveResist;		// �d�S���x��R��(%)
	float mRotResist;		// ��]���x��R��(%)
};