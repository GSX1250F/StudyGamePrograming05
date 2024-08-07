// OpenGL3.3に対応するGLSLバージョンの指定

#version 330

// 入力変数（３次元）の位置情報の宣言
in vec3 inPosition;

// uniform変数の宣言(const変数と意味は近い？)
uniform mat4 uWorldTransform;	//ワールド変換行列
uniform mat4 uViewProj;		//ビュー射影変換行列

void main()
{
	// 3次元の入力変数を4次元に変換する
	vec4 pos = vec4(inPosition, 1.0);

	// ワールド変換とビュー射影変換を実行。
	// 行ベクトルの場合は、元の行ベクトル×ワールド変換行列×ビュー射影変換行列
	// ※縦ベクトルの場合は、ビュー射影変換行列×ワールド変換行列×元の縦ベクトル
	gl_Position = pos * uWorldTransform * uViewProj;
}