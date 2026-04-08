#include "hge_impl.h"

// TODO: WIP

void *CALL HGE_Impl::Resource_Load(const char *filename, DWORD *size) {
    return nullptr;
}
void CALL HGE_Impl::Resource_Free(void *res) {}
bool CALL HGE_Impl::Resource_AttachPack(const char *filename, const char *password) {
    return false;
}
void CALL HGE_Impl::Resource_RemovePack(const char *filename) {}
void CALL HGE_Impl::Resource_RemoveAllPacks() {}
char *CALL HGE_Impl::Resource_MakePath(const char *filename) {
    return nullptr;
}
char *CALL HGE_Impl::Resource_EnumFiles(const char *wildcard) {
    return nullptr;
}
char *CALL HGE_Impl::Resource_EnumFolders(const char *wildcard) {
    return nullptr;
}
