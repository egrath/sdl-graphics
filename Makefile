SDL_CFLAGS = $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image) 
SDL_LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image) 

sdl-graphics: sdl-graphics.o
	g++ sdl-graphics.o $(SDL_LDFLAGS) -o sdl-graphics

sdl-graphics.o: sdl-graphics.cpp
	g++ -c $(SDL_CFLAGS) sdl-graphics.cpp -o sdl-graphics.o

clean: 
		rm sdl-graphics sdl-graphics.o

