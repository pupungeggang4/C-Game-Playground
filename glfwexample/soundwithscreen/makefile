windows-msys:
	gcc main.c -o main -lOpenAL -logg -lvorbis -lvorbisfile -lglfw3 -lopengl32 -mwindows

macbrew:
	gcc main.c -o main -I/opt/homebrew/include -I/opt/homebrew/opt/openal-soft/include -L/opt/homebrew/lib -L/opt/homebrew/opt/openal-soft/lib -lOpenAL -logg -lvorbis -lvorbisfile -lglfw -framework OpenGL -w

linux:
	gcc main.c -o main -lopenal -logg -lvorbis -lvorbisfile -lglfw -lGL
