#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Shader.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	: Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
	, mVisible(true)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}
/* OpenGLでは不要
void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture && mVisible)
	{
		SDL_Rect r;
		// 高さと幅を所有アクターのスケールに合わせる
		r.w = nearbyint(mTexWidth * mOwner->GetScale());
		r.h = nearbyint(mTexHeight * mOwner->GetScale());
		r.x = nearbyint(mOwner->GetPosition().x - r.w / 2);
		r.y = nearbyint(mOwner->GetPosition().y - r.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}
*/

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture && mVisible)
	{
		// テクスチャサイズで再スケーリングしたワールド変換行列を作成
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();
		// ワールド変換
		shader->SetMatrixUniform("uWorldTransform", world);

		// 短形を描画
		glDrawElements(
			GL_TRIANGLES,		// 描画するポリゴン／プリミティブの種類
			6,					// インデックスバッファにあるインデックスの数
			GL_UNSIGNED_INT,	// インデックスの型
			nullptr				// 通常はnullptr
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// 高さと幅を設定
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
	// 高さと幅の平均をActorの直径とする。
	mOwner->SetRadius((mTexWidth + mTexHeight) * 0.25f);
}