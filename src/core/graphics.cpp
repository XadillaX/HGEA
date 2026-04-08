#include "hge_impl.h"

// TODO: WIP

bool HGE_Impl::_GfxInit() {
    return false;
}
void HGE_Impl::_GfxDone() {}
bool HGE_Impl::_GfxRestore() {
    return false;
}
void HGE_Impl::_AdjustWindow() {}
void HGE_Impl::_Resize(int width, int height) {}
bool HGE_Impl::_init_lost() {
    return false;
}
void HGE_Impl::_render_batch(bool bEndScene) {}
int HGE_Impl::_format_id(int fmt) {
    return 0;
}
void HGE_Impl::_SetBlendMode(int blend) {}
void HGE_Impl::_SetProjectionMatrix(int width, int height) {}

bool CALL HGE_Impl::Gfx_BeginScene(HTARGET target) {
    return false;
}
void CALL HGE_Impl::Gfx_EndScene() {}
void CALL HGE_Impl::Gfx_Clear(DWORD color) {}
void CALL HGE_Impl::Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color, float z) {}
void CALL HGE_Impl::Gfx_RenderTriple(const hgeTriple *triple) {}
void CALL HGE_Impl::Gfx_RenderQuad(const hgeQuad *quad) {}
hgeVertex *CALL HGE_Impl::Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim) {
    return nullptr;
}
void CALL HGE_Impl::Gfx_FinishBatch(int nprim) {}
void CALL HGE_Impl::Gfx_SetClipping(int x, int y, int w, int h) {}
void CALL HGE_Impl::Gfx_SetTransform(float x, float y, float dx, float dy, float rot, float hscale, float vscale) {}

HTARGET CALL HGE_Impl::Target_Create(int width, int height, bool zbuffer) {
    return 0;
}
void CALL HGE_Impl::Target_Free(HTARGET target) {}
HTEXTURE CALL HGE_Impl::Target_GetTexture(HTARGET target) {
    return 0;
}

HTEXTURE CALL HGE_Impl::Texture_Create(int width, int height) {
    return 0;
}
HTEXTURE CALL HGE_Impl::Texture_Load(const char *filename, DWORD size, bool bMipmap) {
    return 0;
}
void CALL HGE_Impl::Texture_Free(HTEXTURE tex) {}
int CALL HGE_Impl::Texture_GetWidth(HTEXTURE tex, bool bOriginal) {
    return 0;
}
int CALL HGE_Impl::Texture_GetHeight(HTEXTURE tex, bool bOriginal) {
    return 0;
}
DWORD *CALL HGE_Impl::Texture_Lock(HTEXTURE tex, bool bReadOnly, int left, int top, int width, int height) {
    return nullptr;
}
void CALL HGE_Impl::Texture_Unlock(HTEXTURE tex) {}
