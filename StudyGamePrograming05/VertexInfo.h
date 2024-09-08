#pragma once
class VertexInfo
{
public:
	VertexInfo(unsigned int numVerts, const float* vertPos, const float* texCoord,
			   const float* vertColor, const unsigned int* indices);
	~VertexInfo();

	// ���̃o�[�e�b�N�X�z����A�N�e�B�u�ɂ���i�`��ł���悤�ɂ���j
	void SetActive();

	unsigned int GetNumVerts() const { return mNumVerts; }

private:	
	unsigned int mNumVerts;			// ���_�̐�
	unsigned int mVertexArray;		// �o�[�e�b�N�X�z��I�u�W�F�N�g��OpenGL ID
	unsigned int mIndexBuffer;		// �C���f�b�N�X�o�b�t�@��OpenGL ID	
	unsigned int mVertPosBuffer;	// ���_���W�o�b�t�@��OpenGL ID
	unsigned int mTexCoordBuffer;	// �e�N�X�`�����W�o�b�t�@��OpenGL ID
	unsigned int mVertColorBuffer;	// ���_�J���[�o�b�t�@��OpenGL ID	
	
	
};