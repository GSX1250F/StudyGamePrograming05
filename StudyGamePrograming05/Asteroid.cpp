#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Random.h"
#include "CircleComponent.h"
#include "SoundPlayer.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	//ランダムな位置と向きと大きさと初速で初期化
	Vector2 randPos = Vector2(GetGame()->mWindowWidth * 0.5f, GetGame()->mWindowHeight * 0.5f);
	//画面の中央3/5区画以外になるまで繰り返し処理
	while (randPos.x > GetGame()->mWindowWidth * 0.2f &&
		   randPos.x < GetGame()->mWindowWidth *0.8f &&
		   randPos.y > GetGame()->mWindowHeight * 0.2f &&
		   randPos.y < GetGame()->mWindowHeight * 0.8f)
	{
		randPos = Random::GetVector(Vector2::Zero, Vector2(GetGame()->mWindowWidth, GetGame()->mWindowHeight));
	}
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	SetScale(Random::GetFloatRange(0.8f, 2.5f));
	
	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Asteroid.png"));

	//MoveComponent作成
	MoveComponent* mc = new MoveComponent(this);
	mc->SetVelocity(GetForward() * Random::GetFloatRange(50.0f, 200.0f));
	mc->SetRotSpeed(Random::GetFloatRange(-1.0f * Math::TwoPi, 1.0f * Math::TwoPi));
	
	//CircleComponent作成
	mCircle = new CircleComponent(this);

	//効果音作成
	mChunkFile = "Assets/destroy.mp3";
	game->GetSoundPlayer()->AddChunk(mChunkFile);
}

Asteroid::~Asteroid()
{
	GetGame()->GetSoundPlayer()->SetChunkControl(-1,mChunkFile,"replay",0);
	GetGame()->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
	//画面外にでたら反対の位置に移動（ラッピング処理）
	if (GetPosition().x < 0.0f - 2 * GetRadius() ||
		GetPosition().x > GetGame()->mWindowWidth + 2 * GetRadius() )
	{
		SetPosition(Vector2(GetGame()->mWindowWidth - GetPosition().x , GetPosition().y));
	}
	if (GetPosition().y < 0.0f - 2 * GetRadius() ||
		GetPosition().y > GetGame()->mWindowHeight + 2 * GetRadius())
	{
		SetPosition(Vector2(GetPosition().x , GetGame()->mWindowHeight - GetPosition().y));
	}
}


