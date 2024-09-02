Imports OpenTK
Imports System.Security.Cryptography
Public Class Asteroid
	Inherits Actor

	Private mCircle As CircleComponent
	Private mAsteroidCooldown As Double
	Private mChunkFile As String

	Sub New(ByRef game As Game)
		MyBase.New(game)

		'ランダムな位置と向きと大きさと初速で初期化
		Dim randPos As Vector2

		Dim rng As RandomNumberGenerator = RandomNumberGenerator.Create()   '乱数生成器クラスを生成
		Dim bs(1) As Byte   'バイト型乱数を格納する配列。２つ分。
		randPos.X = 0.0
		randPos.Y = 0.0
		'画面の中央3/5区画以外になるまで繰り返し処理
		While (randPos.X > GetGame().mWindowWidth * (-0.3)) And
			  (randPos.X < GetGame().mWindowWidth * 0.3) And
			  (randPos.Y > GetGame().mWindowHeight * (-0.3)) And
			  (randPos.Y < GetGame().mWindowHeight * 0.3)
			rng.GetBytes(bs)    '乱数生成。0以上255以下
			randPos.X = bs(0) / 255 * GetGame().mWindowWidth - 0.5 * GetGame().mWindowWidth
			randPos.Y = bs(1) / 255 * GetGame().mWindowHeight - 0.5 * GetGame().mWindowHeight
		End While
		SetPosition(randPos)
		rng.GetBytes(bs)    '乱数生成
		SetRotation(bs(0) / 255 * Math.PI * 2)
		SetScale(bs(1) / 255 * (2.5 - 0.8) + 0.8)   '拡大率 0.8～2.5

		'スプライトコンポーネント作成、テクスチャ設定
		Dim sc As New SpriteComponent(Me, 40)
		sc.SetTexture(game.GetRenderer().GetTexture("Assets\Asteroid.png"))

		'MoveComponent作成
		Dim mc As New MoveComponent(Me, 10)
		rng.GetBytes(bs)    '乱数生成
		mc.SetVelocity(GetForward() * (bs(0) / 255 * (200 - 50) + 50))  '速さ50～200
		mc.SetRotSpeed((bs(1) / 255 * 2.0 * Math.PI) - Math.PI) '角速度-π～π

		rng.Dispose()   '乱数生成器の開放

		'CircleComponent作成
		mCircle = New CircleComponent(Me, 10)

		mChunkFile = "Assets/destroy.mp3"
		game.GetSoundPlayer().AddChunk(mChunkFile)

	End Sub

	Protected Overrides Sub Dispose(ByVal disposing As Boolean)
		If Not Me.disposed Then
			If disposing Then
				'*** アンマネージリソースの開放
			End If
			'*** マネージドリソースの開放
			GetGame().GetSoundPlayer().SetChunkControl(mChunkFile, "replay")
			GetGame().RemoveAsteroid(Me)
		End If
		MyBase.Dispose(disposing)
	End Sub

	Public Overrides Sub UpdateActor(ByVal detaTime As Double)
		'画面外にでたら反対の位置に移動（ラッピング処理）
		If (GetPosition().X < GetGame().mWindowWidth * (-0.5) - GetRadius() Or
			GetPosition().X > GetGame().mWindowWidth * 0.5 + GetRadius()) _
			   Then
			Dim v As Vector2
			v.X = -GetPosition().X
			v.Y = GetPosition().Y
			SetPosition(v)
		End If

		If (GetPosition().Y < GetGame().mWindowHeight * (-0.5) - GetRadius() Or
			GetPosition().Y > GetGame().mWindowHeight * 0.5 + GetRadius()) _
			Then
			Dim v As Vector2
			v.X = GetPosition().X
			v.Y = -GetPosition().Y
			SetPosition(v)
		End If

	End Sub

	Public Function GetCircle() As CircleComponent
		Return mCircle
	End Function
End Class
