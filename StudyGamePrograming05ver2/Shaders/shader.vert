#version 330

// ���͕ϐ��̐錾
layout (location = 0) in vec2 inVertPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec4 inVertColor;

// uniform�ϐ�
uniform mat4 uWorldTransform;	//���[���h�ϊ��s��
uniform mat4 uViewProj;		//�r���[�ˉe�ϊ��s��

// �o��
out vec2 fragTexCoord;		//�e�N�X�`�����W
out vec4 fragVertColor;		//���_�J���[

void main()
{
	vec4 pos = vec4(inVertPos, 0.0, 1.0);

	// ���[���h�ϊ��ƃr���[�ˉe�ϊ������s�B
	gl_Position = pos * uWorldTransform * uViewProj;

	fragTexCoord = inTexCoord;
	fragVertColor = inVertColor;
}