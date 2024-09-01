// GLSL3.3��v��
#version 330 core

// �J���[�o�b�t�@�ւ̏o�͐F
out vec4 outColor;

// �e�N�X�`�����W���o�[�e�b�N�X�V�F�[�_�[����󂯎��
in vec2 fragTexCoord;

// �e�N�X�`�����W�ɂ��������ăe�N�X�`������F���擾����T���v�����O�p�ϐ�
uniform sampler2D uTexture;

void main()
{
	// �e�N�X�`������F���T���v�����O����
	outColor = texture(uTexture, fragTexCoord);
}