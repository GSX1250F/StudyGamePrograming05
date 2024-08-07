#include "ClearPict.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Renderer.h"

ClearPict::ClearPict(Game* game) : Actor(game)
{
	SetState(EPaused);
	SetPosition(Vector2(game->mWindowWidth * 0.5f, game->mWindowHeight * 0.5f));

	//スプライトコンポーネント作成、テクスチャ設定
	sc = new SpriteComponent(this, 100);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/ClearPict.png"));
}

void ClearPict::UpdateActor(float deltaTime)
{
	int numAsteroids = GetGame()->GetAsteroids().size();
	if (numAsteroids <= 0)
	{
		SetState(EActive);
	}
}