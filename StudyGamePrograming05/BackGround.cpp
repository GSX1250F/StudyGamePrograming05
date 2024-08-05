#include "BackGround.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"

BackGround::BackGround(Game* game) :Actor(game)
{
	//1‚Â–Ú‚Ì”wŒi
	Actor* bgactor = new Actor(game);
	bgactor->SetPosition(Vector2(0.0f, game->mWindowHeight * 0.5f));
	SpriteComponent* sc = new SpriteComponent(bgactor, 5);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Farback01.png"));
	MoveComponent* mc = new MoveComponent(bgactor);
	mc->SetVelocity(Vector2(-10.0f, 0.0f));
	mBGs.emplace_back(bgactor);

	//2‚Â–Ú‚Ì”wŒi
	bgactor = new Actor(game);
	bgactor->SetPosition(Vector2(game->mWindowWidth, game->mWindowHeight * 0.5f));
	sc = new SpriteComponent(bgactor, 5);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Farback02.png"));
	mc = new MoveComponent(bgactor);
	mc->SetVelocity(Vector2(-10.0f, 0.0f));
	mBGs.emplace_back(bgactor);

	//3‚Â–Ú‚Ì”wŒi
	bgactor = new Actor(game);
	bgactor->SetPosition(Vector2(0.0f, game->mWindowHeight * 0.5f));
	sc = new SpriteComponent(bgactor, 10);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Stars.png"));
	mc = new MoveComponent(bgactor);
	mc->SetVelocity(Vector2(-20.0f, 0.0f));
	mBGs.emplace_back(bgactor);

	//4‚Â–Ú‚Ì”wŒi
	bgactor = new Actor(game);
	bgactor->SetPosition(Vector2(game->mWindowWidth, game->mWindowHeight * 0.5f));
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
		if (bg->GetPosition().x < GetGame()->mWindowWidth * (-0.5f))
		{
			bg->SetPosition(bg->GetPosition() + Vector2(2.0f * GetGame()->mWindowWidth, 0.0f));
		}
		else if (bg->GetPosition().x > GetGame()->mWindowWidth * 1.5f)
		{
			bg->SetPosition(bg->GetPosition() - Vector2(2.0f * GetGame()->mWindowWidth, 0.0f));
		}
		if (bg->GetPosition().y < GetGame()->mWindowHeight * (-0.5f))
		{
			bg->SetPosition(bg->GetPosition() + Vector2(0.0f, 2.0f * GetGame()->mWindowHeight));
		}
		else if (bg->GetPosition().y > GetGame()->mWindowHeight * 1.5f)
		{
			bg->SetPosition(bg->GetPosition() - Vector2(0.0f, 2.0f * GetGame()->mWindowHeight));
		}
	}
}