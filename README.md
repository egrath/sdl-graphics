# SDL-Graphics
a simple tool to test out some SDL2 things, including:

- rendering text
- moving graphics

![Screenshot](https://raw.githubusercontent.com/egrath/sdl-graphics/master/sdl-graphics-screenshot.png)

### Usage

keyboard bindings:
- q or ESC for quit
- s for toggling vertical sync
- f for toggling fullscreen

### Troubleshooting

You can test out the different video and render drivers by prepending them to the command:

```
SDL_VIDEODRIVER=x11 SDL_RENDER_DRIVER=software ./sdl-test
```

When running on the console without X11/Wayland with the KMSDRM driver, make sure that your user belongs to the 'input' group by running as root:
```
usermod -a -G input username
```
SDL2 uses /dev/input for accessing input devices when running with KMSDRM

