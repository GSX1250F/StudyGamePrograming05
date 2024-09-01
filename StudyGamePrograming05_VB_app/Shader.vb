Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL
Imports OpenTK.Mathematics
Public Class Shader
    Implements IDisposable      '明示的にクラスを開放するために必要
    'public
    Public Sub New()

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
    Public Function Load(ByRef vertName As String, ByRef fragName As String)

    End Function
    Public Sub Unload()

    End Sub
    Public Sub SetMatrixUniform(ByRef name As Char, ByRef matrix As Matrix4)

    End Sub

    'private
    Private disposedValue As Boolean
    Private Function CompileShader(ByRef fileName As String, ByVal shaderType As ShaderType, ByRef outShader As UInteger)

    End Function

End Class
