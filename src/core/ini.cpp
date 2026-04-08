#include "../../include/hge.h"
#include "hge_impl.h"

// TODO: WIP

void CALL HGE_Impl::Ini_SetInt(const char *section, const char *name, int value) {}
int CALL HGE_Impl::Ini_GetInt(const char *section, const char *name, int def_val) { return def_val; }
void CALL HGE_Impl::Ini_SetFloat(const char *section, const char *name, float value) {}
float CALL HGE_Impl::Ini_GetFloat(const char *section, const char *name, float def_val) { return def_val; }
void CALL HGE_Impl::Ini_SetString(const char *section, const char *name, const char *value) {}
char* CALL HGE_Impl::Ini_GetString(const char *section, const char *name, const char *def_val) { return (char*)def_val; }
