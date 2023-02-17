#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer.h>

int fps = 0;
char *fpsText = nullptr;
const char *videoDriverText;
const char *renderDriverText;
TTF_Font *font;

const char *applicationName = "SDL-Graphics";

Uint32 TimerCallback(Uint32 interval, void *parameter)
{
    if(fpsText==nullptr)
        fpsText = new char[100];

    sprintf(fpsText, "FPS: %d", fps);
    fps=0;

    return interval;
}

// This is a expensive and unoptimized function!
// CURRENTLY UNUSED AFTER INTEGRATING IMGUI
void drawText(int x, int y, const char *text, SDL_Renderer *renderer)
{    
    // Render information about how many FPS we have
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);        
        
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect targetRect = { x, y, textWidth, textHeight };
    SDL_RenderCopy(renderer, textTexture, nullptr, &targetRect);
        
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);     
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    TTF_Init();
    font = TTF_OpenFont("RobotoMono-Regular.ttf", 20);
    if(font==nullptr)
    {
        std::cerr << TTF_GetError();
        return -1;
    }

    // Resolution 640x480 per default for windows and fullscreen native for KMSDRM
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0,&displayMode);

    SDL_Window *window = nullptr;
    SDL_WindowFlags windowFlags = (SDL_WindowFlags) (SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);    
    if(strcmp(SDL_GetCurrentVideoDriver(),"KMSDRM")==0)
        window = SDL_CreateWindow(applicationName, 0, 0, displayMode.w, displayMode.h, windowFlags);            
    else
        window = SDL_CreateWindow(applicationName, 0, 0, 800, 600, windowFlags | SDL_WINDOW_RESIZABLE);    

    if(window==nullptr)
    {
        std::cerr << SDL_GetError();
        return -1;
    }    
    
    // Set Window size to something reasonable
    SDL_SetWindowPosition(window, 100, 100);

    // Get size of created window
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Create the renderer (SDL_RENDER_DRIVER)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer==nullptr)
    {
        std::cerr << SDL_GetError();
        return -1;
    }
    
    //SDL_ShowCursor(0);   
    SDL_ShowCursor(1);

    // Get information about the available video drivers and rendererss
    std::cout << "available drivers (compiled in):" << std::endl;
    std::cout << "    SDL_VIDEODRIVER  : ";
    for(int i=0;i<SDL_GetNumVideoDrivers();i++)
    {
        std::cout << SDL_GetVideoDriver(i) << " ";        
    }    
    std::cout << std::endl;
    std::cout << "    SDL_RENDER_DRIVER: ";
    for(int i=0;i<SDL_GetNumRenderDrivers();i++)
    {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i,&info);
        std::cout << info.name << " ";
    }
    std::cout << std::endl;

    // Get information about the currently used video driver and renderer
    videoDriverText = SDL_GetCurrentVideoDriver();
    std::cout << "selected drivers:" << std::endl;    
    std::cout << "    SDL_VIDEODRIVER  : " << videoDriverText << std::endl;
    SDL_RendererInfo rendererInfo;
    SDL_GetRendererInfo(renderer,&rendererInfo);
    renderDriverText = rendererInfo.name;
    std::cout << "    SDL_RENDER_DRIVER: " << renderDriverText << std::endl;    
    std::cout << std::flush;

    // Initialize IMGUI
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);    
    ImGuiIO &io=ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("RobotoMono-Regular.ttf", 18.0f);

    // Timer for updating the FPS display    
    SDL_AddTimer(1000, TimerCallback, nullptr);

    // Load the sprite
    SDL_Texture *spriteTexture = IMG_LoadTexture(renderer, "sprite.png");
    int spriteWidth = 0, spriteHeight = 0;
    if(spriteTexture==nullptr)
    {
        std::cerr << IMG_GetError() << std::endl;
        return -1;
    }
    else
        SDL_QueryTexture(spriteTexture, nullptr, nullptr, &spriteWidth, &spriteHeight);
    SDL_Rect spriteTargetRect = { 100, 100, spriteWidth, spriteHeight };
    int spriteMoveX = 1, spriteMoveY = 1;

    // Enable vsync
    bool vsync=true;
    SDL_GL_SetSwapInterval(vsync);

    // Enable windows mode per default
    bool fullscreen=false;
    SDL_SetWindowFullscreen(window,(fullscreen ? SDL_WINDOW_FULLSCREEN : 0));

    int cursorX, cursorY;

    // Rendering loop
    bool run = true;
    while(run)
    {
        // Process events
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);

            switch(event.type)
            {
                case SDL_MOUSEMOTION:
                    cursorX=event.motion.x;
                    cursorY=event.motion.y;
                    break;

                case SDL_WINDOWEVENT:
                    switch(event.window.event)
                    {
                        case SDL_WINDOWEVENT_RESIZED:
                            windowWidth=event.window.data1;
                            windowHeight=event.window.data2;
                            break;
                    }
                    break;

                case SDL_QUIT:
                    run=false;
                    break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_q)
                        run=false;                        
                    break;

                case SDL_KEYUP:
                    if(event.key.keysym.sym==SDLK_s)
                    {
                        vsync = !vsync;
                        std::cout << "VSync: " << (vsync ? "Enabled" : "Disabled") << std::endl;
                        SDL_GL_SetSwapInterval(vsync);
                    }
                    else if(event.key.keysym.sym==SDLK_f)
                    {
                        fullscreen = !fullscreen;
                        SDL_SetWindowFullscreen(window,(fullscreen ? SDL_WINDOW_FULLSCREEN : 0));                        
                    }
                    break;
                
                
                default:
                break;
            }
        }
        
        // Do some rendering
        SDL_SetRenderDrawColor(renderer, 64, 64, 64, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        // Moving sprite
        if(spriteTargetRect.x==(windowWidth-spriteWidth))
            spriteMoveX=-1;
        else if(spriteTargetRect.x==0)
            spriteMoveX=1;

        if(spriteTargetRect.y==(windowHeight-spriteHeight))
            spriteMoveY=-1;
        else if(spriteTargetRect.y==0)
            spriteMoveY=1;

        spriteTargetRect.x += spriteMoveX;
        spriteTargetRect.y += spriteMoveY;

        SDL_RenderCopy(renderer, spriteTexture, nullptr, &spriteTargetRect);

        // Draw our cursor
        //SDL_SetRenderDrawColor(renderer, 255, 48, 48, SDL_ALPHA_OPAQUE);
        //SDL_RenderDrawLine(renderer,cursorX-20,cursorY,cursorX+20,cursorY);
        //SDL_RenderDrawLine(renderer,cursorX, cursorY-20, cursorX, cursorY+20);

        // Draw ImGui
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // First Window
        ImGui::Begin(applicationName);
            if(fpsText!=nullptr && strlen(fpsText)>0)
                ImGui::Text("%s",fpsText);
            if(ImGui::Button("Quit"))
                run=false;
            ImGui::SetWindowSize(ImVec2(160,120));
        ImGui::End();

        // Second Window
        //ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

        // Make the buffer current
        SDL_RenderPresent(renderer);

        // FPS counter, will reset every second after being displayed
        fps++;
    }

    // Clean up and exit gracefully
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);  

    TTF_CloseFont(font);
    TTF_Quit();  
    SDL_Quit();

    return 0;
}
