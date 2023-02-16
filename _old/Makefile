#
# Makefile for SDL Graphics Demo
#
# make TARGET=linux		(default)
# make TARGET=mingw		==> build for Windows on Linux with MinGW toolchain
# make TARGET=macintosh	==> build for Mac OS (on Mac OS)
#

BUILDDIR = build
EXE      = sdl-graphics
TARGET   = linux

ifeq ($(TARGET),linux)
CXX      = g++
CXXFLAGS = $(shell /usr/local/bin/sdl2-config --cflags) $(shell pkg-config --cflags SDL2_ttf SDL2_image)
LDFLAGS  = $(shell /usr/local/bin/sdl2-config --libs) $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image) 
endif

ifeq ($(TARGET),mingw)
CXX      = x86_64-w64-mingw32-g++
CXXFLAGS = -I/usr/x86_64-w64-mingw32/include/SDL2 -Dmain=SDL_main 
LDFLAGS  = -L/usr/x86_64-w64-mingw32/lib -lSDL2_ttf -lSDL2_image -lmingw32 -lSDL2main -lSDL2 -mwindows
endif

ifeq ($(TARGET),macintosh)
FW                = /Library/Frameworks
SDL_HEADERS       = $(FW)/SDL2.framework/Headers
SDL_image_HEADERS = $(FW)/SDL2_image.framework/Headers
SDL_ttf_HEADERS   = $(FW)/SDL2_ttf.framework/Headers
CXX               = clang++
CXXFLAGS          = -std=c++11 -F$(FW) -I$(SDL_HEADERS) -I$(SDL_image_HEADERS) -I$(SDL_ttf_HEADERS)
LDFLAGS           =-F$(FW) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework SDL2 -framework SDL2_image -framework SDL2_ttf
endif

SOURCES  = sdl-graphics.cpp
SOURCES += imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp
SOURCES += imgui/imgui_widgets.cpp imgui/imgui_impl_sdl.cpp imgui/imgui_impl_sdlrenderer.cpp imgui/imgui_demo.cpp
OBJS     = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

.DEFAULT_GOAL := all

# implicit rules
$(BUILDDIR)/%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o:imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# build rules
all: $(BUILDDIR)/$(EXE) assets
	@echo $(TARGET) build complete

assets: data/sprite.png data/RobotoMono-Regular.ttf
	@echo copying data ...
	@cp $^ $(BUILDDIR)/

$(BUILDDIR)/$(EXE): $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@ 

clean:
	-rm -Rf $(BUILDDIR)
	-mkdir $(BUILDDIR)
