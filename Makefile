#
# Makefile for SDL Graphics Demo Linux version
#

CFLAGS = $(shell /usr/local/bin/sdl2-config --cflags) $(shell pkg-config --cflags SDL2_ttf SDL2_image) 
LDFLAGS = $(shell /usr/local/bin/sdl2-config --libs) $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image) 

sdl-graphics: sdl-graphics.o imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_sdl.o imgui_impl_sdlrenderer.o imgui_demo.o
	g++ sdl-graphics.o imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_sdl.o imgui_impl_sdlrenderer.o imgui_demo.o $(LDFLAGS) -o sdl-graphics

sdl-graphics.o: sdl-graphics.cpp
	g++ -c $(CFLAGS) sdl-graphics.cpp -o sdl-graphics.o

imgui.o: imgui/imgui.cpp
	g++ -c $(CFLAGS) imgui/imgui.cpp -o imgui.o

imgui_draw.o: imgui/imgui_draw.cpp
	g++ -c $(CFLAGS) imgui/imgui_draw.cpp -o imgui_draw.o

imgui_tables.o: imgui/imgui_tables.cpp
	g++ -c $(CFLAGS) imgui/imgui_tables.cpp -o imgui_tables.o

imgui_widgets.o: imgui/imgui_widgets.cpp
	g++ -c $(CFLAGS) imgui/imgui_widgets.cpp -o imgui_widgets.o

imgui_impl_sdl.o: imgui/imgui_impl_sdl.cpp
	g++ -c $(CFLAGS) imgui/imgui_impl_sdl.cpp -o imgui_impl_sdl.o

imgui_impl_sdlrenderer.o: imgui/imgui_impl_sdlrenderer.cpp
	g++ -c $(CFLAGS) imgui/imgui_impl_sdlrenderer.cpp -o imgui_impl_sdlrenderer.o

imgui_demo.o: imgui/imgui_demo.cpp
	g++ -c $(CFLAGS) imgui/imgui_demo.cpp -o imgui_demo.o

clean: 
		rm sdl-graphics *.o

