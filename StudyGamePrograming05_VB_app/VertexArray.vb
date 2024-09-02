Imports System.Runtime.InteropServices
Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL

Public Class VertexArray
    Implements IDisposable      '明示的にクラスを開放するために必要

    'public
    Public Sub New(ByRef verts As Single(), ByVal numVerts As Integer,
                   ByRef indices As UInteger(), ByVal numIndices As Integer)
        mNumVerts = numVerts
        mNumIndices = numIndices

        mVertexArray = GL.GenVertexArray()
        GL.BindVertexArray(mVertexArray)

        mIndexBuffer = GL.GenBuffer()
        GL.BindBuffer(BufferTarget.ElementArrayBuffer, mIndexBuffer)
        GL.BufferData(BufferTarget.ElementArrayBuffer,
                      numIndices * Marshal.SizeOf(Of UInteger),
                      indices,
                      BufferUsageHint.StaticDraw)


        mVertexBuffer = GL.GenBuffer()
        GL.BindBuffer(BufferTarget.ArrayBuffer, mVertexBuffer)
        GL.BufferData(BufferTarget.ArrayBuffer,
                      numVerts * 5 * Marshal.SizeOf(Of Single),
                      verts,
                      BufferUsageHint.StaticDraw)



        'VertexAttribute layout0 = position
        GL.VertexAttribPointer(0,
                               3,
                               VertexAttribPointerType.Float,
                               False,
                               5 * Marshal.SizeOf(Of Single),
                               0)
        GL.EnableVertexAttribArray(0)

        'VertexAttribute layout1 = texCoord
        GL.VertexAttribPointer(1,
                               2,
                               VertexAttribPointerType.Float,
                               False,
                               5 * Marshal.SizeOf(Of Single),
                               3 * Marshal.SizeOf(Of Single))
        GL.EnableVertexAttribArray(1)

    End Sub
    Protected disposed = False     '開放処理が実施済みかのフラグ
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
        GL.BindVertexArray(mVertexArray)
    End Sub
    Public Function GetNumIndices() As Integer
        Return mNumIndices
    End Function
    Public Function GetNumVerts() As Integer
        Return mNumVerts
    End Function

    'private
    Private disposedValue As Boolean
    ' バーテックスバッファにあるバーテックス属性の数
    Private mNumVerts As Integer
    ' インデックスバッファにあるインデックスの数
    Private mNumIndices As Integer
    ' バーテックスバッファのOpenGL ID
    Private mVertexBuffer As Integer
    ' インデックスバッファのOpenGL ID
    Private mIndexBuffer As Integer
    ' バーテックス配列オブジェクトのOpenGL ID
    Private mVertexArray As Integer
End Class
