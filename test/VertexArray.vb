Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL
Public Class VertexArray
    Implements IDisposable

    'public
    Public Sub New()

    End Sub
    Protected disposed = False
    Public Overloads Sub Dispose() Implements IDisposable.Dispose
        Dispose(True)
    End Sub
    Protected Overridable Overloads Sub Dispose(ByVal disposing As Boolean)
        If Not Me.disposed Then
            If disposing Then
                '*** アンマネージリソースの開放
                GL.DeleteBuffers(1, mVertexBuffer)
                GL.DeleteBuffers(1, mIndexBuffer)
                GL.DeleteVertexArrays(1, mVertexArray)
            End If
            '*** マネージドリソースの開放
        End If
        disposed = True
    End Sub
    Protected Overrides Sub Finalize()
        MyBase.Finalize()
        Dispose(False)
    End Sub
    Public Sub SetActive()

    End Sub

    'private
    Private disposedValue As Boolean

    Private mNumVerts As Integer        ' バーテックスバッファにあるバーテックス属性の数

    Private mNumIndices As Integer      ' インデックスバッファにあるインデックスの数

    Private mVertexBuffer As Integer    ' バーテックスバッファのOpenGL ID
    ' インデックスバッファのOpenGL ID
    Private mIndexBuffer As Integer
    ' バーテックス配列オブジェクトのOpenGL ID
    Private mVertexArray As Integer
End Class
