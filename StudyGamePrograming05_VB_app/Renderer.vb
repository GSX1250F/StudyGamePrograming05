Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL
Imports OpenTK.Mathematics
Imports OpenTK.Windowing.Common

Public Class Renderer
    Implements IDisposable      '明示的にクラスを開放するために必要

    'public
    Sub New(ByRef window As Game)
        mWindow = window
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

        Return True
    End Function
    Public Sub Shutdown()
        Me.Dispose()
    End Sub
    Public Sub UnloadData()
    End Sub
    Public Sub Draw()
        '背景色を指定して画面をクリア
        GL.ClearColor(0.3, 0.3, 0.3, 1.0)
        GL.Clear(ClearBufferMask.ColorBufferBit)
        'カラーバッファのアルファブレンディングを有効化
        GL.Enable(EnableCap.Blend)
        GL.BlendFunc(BlendingFactor.SrcAlpha, BlendingFactor.OneMinusSrcAlpha)

        'test





        'ダブルバッファを交換
        mWindow.SwapBuffers()
    End Sub

    Public Function GetScreenWidth() As Double
        Return mScreenWidth
    End Function
    Public Function GetScreenHeight() As Double
        Return mScreenHeight
    End Function

    'private
    Private disposedValue As Boolean
    Private mWindow As Game     'GameクラスはOpenTK.GameWindowの子クラス
    Private mScreenWidth As Integer
    Private mScreenHeight As Integer

End Class