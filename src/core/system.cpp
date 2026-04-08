#include "hge_impl.h"
#include <string.h>

HGE_Impl* pHGE = nullptr;

HGE* CALL hgeCreate(int ver) {
    if (ver != HGE_VERSION) {
        return nullptr;
    }
    return HGE_Impl::_Interface_Get();
}

HGE_Impl* HGE_Impl::_Interface_Get() {
    if (!pHGE) {
        pHGE = new HGE_Impl();
    }
    return pHGE;
}

void CALL HGE_Impl::Release() {
    if (pHGE) {
        delete pHGE;
        pHGE = nullptr;
    }
}

HGE_Impl::HGE_Impl() {
    // Initialize default states
    bActive = false;
    szError[0] = 0;
    szAppPath[0] = 0;
    szIniString[0] = 0;

    procFrameFunc = nullptr;
    procRenderFunc = nullptr;
    procFocusLostFunc = nullptr;
    procFocusGainFunc = nullptr;
    procGfxRestoreFunc = nullptr;
    procExitFunc = nullptr;

    szIcon = nullptr;
    strcpy(szWinTitle, "HGE");
    nScreenWidth = 800;
    nScreenHeight = 600;
    nScreenBPP = 32;
    bWindowed = false;
    bZBuffer = false;
    bTextureFilter = true;
    szIniFile[0] = 0;
    szLogFile[0] = 0;
    bUseSound = true;
    nSampleRate = 44100;
    nFXVolume = 100;
    nMusVolume = 100;
    nStreamVolume = 100;
    nHGEFPS = HGEFPS_UNLIMITED;
    bHideMouse = true;
    bDontSuspend = false;
    hwndParent = nullptr;

    hInstance = nullptr;
    hwnd = nullptr;
}

void CALL HGE_Impl::System_SetStateBool(hgeBoolState state, bool value) {
    switch (state) {
        case HGE_WINDOWED:
            bWindowed = value;
            break;
        case HGE_ZBUFFER:
            bZBuffer = value;
            break;
        case HGE_TEXTUREFILTER:
            bTextureFilter = value;
            break;
        case HGE_USESOUND:
            bUseSound = value;
            break;
        case HGE_DONTSUSPEND:
            bDontSuspend = value;
            break;
        case HGE_HIDEMOUSE:
            bHideMouse = value;
            break;
        default:
            break;
    }
}

void CALL HGE_Impl::System_SetStateFunc(hgeFuncState state, hgeCallback value) {
    switch (state) {
        case HGE_FRAMEFUNC:
            procFrameFunc = value;
            break;
        case HGE_RENDERFUNC:
            procRenderFunc = value;
            break;
        case HGE_FOCUSLOSTFUNC:
            procFocusLostFunc = value;
            break;
        case HGE_FOCUSGAINFUNC:
            procFocusGainFunc = value;
            break;
        case HGE_GFXRESTOREFUNC:
            procGfxRestoreFunc = value;
            break;
        case HGE_EXITFUNC:
            procExitFunc = value;
            break;
        default:
            break;
    }
}

void CALL HGE_Impl::System_SetStateHwnd(hgeHwndState state, HGE_HWND value) {
    switch (state) {
        case HGE_HWNDPARENT:
            hwndParent = value;
            break;
        default:
            break;
    }
}

void CALL HGE_Impl::System_SetStateInt(hgeIntState state, int value) {
    switch (state) {
        case HGE_SCREENWIDTH:
            nScreenWidth = value;
            break;
        case HGE_SCREENHEIGHT:
            nScreenHeight = value;
            break;
        case HGE_SCREENBPP:
            nScreenBPP = value;
            break;
        case HGE_SAMPLERATE:
            nSampleRate = value;
            break;
        case HGE_FXVOLUME:
            nFXVolume = value;
            break;
        case HGE_MUSVOLUME:
            nMusVolume = value;
            break;
        case HGE_STREAMVOLUME:
            nStreamVolume = value;
            break;
        case HGE_FPS:
            nHGEFPS = value;
            break;
        default:
            break;
    }
}

