﻿Imports System.Runtime.InteropServices
Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL

Public Class VertexArray
    Implements IDisposable      '明示的にクラスを開放するために必要

    'public
    Public Sub New(ByVal numVerts As Integer, ByRef vertPos As Single(),
                   ByRef texPos As Single(), ByRef vertColor As Single(),
                   ByRef indices As UInteger())
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
                               3,
                               VertexAttribPointerType.Float,
                               False,
                               CInt(vertPos.Length / numVerts) * Marshal.SizeOf(Of Single),
                               0)
        GL.EnableVertexAttribArray(0)

        'VertexAttribute layout1 = texCoord
        mTexPosBuffer = GL.GenBuffer()
        GL.BindBuffer(BufferTarget.ArrayBuffer, mTexPosBuffer)
        GL.BufferData(BufferTarget.ArrayBuffer,
                      texPos.Length * Marshal.SizeOf(Of Single),
                      texPos,
                      BufferUsageHint.StaticDraw)
        GL.VertexAttribPointer(1,
                               2,
                               VertexAttribPointerType.Float,
                               False,
                               CInt(texPos.Length / numVerts) * Marshal.SizeOf(Of Single),
                               0)
        GL.EnableVertexAttribArray(1)

        'VertexAttribute layout2 = vertColor
        mVertColorBuffer = GL.GenBuffer()
        GL.BindBuffer(BufferTarget.ArrayBuffer, mVertColorBuffer)
        GL.BufferData(BufferTarget.ArrayBuffer,
                      vertColor.Length * Marshal.SizeOf(Of Single),
                      vertColor,
                      BufferUsageHint.StaticDraw)
        GL.VertexAttribPointer(2,
                               4,
                               VertexAttribPointerType.Float,
                               False,
                               CInt(vertColor.Length / numVerts) * Marshal.SizeOf(Of Single),
                               0)
        GL.EnableVertexAttribArray(2)

    End Sub
    Protected disposed = False     '開放処理が実施済みかのフラグ
    Public Overloads Sub Dispose() Implements IDisposable.Dispose
        Dispose(True)
    End Sub
    Protected Overridable Overloads Sub Dispose(ByVal disposing As Boolean)
        If Not Me.disposed Then
            If disposing Then
                '*** アンマネージリソースの開放
                GL.DeleteBuffers(1, mVertPosBuffer)
                GL.DeleteBuffers(1, mTexPosBuffer)
                GL.DeleteBuffers(1, mVertColorBuffer)
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
    Private mTexPosBuffer As Integer        ' テクスチャ座標バッファのOpenGL ID
    Private mVertColorBuffer As Integer        ' 頂点カラーバッファのOpenGL ID

End Class
