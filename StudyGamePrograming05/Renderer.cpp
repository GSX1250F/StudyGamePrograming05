#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include "SpriteComponent.h"
#include <glew.h>
#include "Shader.h"
#include "VertexArray.h"

Renderer::Renderer(Game* game) 
	: mGame(game)
	, mWindow(nullptr)
	, mSpriteShader(nullptr)
	, mSpriteVerts(nullptr)
{}

Renderer::~Renderer()
{}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
	// OpenGL�����ݒ�
	// OpenGL�̃R�A�v���t�@�C�����g�p
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// version 3.3���w��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// �e�J���[�`�����l��8�r�b�g(RGBA)
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// �_�u���o�b�t�@�L����
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// OpenGL�̃n�[�h�E�F�A�A�N�Z�����[�^�g�p
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// SDL�E�B���h�E���쐬
	mWindow = SDL_CreateWindow(
		"Game Programming in C++",
		100,
		100,
		static_cast<int>(screenWidth),
		static_cast<int>(screenHeight),
		SDL_WINDOW_OPENGL					//SDL�E�B���h�E��OpenGL���g�p����ۂɎw��
	);

	if (!mWindow)
	{
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s���܂���: %s", SDL_GetError());
		return false;
	}

	// SDL�����_���[���쐬
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("�����_���[�̍쐬�Ɏ��s���܂���: %s", SDL_GetError());
		return false;
	}
	
	// OpenGL�R���e�N�X�g�𐶐��i���ׂĂ�OpenGL�@�\�ɃA�N�Z�X����j
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEW��������
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("GLEW�̏������Ɏ��s���܂����B");
		return false;
	}
	glGetError();

	// �o�[�e�b�N�X�z��I�u�W�F�N�g�̐���
	InitSpriteVerts();

	// �V�F�[�_�[�̐���
	if (!LoadShaders())
	{
		SDL_Log("�V�F�[�_�[�̓ǂݍ��݂Ɏ��s���܂����B");
		return false;
	}


	return true;
}

void Renderer::UnloadData()
{
	mTextures.clear();
}

void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}


void Renderer::Draw()
{
	/* OpenGL�ł͕s�v
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// ���ׂẴX�v���C�g�R���|�[�l���g��`��
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}
	SDL_RenderPresent(mRenderer);
	*/

	// �w�i�F���w�肵�ĉ�ʂ��N���A
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// �V�F�[�_�[�ƃo�[�e�b�N�X�z��I�u�W�F�N�g��L����
	mSpriteVerts->SetActive();
	mSpriteShader->SetActive();
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}
	// �_�u���o�b�t�@������
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

SDL_Texture* Renderer::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;

	// ���łɃ��[�h�ς݂Ȃ�A���̃e�N�X�`����Ԃ��B
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// �t�@�C�����烍�[�h
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("�e�N�X�`���t�@�C���̓ǂݍ��݂Ɏ��s���܂��� %s", filename.c_str());
			return nullptr;
		}

		// �T�[�t�F�C�X����e�N�X�`�����쐬
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("�T�[�t�F�C�X����e�N�X�`���ɕϊ�����̂Ɏ��s���܂��� %s", filename.c_str());
			return nullptr;
		}

		mTextures.emplace(filename.c_str(), tex);
	}
	return tex;
}

void Renderer::InitSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.0f,			// ���� (�C���f�b�N�X 0)
		-0.5f, -0.5f, 0.0f,			// ���� (�C���f�b�N�X 1)
		0.5f, -0.5f, 0.0f,			// �E�� (�C���f�b�N�X 2)
		0.5f, 0.5f, 0.0f			// �E�� (�C���f�b�N�X 3)
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

bool Renderer::LoadShaders()
{
	// �V�F�[�_�[�𐶐�
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Transform.vert", "Shaders/Basic.frag"))
	{
		return false;
	}
	mSpriteShader->SetActive();
	// �r���[�ϊ��s����쐬�B�����ł͕��s���e�ϊ����s���B
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}