void CALL HGE_Impl::System_SetStateString(hgeStringState state, const char* value) {
    switch (state) {
        case HGE_ICON:
            szIcon = value;
            break;
        case HGE_TITLE:
            if (value) strncpy(szWinTitle, value, sizeof(szWinTitle) - 1);
            break;
        case HGE_INIFILE:
            if (value)
                strncpy(szIniFile, value, sizeof(szIniFile) - 1);
            else
                szIniFile[0] = 0;
            break;
        case HGE_LOGFILE:
            if (value)
                strncpy(szLogFile, value, sizeof(szLogFile) - 1);
            else
                szLogFile[0] = 0;
            break;
        default:
            break;
    }
}

bool CALL HGE_Impl::System_GetStateBool(hgeBoolState state) {
    switch (state) {
        case HGE_WINDOWED:
            return bWindowed;
        case HGE_ZBUFFER:
            return bZBuffer;
        case HGE_TEXTUREFILTER:
            return bTextureFilter;
        case HGE_USESOUND:
            return bUseSound;
        case HGE_DONTSUSPEND:
            return bDontSuspend;
        case HGE_HIDEMOUSE:
            return bHideMouse;
        default:
            return false;
    }
}

hgeCallback CALL HGE_Impl::System_GetStateFunc(hgeFuncState state) {
    switch (state) {
        case HGE_FRAMEFUNC:
            return procFrameFunc;
        case HGE_RENDERFUNC:
            return procRenderFunc;
        case HGE_FOCUSLOSTFUNC:
            return procFocusLostFunc;
        case HGE_FOCUSGAINFUNC:
            return procFocusGainFunc;
        case HGE_GFXRESTOREFUNC:
            return procGfxRestoreFunc;
        case HGE_EXITFUNC:
            return procExitFunc;
        default:
            return nullptr;
    }
}

HGE_HWND CALL HGE_Impl::System_GetStateHwnd(hgeHwndState state) {
    switch (state) {
        case HGE_HWND_STATE:
            return hwnd;
        case HGE_HWNDPARENT:
            return hwndParent;
        default:
            return nullptr;
    }
}

int CALL HGE_Impl::System_GetStateInt(hgeIntState state) {
    switch (state) {
        case HGE_SCREENWIDTH:
            return nScreenWidth;
        case HGE_SCREENHEIGHT:
            return nScreenHeight;
        case HGE_SCREENBPP:
            return nScreenBPP;
        case HGE_SAMPLERATE:
            return nSampleRate;
        case HGE_FXVOLUME:
            return nFXVolume;
        case HGE_MUSVOLUME:
            return nMusVolume;
        case HGE_STREAMVOLUME:
            return nStreamVolume;
        case HGE_FPS:
            return nHGEFPS;
        case HGE_POWERSTATUS:
            return nPowerStatus;
        default:
            return 0;
    }
}

const char* CALL HGE_Impl::System_GetStateString(hgeStringState state) {
    switch (state) {
        case HGE_ICON:
            return szIcon;
        case HGE_TITLE:
            return szWinTitle;
        case HGE_INIFILE:
            return szIniFile[0] ? szIniFile : nullptr;
        case HGE_LOGFILE:
            return szLogFile[0] ? szLogFile : nullptr;
        default:
            return nullptr;
    }
}

char* CALL HGE_Impl::System_GetErrorMessage() {
    return szError;
}

void CALL HGE_Impl::System_Log(const char* format, ...) {
    // TODO: WIP
}

bool CALL HGE_Impl::System_Launch(const char* url) {
    // TODO: WIP
    return false;
}

void CALL HGE_Impl::System_Snapshot(const char* filename) {
    // TODO: WIP
}

void HGE_Impl::_PostError(const char* error) {
    System_Log("%s", error);
    strncpy(szError, error, sizeof(szError) - 1);
    szError[sizeof(szError) - 1] = 0;
}

#ifndef __APPLE__
// Stub implementations for non-macOS systems to allow compilation
bool CALL HGE_Impl::System_Initiate() {
    return false;
}
void CALL HGE_Impl::System_Shutdown() {}
bool CALL HGE_Impl::System_Start() {
    return false;
}
#endif
