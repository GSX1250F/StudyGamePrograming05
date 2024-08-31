Imports System
Imports OpenTK.Windowing.Desktop

Module Program

    Sub Main(args As String())
        Using game As Game = New Game(1024, 768, "OpenTK not using glControl VB")
            game.Run()
        End Using
    End Sub
End Module
