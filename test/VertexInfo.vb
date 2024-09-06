Imports System.Runtime.InteropServices
Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL
Public Class VertexInfo
    Implements IDisposable

    'public
    Public Sub New(ByVal numVerts As Integer, ByRef vertPos As Single(), ByRef indices As UInteger())
        mNumVerts = numVerts

        mVertexArray = GL.GenVertexArray()
        GL.BindVertexArray(mVertexArray)

        mIndexBuffer = GL.GenBuffer()
        GL.BindBuffer(BufferTarget.ElementArrayBuffer, mIndexBuffer)
        GL.BufferData(BufferTarget.ElementArrayBuffer,
                      indices.Length * Marshal.SizeOf(Of UInteger),
                      indices,
                      BufferUsageHint.StaticDraw)

        'VertexAttribute layout0 = position
        mVertPosBuffer = GL.GenBuffer()
        GL.BindBuffer(BufferTarget.ArrayBuffer, mVertPosBuffer)
        GL.BufferData(BufferTarget.ArrayBuffer,
                      vertPos.Length * Marshal.SizeOf(Of Single),
                      vertPos,
                      BufferUsageHint.StaticDraw)
        GL.VertexAttribPointer(0,
                               2,
                               VertexAttribPointerType.Float,
                               False,
                               CInt(vertPos.Length / numVerts) * Marshal.SizeOf(Of Single),
                               0)
        GL.EnableVertexAttribArray(0)



    End Sub
    Protected disposed = False
    Public Overloads Sub Dispose() Implements IDisposable.Dispose
        Dispose(True)
    End Sub
    Protected Overridable Overloads Sub Dispose(ByVal disposing As Boolean)
        If Not Me.disposed Then
            If disposing Then
                '*** アンマネージリソースの開放
                GL.DeleteBuffers(1, mVertPosBuffer)
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
        GL.BindVertexArray(mVertexArray)
    End Sub
    Public Function GetNumVerts() As Integer
        Return mNumVerts
    End Function


    'private
    Private disposedValue As Boolean
    Private mNumVerts As Integer    ' 頂点の数
    Private mVertexArray As Integer         ' バーテックス配列オブジェクトのOpenGL ID
    Private mIndexBuffer As Integer         ' インデックスバッファのOpenGL ID
    Private mVertPosBuffer As Integer        ' 頂点座標バッファのOpenGL ID
End Class
