// OpenGL3.3�ɑΉ�����GLSL�o�[�W�����̎w��

#version 330

// ���͕ϐ��̐錾�i�o�[�e�b�N�X���W�ƃe�N�X�`�����W�j
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;

// uniform�ϐ��̐錾(const�ϐ��ƈӖ��͋߂��H)
uniform mat4 uWorldTransform;	//���[���h�ϊ��s��
uniform mat4 uViewProj;		//�r���[�ˉe�ϊ��s��

// �o�͂Ƀe�N�X�`�����W��ǉ�
out vec2 fragTexCoord;

void main()
{
	// 3�����̓��͕ϐ���4�����ɕϊ�����
	vec4 pos = vec4(inPosition, 1.0);

	// ���[���h�ϊ��ƃr���[�ˉe�ϊ������s�B
	// �s�x�N�g���̏ꍇ�́A���̍s�x�N�g���~���[���h�ϊ��s��~�r���[�ˉe�ϊ��s��
	gl_Position = pos * uWorldTransform * uViewProj;

	// �e�N�X�`�����W���t���O�����g�V�F�[�_�[�ɓn��
	fragTexCoord = inTexCoord;
}