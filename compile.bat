cls

@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/main.cc -I ../../Prog/ESAT_rev109/include
@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/MathLib.cc -I ../../Prog/ESAT_rev109/include
@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Misc.cc -I ../../Prog/ESAT_rev109/include
@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Button.cc -I ../../Prog/ESAT_rev109/include
@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Physics.cc -I ../../Prog/ESAT_rev109/include
@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Level.cc -I ../../Prog/ESAT_rev109/include

@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Screens/Screen.cc -I ../../Prog/ESAT_rev109/include
@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Screens/Game.cc -I ../../Prog/ESAT_rev109/include

@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Pieces/Piece.cc -I ../../Prog/ESAT_rev109/include
@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Pieces/SmallRamp.cc -I ../../Prog/ESAT_rev109/include
@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Pieces/LargeRamp.cc -I ../../Prog/ESAT_rev109/include

@cl /nologo /Zi /GR- /EHs /MDd /c /D WIN32 src/Manager.cc -I ../../Prog/ESAT_rev109/include

@cl /nologo /Zi /GR- /EHs /MDd /Fe:gravity.exe main.obj MathLib.obj Misc.obj Button.obj Physics.obj Level.obj Screen.obj Game.obj Piece.obj SmallRamp.obj LargeRamp.obj Manager.obj ..\..\Prog\ESAT_rev109\bin\ESAT_d.lib opengl32.lib user32.lib gdi32.lib shell32.lib
