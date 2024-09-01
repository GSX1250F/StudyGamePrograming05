Imports OpenTK.Windowing.Common
Imports OpenTK.Windowing.Desktop
Imports OpenTK.Windowing.GraphicsLibraryFramework
Imports System.Drawing
Imports System.Runtime.InteropServices
Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL

Public Class Game
    Inherits GameWindow
    'public
    Public Sub New(width As Integer, height As Integer, title As String)
        MyBase.New(GameWindowSettings.Default, New NativeWindowSettings())
        MyBase.ClientSize = (width, height)
        MyBase.Title = title
        mWindowWidth = width
        mWindowHeight = height
        mRenderer = Nothing
        mIsRunning = True
        mTicksCount = 0
    End Sub
    Public Function Initialize() As Boolean
        'レンダラー作成
        mRenderer = New Renderer(Me)
        If (mRenderer.Initialize(mWindowWidth, mWindowHeight)) = False Then
            mRenderer.Dispose()
        End If
        'ストップウォッチ開始
        Ticks = New Stopwatch()
        Ticks.Start()
        mTicksCount = Ticks.ElapsedMilliseconds
        Return True
    End Function

    Public Sub Shutdown()
        UnloadData()
        If mRenderer IsNot Nothing Then
            mRenderer.Shutdown()
        End If

        Ticks.Stop()
        Me.Close()
    End Sub

    Public Function GetRenderer()
        Return mRenderer
    End Function

    Public Sub SetRunning(ByVal value As Boolean)
        mIsRunning = value
    End Sub
    Public mWindowWidth As Integer
    Public mWindowHeight As Integer

    'private
    Private Sub ProcessInput()
        If (KeyboardState.IsKeyDown(Keys.Escape)) Then
            mIsRunning = False
        End If
    End Sub
    Private Sub UpdateGame()
        '前のフレームから16ms経つまで待つ
        While Ticks.ElapsedMilliseconds < mTicksCount + 16
        End While
        'デルタタイムの計算
        Dim deltaTime As Double = (Ticks.ElapsedMilliseconds - mTicksCount) / 1000

        'デルタタイムを最大値で制限する
        If deltaTime > 0.05 Then
            deltaTime = 0.05
        End If
        mTicksCount = Ticks.ElapsedMilliseconds


    End Sub
    Private Sub GenerateOutput()
        mRenderer.Draw()
    End Sub

    Private Sub LoadData()

    End Sub

    Private Sub UnloadData()
        If mRenderer IsNot Nothing Then
            mRenderer.UnloadData()
        End If
    End Sub

    Private mRenderer As Renderer
    Private Ticks As Stopwatch
    Private mTicksCount As Integer
    Private mIsRunning As Boolean


    'OpenTK original function
    Protected Overrides Sub OnLoad()        'Loadされたら呼び出される。Initializeと同等？
        MyBase.OnLoad()
    End Sub

    Protected Overrides Sub OnRenderFrame(e As FrameEventArgs)
        'フレーム毎の描画時に呼び出される。
        '特に何もしない。
        MyBase.OnRenderFrame(e)
    End Sub

    Protected Overrides Sub OnUpdateFrame(e As FrameEventArgs)
        '毎フレーム更新時に呼び出される。
        If mIsRunning Then
            ProcessInput()
            UpdateGame()
            GenerateOutput()
            MyBase.OnUpdateFrame(e)     '最後に親クラス関数呼び出し
        Else
            Shutdown()
        End If
    End Sub

    Protected Overrides Sub OnResize(e As ResizeEventArgs)
        '画面サイズ変更時に呼び出される。
        MyBase.OnResize(e)
        GL.Viewport(0, 0, Size.X, Size.Y)
    End Sub

    Protected Overrides Sub OnUnload()
        MyBase.OnUnload()
    End Sub

End Class
