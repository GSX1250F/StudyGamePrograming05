﻿Imports System.Drawing.Drawing2D
Imports System.Net.Mime.MediaTypeNames
Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL

Public Class SpriteComponent
    Inherits Component

    Private mTexture As Texture
    Private mTextureID As UInteger
    Private mDrawOrder As Integer
    Private mTexWidth As Integer
    Private mTexHeight As Integer
    Private mVisible As Boolean

    Sub New(ByRef owner As Actor, ByVal drawOrder As Integer)
        MyBase.New(owner, drawOrder)
        mTexture = Nothing
        mDrawOrder = drawOrder
        mTexWidth = 0
        mTexHeight = 0
        mVisible = True
        mOwner.GetGame().GetRenderer().AddSprite(Me)
    End Sub
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        If Not Me.disposed Then
            If disposing Then
                '*** アンマネージリソースの開放
            End If
            '*** マネージドリソースの開放
            mOwner.GetGame().GetRenderer().RemoveSprite(Me)
        End If
        MyBase.Dispose(disposing)
    End Sub

    Public Overridable Sub Draw()
        If (mTexture IsNot Nothing) And (mVisible = True) Then
            Dim vertices = New List(Of Vector3) From {
                    New Vector3(-0.5, -0.5, 0.0),
                    New Vector3(0.5, -0.5, 0.0),
                    New Vector3(0.5, 0.5, 0.0),
                    New Vector3(-0.5, 0.5, 0.0),
                    New Vector3(-0.5, -0.5, 0.0),
                    New Vector3(0.5, -0.5, 0.0),
                    New Vector3(0.5, 0.5, 0.0),
                    New Vector3(-0.5, 0.5, 0.0)
            }

            Dim texcoords As List(Of Vector2) = New List(Of Vector2) From {
                    New Vector2(0.0, 0.0),
                    New Vector2(1.0, 0.0),
                    New Vector2(1.0, 1.0),
                    New Vector2(0.0, 1.0),
                    New Vector2(0.0, 0.0),
                    New Vector2(1.0, 0.0),
                    New Vector2(1.0, 1.0),
                    New Vector2(0.0, 1.0)
            }

            ' テクスチャサイズで再スケーリングしたワールド変換行列を作成
            Dim scaleMat As Matrix4 = Matrix4.CreateScale(mTexWidth, mTexHeight, 1.0)
            Dim world As Matrix4 = scaleMat * mOwner.GetWorldTransform()
            Dim cameraPos = New Vector3(0.0, 0.0, 0.1)
            Dim cameraTarget = New Vector3(0.0, 0.0, 0.0)
            Dim cameraUp = Vector3.UnitY
            Dim mView As Matrix4 = Matrix4.LookAt(cameraPos, cameraTarget, cameraUp)
            Dim mProj As Matrix4 = Matrix4.CreatePerspectiveFieldOfView(MathHelper.Pi * 0.995, mOwner.GetGame.mWindowWidth / mOwner.GetGame.mWindowHeight, 0.01, 1000.0)

            ' ビューポート変換行列
            Dim viewProj = Matrix4.CreateOrthographic(mOwner.GetGame().mWindowWidth, mOwner.GetGame().mWindowHeight, 0.01, 1.0)

            mTexture.SetActive()

            'OpenGLで四角形を描画（'TriangleStripの場合、0,1,2→1つ目、1,2,3→2つ目の三角形となる。）
            GL.Begin(PrimitiveType.Quads)
            ' 各頂点を行列で変換
            For i = 0 To vertices.Count - 1
                Dim v As Vector4 = New Vector4(vertices(i).X, vertices(i).Y, vertices(i).Z, 1.0)

                v *= world * mView * mProj

                GL.TexCoord2(texcoords(i).X, texcoords(i).Y)
                GL.Vertex3(v.X, v.Y, v.Z)
            Next
            GL.End()

        End If

    End Sub

    Public Function GetDrawOrder() As Integer
        Return mDrawOrder
    End Function
    Public Function GetTexWidth() As Integer
        Return mTexWidth
    End Function
    Public Function GetTexHeight() As Integer
        Return mTexHeight
    End Function
    Public Function GetTexture() As Texture
        Return mTexture
    End Function
    Public Sub SetTexture(ByRef tex As Texture)
        mTexture = tex
        mTextureID = tex.GetTextureID()
        mTexWidth = tex.GetTexWidth()
        mTexHeight = tex.GetTexHeight()
        ' 高さと幅の平均をActorの直径とする。
        mOwner.SetRadius((mTexWidth + mTexHeight) / 4)
    End Sub
    Public Sub SetVisible(ByVal visible As Boolean)
        mVisible = visible
    End Sub
    Public Function GetVisible() As Boolean
        Return mVisible
    End Function
End Class
