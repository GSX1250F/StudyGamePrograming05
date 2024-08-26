Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL
Public Class Renderer
	Implements IDisposable      '明示的にクラスを開放するために必要
	Private disposedValue As Boolean

	Private mGame As Game
	Private mWindow As GLControl
	Private mScreenWidth As Integer
	Private mScreenHeight As Integer
	Private mTextures As New Dictionary(Of String, Image)   'テクスチャの配列
	Private mSprites As New List(Of SpriteComponent)    'スプライトコンポーネントの配列

	Sub New(ByRef game As Game)
		mGame = game
		mWindow = Nothing
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
		mWindow = mGame.GetGLControl()
		' 背景色の設定
		GL.ClearColor(0.3, 0.3, 0.3, 1.0)
		' 画面初期化
		GL.Viewport(0, 0, 1024, 768)

		AddHandler mWindow.Paint, AddressOf mWindow_Paint

		Return True
	End Function
	Public Sub Shutdown()
		mWindow.Dispose()
		Me.Dispose()
	End Sub
	Public Sub UnloadData()
		mTextures.Clear()
	End Sub
	Public Sub Draw()
		'画面のクリア
		mGraphics.Clear(Color.Gray)

		'すべてのスプライトコンポーネントを描画
		For Each sprite In mSprites
			If sprite.GetVisible() = True Then
				sprite.Draw(mGraphics)
			End If
		Next
		mGame.GetPictureBox().Image = mWindow
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

	Public Function GetTexture(ByRef filename As String) As Image
		Dim tex As System.Drawing.Image = Nothing
		Dim b As Boolean = mTextures.ContainsKey(filename)
		If b = True Then
			'すでに読み込み済み
			tex = mTextures(filename)
		Else
			'画像ファイルを読み込んで、Imageオブジェクトを作成し、ファイル名と紐づけする
			tex = Image.FromFile(Application.StartupPath & filename)
			mTextures.Add(filename, tex)
		End If
		Return tex
	End Function
	Public Function GetScreenWidth() As Double
		Return mScreenWidth
	End Function
	Public Function GetScreenHeight() As Double
		Return mScreenHeight
	End Function

	Private Sub mWindow_Paint(sender As Object, e As PaintEventArgs)

		' 背景色でクリア
		GL.Clear(ClearBufferMask.ColorBufferBit)

		mWindow.SwapBuffers()
	End Sub


End Class