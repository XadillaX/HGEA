#include "hge.h"
#include <iostream>

HGE *hge = nullptr;

bool FrameFunc() {
    static int frames = 0;
    frames++;
    
    // Get delta time and FPS
    float dt = hge->Timer_GetDelta();
    int fps = hge->Timer_GetFPS();

    // Get mouse position
    float mx, my;
    hge->Input_GetMousePos(&mx, &my);

    // Print some debug info every second or so
    static float timer = 0.0f;
    timer += dt;
    if (timer >= 1.0f) {
        std::cout << "FPS: " << fps << " | Mouse: (" << mx << ", " << my << ")" << std::endl;
        timer = 0.0f;
    }

    // Quit after some frames since ESC won't work yet
    if (frames > 1000) {
        return true;
    }

    return false; // continue running
}

bool RenderFunc() {
    // Currently graphics module is WIP, so we just clear and return
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(ARGB(255, 0, 0, 0));
    hge->Gfx_EndScene();
    return false;
}

int main(int argc, char **argv) {
    hge = hgeCreate(HGE_VERSION);
    if (!hge) {
        std::cerr << "Failed to create HGE interface!" << std::endl;
        return 1;
    }
    
    // Set HGE callbacks
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
    
    // Set window properties
    hge->System_SetState(HGE_TITLE, "HGE macOS Basic Example");
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_SCREENWIDTH, 800);
    hge->System_SetState(HGE_SCREENHEIGHT, 600);
    hge->System_SetState(HGE_FPS, 60); // limit to 60 fps
    
    // Initiate and start the engine
    if (hge->System_Initiate()) {
        std::cout << "HGE successfully initialized. Press ESC to exit." << std::endl;
        hge->System_Start();
        std::cout << "HGE main loop finished." << std::endl;
    } else {
        std::cerr << "System_Initiate failed: " << hge->System_GetErrorMessage() << std::endl;
    }
    
    // Clean up
    hge->System_Shutdown();
    hge->Release();
    
    return 0;
}
