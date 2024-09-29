#include "BackGround.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"

BackGround::BackGround(Game* game) :Actor(game)
{
	//1‚Â–Ú‚Ì”wŒi
	Actor* bgactor = new Actor(game);
	bgactor->SetPosition(Vector2::Zero);
	SpriteComponent* sc = new SpriteComponent(bgactor, 5);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Farback01.png"));
	MoveComponent* mc = new MoveComponent(bgactor);
	mc->SetVelocity(Vector2(-10.0f, 0.0f));
	mBGs.emplace_back(bgactor);

	//2‚Â–Ú‚Ì”wŒi
	bgactor = new Actor(game);
	bgactor->SetPosition(Vector2(game->mWindowWidth, 0.0f));
	sc = new SpriteComponent(bgactor, 5);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Farback02.png"));
	mc = new MoveComponent(bgactor);
	mc->SetVelocity(Vector2(-10.0f, 0.0f));
	mBGs.emplace_back(bgactor);

	//3‚Â–Ú‚Ì”wŒi
	bgactor = new Actor(game);
	bgactor->SetPosition(Vector2::Zero);
	sc = new SpriteComponent(bgactor, 10);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Stars.png"));
	mc = new MoveComponent(bgactor);
	mc->SetVelocity(Vector2(-20.0f, 0.0f));
	mBGs.emplace_back(bgactor);

	//4‚Â–Ú‚Ì”wŒi
	bgactor = new Actor(game);
	bgactor->SetPosition(Vector2(game->mWindowWidth, 0.0f));
	sc = new SpriteComponent(bgactor, 10);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Stars.png"));
	mc = new MoveComponent(bgactor);
	mc->SetVelocity(Vector2(-20.0f, 0.0f));
	mBGs.emplace_back(bgactor);
}

void BackGround::UpdateActor(float deltaTime)
{
	//ƒ‰ƒbƒsƒ“ƒOˆ—
	for (auto bg : mBGs)
	{
		if (bg->GetPosition().x < -GetGame()->mWindowWidth)
		{
			bg->SetPosition(bg->GetPosition() + 2.0f * Vector2(GetGame()->mWindowWidth, 0.0f));
		}
		else if (bg->GetPosition().x > GetGame()->mWindowWidth)
		{
			bg->SetPosition(bg->GetPosition() - 2.0f * Vector2(GetGame()->mWindowWidth, 0.0f));
		}
		if (bg->GetPosition().y < -GetGame()->mWindowHeight)
		{
			bg->SetPosition(bg->GetPosition() + 2.0f * Vector2(0.0f, GetGame()->mWindowHeight));
		}
		else if (bg->GetPosition().y > GetGame()->mWindowHeight)
		{
			bg->SetPosition(bg->GetPosition() - 2.0f * Vector2(0.0f, GetGame()->mWindowHeight));
		}
	}
}