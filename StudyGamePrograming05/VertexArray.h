#pragma once
class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
				const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	// ���̃o�[�e�b�N�X�z����A�N�e�B�u�ɂ���i�`��ł���悤�ɂ���j
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	// �o�[�e�b�N�X�o�b�t�@�ɂ���o�[�e�b�N�X�����̐�
	unsigned int mNumVerts;
	// �C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
	unsigned int mNumIndices;
	// �o�[�e�b�N�X�o�b�t�@��OpenGL ID
	unsigned int mVertexBuffer;
	// �C���f�b�N�X�o�b�t�@��OpenGL ID
	unsigned int mIndexBuffer;
	// �o�[�e�b�N�X�z��I�u�W�F�N�g��OpenGL ID
	unsigned int mVertexArray;
};