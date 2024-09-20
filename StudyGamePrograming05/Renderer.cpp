#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include "SpriteComponent.h"
#include <glew.h>
#include "Shader.h"
#include "VertexInfo.h"
#include "Texture.h"

Renderer::Renderer(Game* game) 
	: mGame(game)
	, mWindow(nullptr)
	, mShader(nullptr)
	, mVertexInfo(nullptr)
{}

Renderer::~Renderer()
{}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
	// OpenGL初期設定
	// OpenGLのコアプロファイルを使用
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// version 3.3を指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// 各カラーチャンネル8ビット(RGBA)
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファ有効化
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// OpenGLのハードウェアアクセラレータ使用
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// SDLウィンドウを作成
	mWindow = SDL_CreateWindow(
		"Game Programming in C++",
		100,
		100,
		static_cast<int>(screenWidth),
		static_cast<int>(screenHeight),
		SDL_WINDOW_OPENGL					//SDLウィンドウでOpenGLを使用する際に指定
	);

	if (!mWindow)
	{
		SDL_Log("ウィンドウの作成に失敗しました: %s", SDL_GetError());
		return false;
	}

	// OpenGLコンテクストを生成（すべてのOpenGL機能にアクセスする）
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEWを初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("GLEWの初期化に失敗しました。");
		return false;
	}
	glGetError();

	// バーテックス配列オブジェクトの生成
	CreateVertexInfo();

	// シェーダーの生成
	if (!LoadShaders())
	{
		SDL_Log("シェーダーの読み込みに失敗しました。");
		return false;
	}

	// 画面クリアの色を設定
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	return true;
}

void Renderer::UnloadData()
{
	mTextures.clear();
}

void Renderer::Shutdown()
{
	delete mVertexInfo;
	mShader->Unload();
	delete mShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}


void Renderer::Draw()
{
	// 画面をクリア	
	glClear(GL_COLOR_BUFFER_BIT);
	// カラーバッファのアルファブレンディングを有効化
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,				// srcFactorはsrcAlpha
		GL_ONE_MINUS_SRC_ALPHA		// dstFactorは(1-srcAlpha)
	);

	// シェーダーとバーテックス配列オブジェクトを有効化
	mVertexInfo->SetActive();
	mShader->SetActive();
	for (auto sprite : mSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(mShader);
		}
	}
	// ダブルバッファを交換
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

class Texture* Renderer::GetTexture(const std::string& filename)
{
	class Texture* tex = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(filename))
		{
			mTextures.emplace(filename, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

void Renderer::CreateVertexInfo()
{
	int numVerts = 4;			//頂点の数
	//頂点座標(vector2)
	float vertPos[] = {
		-0.5f, -0.5f, 			// 左下 (インデックス 0)
		0.5f, -0.5f, 			// 右下 (インデックス 1)
		-0.5f, 0.5f, 			// 左上 (インデックス 2) 
		0.5f, 0.5f, 			// 右上 (インデックス 3)
	};
	//テクスチャ座標(vector2)		頂点座標とは上下反転させる
	float texCoord[] = {
		0.0f, 1.0f,			//テクスチャ座標左上
		1.0f, 1.0f,			//テクスチャ座標右上
		0.0f, 0.0f,			//テクスチャ座標左下		
		1.0f, 0.0f			//テクスチャ座標右下
	};
	//頂点カラー(vector4 RGBA)
	float vertColor[] = {
		1.0f, 0.0f, 0.0f, 1.0f,		//R
		0.0f, 1.0f, 0.0f, 1.0f,		//G
		0.0f, 0.0f, 1.0f, 1.0f,		//B
		1.0f, 1.0f, 1.0f, 1.0f		//W
	};
	int numIndices = 6;			//頂点の数
	//インデックス
	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	mVertexInfo = new VertexInfo(vertPos, texCoord, vertColor, indices, numVerts, numIndices);
}

bool Renderer::LoadShaders()
{
	// シェーダーを生成
	mShader = new Shader();
	if (!mShader->Load("Shaders/shader.vert", "Shaders/shader.frag"))
	{
		return false;
	}
	mShader->SetActive();
	// ビュー変換行列を作成。ここでは平行投影変換を行う。
	//Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	Matrix4 viewProj = Matrix4::CreateOrtho(mScreenWidth, mScreenHeight, -500.0f, 500.0f);
	mShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}