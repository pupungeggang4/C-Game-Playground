windows-msys2:
	clang main.c -o main -lglfw3 -lopengl32 -lpng

macbrew:
	clang main.c -o main.out -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -lpng -framework OpenGL -w

linux:
	clang main.c -o main.out -lglfw -lGL -lm -lpng
