# SDL-Graphics
a simple tool to test out some SDL2 things, including:

- rendering text
- moving graphics
- creating a UI with ImGui

![Screenshot](https://raw.githubusercontent.com/egrath/sdl-graphics/master/sdl-graphics-screenshot.png)

### Building
Prerequisites:
- SDL2
- SDL_image
- SDL_ttf
If the prerequisites are satisfied, run:
```
mkdir build
cd build
cmake ..
cmake --build .
```

## Special notes for users of brew on Macintosh:
```
mkdir build
cd build

export CFLAGS="-I/opt/homebrew/include"
export CXXFLAGS=$CFLAGS
export LDFLAGS="-L/opt/homebrew/lib"

cmake -DCMAKE_C_COMPILER=/opt/homebrew/bin/gcc-14 -DCMAKE_CXX_COMPILER=/opt/homebrew/bin/g++-14 ..
```

### Usage

keyboard bindings:
- q or ESC for quit
- s for toggling vertical sync
- f for toggling fullscreen

### Troubleshooting

You can test out the different video and render drivers by prepending them to the command:

```
SDL_VIDEODRIVER=x11 SDL_RENDER_DRIVER=software ./sdl-graphics
```

When running on the console without X11/Wayland with the KMSDRM driver, make sure that your user belongs to the 'input' group by running as root:
```
usermod -a -G input username
```
SDL2 uses /dev/input for accessing input devices when running with KMSDRM

