#include "../../include/hge.h"
#include "hge_impl.h"

// TODO: WIP

void HGE_Impl::_UpdateMouse() {}
void HGE_Impl::_InputInit() {}
void HGE_Impl::_ClearQueue() {}
void HGE_Impl::_BuildEvent(int type, int key, int scan, int flags, int x, int y) {}

void CALL HGE_Impl::Input_GetMousePos(float *x, float *y) {}
void CALL HGE_Impl::Input_SetMousePos(float x, float y) {}
int CALL HGE_Impl::Input_GetMouseWheel() { return 0; }
bool CALL HGE_Impl::Input_IsMouseOver() { return false; }
bool CALL HGE_Impl::Input_KeyDown(int key) { return false; }
bool CALL HGE_Impl::Input_KeyUp(int key) { return false; }
bool CALL HGE_Impl::Input_GetKeyState(int key) { return false; }
char* CALL HGE_Impl::Input_GetKeyName(int key) { return nullptr; }
int CALL HGE_Impl::Input_GetKey() { return 0; }
int CALL HGE_Impl::Input_GetChar() { return 0; }
bool CALL HGE_Impl::Input_GetEvent(hgeInputEvent *event) { return false; }
