Imports OpenTK.Windowing.Desktop

Public Class Game
    Inherits GameWindow
    'public
    Public Sub New(width As Integer, height As Integer, title As String)
        MyBase.New(GameWindowSettings.Default, New NativeWindowSettings())
        MyBase.ClientSize = (width, height)
        MyBase.Title = title
    End Sub
    Public Function Initialize() As Boolean
        Return True
    End Function


End Class