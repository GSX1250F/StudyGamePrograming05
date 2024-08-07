#pragma once
#include "Component.h"
#include <SDL.h>

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	//virtual void Draw(SDL_Renderer* renderer);		// �ύX
	virtual void Draw(class Shader* shader);
	
	virtual void SetTexture(SDL_Texture* texture);
	SDL_Texture* GetTexture() const { return mTexture; }

	int GetDrawOrder() const { return mDrawOrder; }
	void SetTexWidth(int width) { mTexWidth = width; }
	int GetTexWidth() const { return mTexWidth; }
	void SetTexHeight(int height) { mTexHeight = height; }
	int GetTexHeight() const { return mTexHeight; }
	
private:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};