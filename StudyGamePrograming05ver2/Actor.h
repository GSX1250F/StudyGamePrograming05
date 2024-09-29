#pragma once
#include <vector>
#include "Math.h"
#include <SDL.h>

class Actor
{
public:
	enum State
	{
		EActive,		//�ғ���
		EPaused,		//�X�V��~��
		EDead			//�폜�Ώ�
	};

	Actor(class Game* game);
	virtual ~Actor();

	// �Q�[������Ăяo�����Process Input(�I�[�o�[���C�h�s��)
	void ProcessInput(const uint8_t* keyState);
	// �A�N�^�[�Ǝ��̓��͏���(�I�[�o�[���C�h�\)
	virtual void ActorInput(const uint8_t* keyState);

	// �Q�[������Ăяo�����X�V�֐�(�I�[�o�[���C�h�s��)
	void Update(float deltaTime);
	// �A�N�^�[�����S�R���|�[�l���g���X�V(�I�[�o�[���C�h�s��)
	void UpdateComponents(float deltaTime);
	// �A�N�^�[�Ǝ��̍X�V����(�I�[�o�[���C�h�\)
	virtual void UpdateActor(float deltaTime);
	
	// �Q�b�^�[�E�Z�b�^�[
	// �ʒu
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	// �g�嗦�i���ʂ͕ς��Ȃ��B���a�ɉe������j
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true;
	}
	// ��]
	const float& GetRotation() const { return mRotation; }
	void SetRotation(const float& rotation) { mRotation = rotation; mRecomputeWorldTransform = true;
	}
	// ���a
	float GetRadius() const { return mRadius * mScale; }	//�g�嗦���l��
	void SetRadius(float radius) { mRadius = radius; mRecomputeWorldTransform = true;
	}

	// �����̒P�ʃx�N�g��
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }

	// ���
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	// ���[���h�ϊ�
	void ComputeWorldTransform();
	Matrix4 GetWorldTransform() { return mWorldTransform; }

private:
	State mState;			//�A�N�^�[���
	Vector2 mPosition;		//��ʏ�̈ʒu
	float mScale;			//�g�嗦
	float mRotation;		//��]
	float mRadius;			//���a�i�g�嗦�͖����j
	std::vector<class Component*> mComponents;
	class Game* mGame;

	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;
};