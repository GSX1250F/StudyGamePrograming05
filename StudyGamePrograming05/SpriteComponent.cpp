#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder):Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
	,mVisible(true)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture && GetVisible())
	{
		SDL_Rect r;
		// �����ƕ������L�A�N�^�[�̃X�P�[���ɍ��킹��
		r.w = nearbyint(mTexWidth * mOwner->GetScale());
		r.h = nearbyint(mTexHeight * mOwner->GetScale());
		r.x = nearbyint(mOwner->GetPosition().x - r.w / 2);
		r.y = nearbyint(mOwner->GetPosition().y - r.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// �����ƕ���ݒ�
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
	// �����ƕ��̕��ς�Actor�̒��a�Ƃ���B
	mOwner->SetRadius((mTexWidth + mTexHeight) * 0.25f);
}