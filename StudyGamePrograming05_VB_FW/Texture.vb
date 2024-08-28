﻿Imports System.Drawing.Imaging
Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL

Public Class Texture
    Implements IDisposable      '明示的にクラスを開放するために必要
    Private disposedValue As Boolean
    Sub New()
        mTextureID = 0
        mTexWidth = 0
        mTexHeight = 0
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

    Public Function Load(ByRef filename As String) As Boolean
        Dim image As Bitmap = New Bitmap(filename)
        Dim Data As BitmapData = image.LockBits(New Rectangle(0, 0, image.Width, image.Height), ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb)
        image.UnlockBits(Data)
        'テクスチャをOpenGLに生成し、そのIDをメンバ変数mTextureIDに保存する。
        GL.GenTextures(1, mTextureID)
        GL.BindTexture(TextureTarget.Texture2D, mTextureID)
        GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, mTexWidth, mTexHeight, 0, OpenTK.Graphics.OpenGL.PixelFormat.Bgra, PixelType.UnsignedByte, Data.Scan0)
        'OpenGLに登録が完了したら画像データを開放する。
        image.Dispose()

        'バイリニアフィルタリングを有効化
        GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, Int(TextureMinFilter.Nearest))
        GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, Int(TextureMagFilter.Linear))

        Return True
    End Function
    Public Sub Unload()
        GL.DeleteTextures(1, mTextureID)
    End Sub
    Public Sub SetActive()
        GL.BindTexture(TextureTarget.Texture2D, mTextureID)
    End Sub
    Public Function GetTexWidth() As Integer
        Return mTexWidth
    End Function
    Public Function GetTexHeight() As Integer
        Return mTexHeight
    End Function

    Private mTextureID As UInteger
    Private mTexWidth As Integer
    Private mTexHeight As Integer


End Class
