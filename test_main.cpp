#include "hge.h"
#include <iostream>

HGE *hge = nullptr;
int frames = 0;

bool FrameFunc() {
    frames++;
    std::cout << "FrameFunc called, frame count: " << frames << std::endl;
    
    // Quit after 100 frames
    if (frames > 100) {
        return true;
    }
    
    return false;
}

bool RenderFunc() {
    return false;
}

int main(int argc, char **argv) {
    hge = hgeCreate(HGE_VERSION);
    if (!hge) {
        std::cerr << "Failed to create HGE interface!" << std::endl;
        return 1;
    }
    
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
    hge->System_SetState(HGE_TITLE, "HGE macOS Test");
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_SCREENWIDTH, 800);
    hge->System_SetState(HGE_SCREENHEIGHT, 600);
    
    if (hge->System_Initiate()) {
        std::cout << "System Initiated successfully, starting loop..." << std::endl;
        hge->System_Start();
        std::cout << "System loop finished." << std::endl;
    } else {
        std::cerr << "System_Initiate failed: " << hge->System_GetErrorMessage() << std::endl;
    }
    
    hge->System_Shutdown();
    hge->Release();
    
    return 0;
}
