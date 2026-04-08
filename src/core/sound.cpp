#include "../../include/hge.h"
#include "hge_impl.h"

// TODO: WIP

bool HGE_Impl::_SoundInit() { return false; }
void HGE_Impl::_SoundDone() {}
void HGE_Impl::_SetMusVolume(int vol) {}
void HGE_Impl::_SetStreamVolume(int vol) {}
void HGE_Impl::_SetFXVolume(int vol) {}

HEFFECT CALL HGE_Impl::Effect_Load(const char *filename, DWORD size) { return 0; }
void CALL HGE_Impl::Effect_Free(HEFFECT eff) {}
HCHANNEL CALL HGE_Impl::Effect_Play(HEFFECT eff) { return 0; }
HCHANNEL CALL HGE_Impl::Effect_PlayEx(HEFFECT eff, int volume, int pan, float pitch, bool loop) { return 0; }

HMUSIC CALL HGE_Impl::Music_Load(const char *filename, DWORD size) { return 0; }
void CALL HGE_Impl::Music_Free(HMUSIC mus) {}
HCHANNEL CALL HGE_Impl::Music_Play(HMUSIC mus, bool loop, int volume, int order, int row) { return 0; }
void CALL HGE_Impl::Music_SetAmplification(HMUSIC music, int ampl) {}
int CALL HGE_Impl::Music_GetAmplification(HMUSIC music) { return 0; }
int CALL HGE_Impl::Music_GetLength(HMUSIC music) { return 0; }
void CALL HGE_Impl::Music_SetPos(HMUSIC music, int order, int row) {}
bool CALL HGE_Impl::Music_GetPos(HMUSIC music, int *order, int *row) { return false; }
void CALL HGE_Impl::Music_SetInstrVolume(HMUSIC music, int instr, int volume) {}
int CALL HGE_Impl::Music_GetInstrVolume(HMUSIC music, int instr) { return 0; }
void CALL HGE_Impl::Music_SetChannelVolume(HMUSIC music, int channel, int volume) {}
int CALL HGE_Impl::Music_GetChannelVolume(HMUSIC music, int channel) { return 0; }

HSTREAM CALL HGE_Impl::Stream_Load(const char *filename, DWORD size) { return 0; }
void CALL HGE_Impl::Stream_Free(HSTREAM stream) {}
HCHANNEL CALL HGE_Impl::Stream_Play(HSTREAM stream, bool loop, int volume) { return 0; }

void CALL HGE_Impl::Channel_SetPanning(HCHANNEL chn, int pan) {}
void CALL HGE_Impl::Channel_SetVolume(HCHANNEL chn, int volume) {}
void CALL HGE_Impl::Channel_SetPitch(HCHANNEL chn, float pitch) {}
void CALL HGE_Impl::Channel_Pause(HCHANNEL chn) {}
void CALL HGE_Impl::Channel_Resume(HCHANNEL chn) {}
void CALL HGE_Impl::Channel_Stop(HCHANNEL chn) {}
void CALL HGE_Impl::Channel_PauseAll() {}
void CALL HGE_Impl::Channel_ResumeAll() {}
void CALL HGE_Impl::Channel_StopAll() {}
bool CALL HGE_Impl::Channel_IsPlaying(HCHANNEL chn) { return false; }
float CALL HGE_Impl::Channel_GetLength(HCHANNEL chn) { return 0.0f; }
float CALL HGE_Impl::Channel_GetPos(HCHANNEL chn) { return 0.0f; }
void CALL HGE_Impl::Channel_SetPos(HCHANNEL chn, float fSeconds) {}
void CALL HGE_Impl::Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan, float pitch) {}
bool CALL HGE_Impl::Channel_IsSliding(HCHANNEL channel) { return false; }
