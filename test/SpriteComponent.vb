Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL
Imports OpenTK.Mathematics

Public Class SpriteComponent
    Inherits Component

    Private mTexture As Texture
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

    Public Overridable Sub Draw(ByRef shader As Shader)
        If (mTexture IsNot Nothing) And (mVisible = True) Then
            Dim scaleMat As Matrix4 = Matrix4.CreateScale(mTexture.GetTexWidth, mTexture.GetTexHeight, 1.0)
            Dim world As Matrix4 = scaleMat * mOwner.GetWOrldTransform()
            shader.SetMatrixUniform("uWorldTransform", world)
            Dim viewProj As Matrix4 = Matrix4.CreateScale(2.0 / mOwner.GetGame().mWindowWidth, 2.0 / mOwner.GetGame.mWindowHeight, 1.0)
            shader.SetMatrixUniform("uViewProj", viewProj)

            mTexture.SetActive()
            GL.DrawElements(PrimitiveType.Triangles,
                            6,
                            DrawElementsType.UnsignedInt,
                            0)

        End If

    End Sub
    Public Sub SetTexture(ByRef tex As Texture)
        mTexture = tex
        mTexWidth = tex.GetTexWidth
        mTexHeight = tex.GetTexHeight
        ' 高さと幅の平均をActorの直径とする。
        mOwner.SetRadius((mTexWidth + mTexHeight) / 4)
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
    Public Sub SetVisible(ByVal visible As Boolean)
        mVisible = visible
    End Sub
    Public Function GetVisible() As Boolean
        Return mVisible
    End Function
End Class
