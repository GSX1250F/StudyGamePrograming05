Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL
Public Class Renderer
	Implements IDisposable      '明示的にクラスを開放するために必要
	Private disposedValue As Boolean

	Private mGame As Game
	Private mScreenWidth As Integer
	Private mScreenHeight As Integer
	Private mTextures As New Dictionary(Of String, Texture)   'テクスチャの配列
	Private mSprites As New List(Of SpriteComponent)    'スプライトコンポーネントの配列
	Private mVertsInfo As VertexInfo
	Private mShader As Shader

	Sub New(ByRef game As Game)
		mGame = game
	End Sub
	Protected disposed = False     '開放処理が実施済みかのフラグ
	Public Overloads Sub Dispose() Implements IDisposable.Dispose
		Dispose(True)
	End Sub
	Protected Overridable Overloads Sub Dispose(ByVal disposing As Boolean)
		If Not Me.disposed Then
			If disposing Then
				'*** アンマネージリソースの開放
			End If
			'*** マネージドリソースの開放
		End If
		disposed = True
	End Sub
	Protected Overrides Sub Finalize()
		MyBase.Finalize()
		Dispose(False)
	End Sub
	Public Function Initialize(ByVal screenWidth As Integer, ByVal screenHeight As Integer) As Boolean
		mScreenWidth = screenWidth
		mScreenHeight = screenHeight
		GL.Viewport(0, 0, screenWidth, screenHeight)

		InitVertsInfo()

		If (LoadShaders() <> True) Then
			Console.WriteLine("シェーダーの読み込みに失敗しました。")
			Return False
		End If

		Return True
	End Function
	Public Sub Shutdown()
		Me.Dispose()
	End Sub
	Public Sub UnloadData()
		mTextures.Clear()
	End Sub
	Public Sub Draw()
		'画面のクリア
		GL.ClearColor(0.3, 0.3, 0.3, 1.0)
		GL.Clear(ClearBufferMask.ColorBufferBit)

		mVertsInfo.SetActive()
		mShader.SetActive()

		'すべてのスプライトコンポーネントを描画
		For Each sprite In mSprites
			If sprite.GetVisible() = True Then
				sprite.Draw(mShader)
			End If
		Next
		mGame.SwapBuffers()
	End Sub
	Public Sub AddSprite(ByRef sprite As SpriteComponent)
		Dim myDrawOrder As Integer = sprite.GetDrawOrder()
		Dim cnt As Integer = mSprites.Count     '配列の要素数
		Dim iter As Integer
		If cnt > 0 Then
			For iter = 0 To mSprites.Count - 1
				If myDrawOrder < mSprites(iter).GetDrawOrder() Then
					Exit For
				End If
			Next
		End If
		mSprites.Insert(iter, sprite)
	End Sub

	Public Sub RemoveSprite(ByRef sprite As SpriteComponent)
		Dim iter As Integer = mSprites.IndexOf(sprite)
		'見つからなかったら-1が返される。
		If iter >= 0 Then
			mSprites.RemoveAt(iter)
		End If
	End Sub

	Public Function GetTexture(ByRef filename As String) As Texture
		Dim tex As Texture = Nothing
		'画像ファイルが連想配列になければ追加する。
		Dim b As Boolean = mTextures.ContainsKey(filename)
		If b = True Then
			'すでに読み込み済みなので、そのデータを返す。
			tex = mTextures(filename)
		Else
			'Textureクラスを生成し、連想配列に追加する。
			tex = New Texture()
			If (tex.Load(filename)) Then
				mTextures.Add(filename, tex)
			Else
				tex.Dispose()
				tex = Nothing
			End If
		End If
		Return tex
	End Function
	Public Function GetScreenWidth() As Single
		Return mScreenWidth
	End Function
	Public Function GetScreenHeight() As Single
		Return mScreenHeight
	End Function
	Private Sub InitVertsInfo()
		Dim numVerts As Integer = 4
		'頂点座標(vector2)
		Dim vertPos As Single() = {
			-0.5, -0.5,
			0.5, -0.5,
			-0.5, 0.5,
			0.5, 0.5
		}
		'インデックス
		Dim indices As UInteger() = {
			0, 1, 2,
			2, 1, 3
		}

		mVertsInfo = New VertexInfo(numVerts, vertPos, indices)
	End Sub
	Private Function LoadShaders() As Boolean
		' シェーダーを生成
		mShader = New Shader()
		If (mShader.Load("Shaders/shader.vert", "Shaders/shader.frag") <> True) Then
			Return False
		End If
		Return True
	End Function

End Class