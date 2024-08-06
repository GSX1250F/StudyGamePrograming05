#include "VertexArray.h"
#include <glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
						 const unsigned int* indices, unsigned int numIndices)
	: mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// �o�[�e�b�N�X�z��I�u�W�F�N�g��OpenGL�ɐ������A����ID�������o�[�ϐ�mVertexArray�ɕۑ�����
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// �o�[�e�b�N�X�o�b�t�@��OpenGL�ɐ������A����ID�������o�[�ϐ�mVertexBuffer�ɕۑ�����
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(
		GL_ARRAY_BUFFER,					// �o�b�t�@�̎�ނɃo�[�e�b�N�X�o�b�t�@���w��
		numVerts * 3 * sizeof(float),		//�R�s�[����o�C�g��
		verts,								//�R�s�[���̔z��
		GL_STATIC_DRAW						//���̃f�[�^��1�񂾂����[�h���Ă��̌�p�ɂɎg���Ƃ�
	);

	// �C���f�b�N�X�o�b�t�@��OpenGL�ɐ������A����ID�������o�[�ϐ�mIndexBuffer�ɕۑ�����
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			//�C���f�b�N�X�o�b�t�@�̎w��
		numIndices * sizeof(unsigned int),	//�f�[�^�̃T�C�Y
		indices,							//�R�s�[���̔z��
		GL_STATIC_DRAW						//���̃f�[�^��1�񂾂����[�h���Ă��̌�p�ɂɎg���Ƃ�
	);
	
	// �o�[�e�b�N�X�����̃��C�A�E�g���w�肷��B
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,						// �����C���f�b�N�X�i�P�ڂ̓[���j
		3,						// �v�f��
		GL_FLOAT,				// �v�f�̌^
		GL_FALSE,				// �����^�̂ݎg�p����B
		sizeof(float) * 3,		// �X�g���C�h�i�ʏ�͊e�o�[�e�b�N�X�����̃f�[�^��
		0						// ���_�f�[�^�̊J�n�ʒu���炱�̑����܂ł̃I�t�Z�b�g
	);
	
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
