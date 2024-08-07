// OpenGL3.3�ɑΉ�����GLSL�o�[�W�����̎w��

#version 330

// ���͕ϐ��i�R�����j�̈ʒu���̐錾
in vec3 inPosition;

// uniform�ϐ��̐錾(const�ϐ��ƈӖ��͋߂��H)
uniform mat4 uWorldTransform;	//���[���h�ϊ��s��
uniform mat4 uViewProj;		//�r���[�ˉe�ϊ��s��

void main()
{
	// 3�����̓��͕ϐ���4�����ɕϊ�����
	vec4 pos = vec4(inPosition, 1.0);

	// ���[���h�ϊ��ƃr���[�ˉe�ϊ������s�B
	// �s�x�N�g���̏ꍇ�́A���̍s�x�N�g���~���[���h�ϊ��s��~�r���[�ˉe�ϊ��s��
	// ���c�x�N�g���̏ꍇ�́A�r���[�ˉe�ϊ��s��~���[���h�ϊ��s��~���̏c�x�N�g��
	gl_Position = pos * uWorldTransform * uViewProj;
}