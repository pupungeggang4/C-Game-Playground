windows-msys:
	gcc main.c -o main -lSDL3 -lopengl32 -mwindows

macbrew:
	gcc main.c -o main.out -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL3 -framework OpenGL

linux:
	gcc main.c -o main.out -lSDL3 -lGL

linux-custom:
	gcc main.c -o main.out -I$(SDL_PATH)/SDL/include -L$(SDL_PATH)/SDL/build -Wl,-rpath=$(SDL_PATH)/SDL/build -lSDL3 -lGL

linuxbrew:
	gcc main.c -o main.out -I/home/linuxbrew/.linuxbrew/include -L/home/linuxbrew/.linuxbrew/lib -lSDL3 -lGL

linuxbrew-custom:
	gcc main.c -o main.out -I/home/linuxbrew/.linuxbrew/include -L/home/linuxbrew/.linuxbrew/lib -I$(SDL_PATH)/SDL/include -L$(SDL_PATH)/SDL/build -Wl,-rpath=$(SDL_PATH)/SDL/build -lSDL3 -lGL

dummy:
