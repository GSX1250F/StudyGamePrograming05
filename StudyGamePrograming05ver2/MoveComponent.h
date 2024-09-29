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
	// ���i�ړ����x
	void SetVelocity(Vector3 vel) { mVelocity = vel; }
	// ��]���x
	void SetRotSpeed(float rotspeed) { mRotSpeed = rotspeed; }

	// �ÓT�����ɕK�v�ȃp�����[�^�̃Z�b�^�[���Q�b�^�[
	// ���i�ړ������x
	Vector3 GetMoveAccel() const;
	// ��]�ړ������x
	float GetRotAccel() const;

	// ����
	void SetMass(float v) { mMass = v; }
	//�d�S�ɂ������
	void SetMoveForce(Vector3 v) { mMoveForce = v; }
	//��]�����̗�
	void SetRotForce(float v) { mRotForce = v; }
	// �������[�����g
	float GetImoment() const;
	// �g���N
	float GetTorque() const;
	//���i�ړ��̒�R��
	void SetMoveResist(float v) { mMoveResist = v; }
	//��]�ړ��̒�R��
	void SetRotResist(float v) { mRotResist = v; }
	
private:
	// �P���ړ��p�����[�^
	Vector3 mVelocity;		// ���i�ړ����x
	float mRotSpeed;		// ��]���x

	// �j���[�g���͊w�p�����[�^
	float mMass;			// ����
	Vector3 mMoveForce;		// �d�S�ɂ������
	float mRotForce;		// ��]�����̗�F +������CCW
	float mMoveResist;		// �d�S���x��R��(%)
	float mRotResist;		// ��]���x��R��(%)
};