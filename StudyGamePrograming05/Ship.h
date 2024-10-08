#pragma once
#include "Actor.h"
#include <string>
#include <vector>

class Ship : public Actor
{
public:
	Ship(Game* game);
	
	void ActorInput(const uint8_t* keyState) override;
	void UpdateActor(float deltaTime) override;

	void Init();

private:
	float mLaserCooldown;
	bool mCrash;				//衝突検知
	float mCrashingTime;		//衝突演出時間
	float mCrashCooldown;		//衝突演出後、リセットされるまでスプライトを消す時間
	Vector2 mCrashPos;		//衝突したときの位置
	float mCrashRot;			//衝突したときの向き
	class CircleComponent* mCircle; 
	class SomeSpriteComponent* mSSC;
	class InputComponent* mIC;
	std::vector<std::string> mChunkFiles;
};