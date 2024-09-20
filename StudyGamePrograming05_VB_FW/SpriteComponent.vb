Imports OpenTK
Imports OpenTK.Graphics
Imports OpenTK.Graphics.OpenGL

Public Class SpriteComponent
    Inherits Component
    'public
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
            Dim vertices = New List(Of Vector2) From {
                    New Vector2(-0.5, -0.5),
                    New Vector2(0.5, -0.5),
                    New Vector2(-0.5, 0.5),
                    New Vector2(0.5, 0.5)
            }

            Dim texcoords = New List(Of Vector2) From {
                    New Vector2(0.0, 0.0),
                    New Vector2(1.0, 0.0),
                    New Vector2(0.0, 1.0),
                    New Vector2(1.0, 1.0)
            }

            ' 現在のテクスチャをセット
            mTexture.SetActive()

            ' テクスチャサイズで再スケーリングしたワールド変換行列を作成
            Dim world As Matrix4 = Matrix4.CreateScale(mTexWidth, mTexHeight, 1.0)
            world *= mOwner.GetWorldTransform()

            'OpenGLで四角形を描画（'TriangleStripの場合、0,1,2→1つ目、2,1,3→2つ目の三角形となる。）
            GL.Begin(PrimitiveType.TriangleStrip)
            ' 各頂点を行列で変換
            For i = 0 To vertices.Count - 1
                Dim v = New Vector4(vertices(i).X, vertices(i).Y, 0.0, 1.0)
                v *= world
                'テクスチャ座標設定
                GL.TexCoord2(texcoords(i).X, texcoords(i).Y)

                GL.Vertex2(v.X, v.Y)
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

    'private
    Private mTexture As Texture
    Private mDrawOrder As Integer
    Private mTexWidth As Integer
    Private mTexHeight As Integer
    Private mVisible As Boolean
End Class
