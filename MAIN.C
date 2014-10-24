/*
** Example Winamp .WAV ROAD input plug-in
** Copyright (c) 2014, Evgeny Pereguda
**
**
*/

#include <windows.h>

#include "Winamp/in2.h"

#include <shlwapi.h>

#include "ROADoverWAVE/ROADoverWAVEproxy.h"


#define WM_WA_MPEG_EOF WM_USER+2

int globalMaxSampleRate = 192000;

In_Module mod;			

int decode_pos_ms;		

int paused;		

volatile int seek_needed; 

int lBPS;

int lsamplesPerRang;

int lSampleRate;

int lNewSampleRate;

int lOutBPS;

int lChannels;

int lengthBuffer = 0;

int maxReadLength = 0;

int blockAlign = 1;

char *globalPtrData = 0;

int formatROAD = 0;

volatile int killDecodeThread=0;			

HANDLE thread_handle=INVALID_HANDLE_VALUE;	

DWORD WINAPI DecodeThread(LPVOID b); 

ROADoverWAVEproxy globalROADoverWAVEproxy;

In_Module *in_wave = 0;

HMODULE in_wave_lib = 0;

void config(HWND hwndParent)
{
	MessageBox(hwndParent,
		L".WAV files",
		L"Configuration",MB_OK);
}
void about(HWND hwndParent)
{
	MessageBox(hwndParent,L"ROAD Player Winamp plugin, by Evgeny Pereguda",
		L"About ROAD Player Winamp plugin",MB_OK);
}

typedef In_Module *(*PluginGetter)();

void init() 
{	
	wchar_t path[MAX_PATH];

	GetModuleFileNameW(mod.hDllInstance, path, MAX_PATH);

	PathRemoveFileSpecW(path);

	PathAppendW(path, L"in_wave.dll");

	in_wave_lib = LoadLibraryW(path);

	if (in_wave_lib)
	{
		PluginGetter pluginGetter = (PluginGetter)GetProcAddress(in_wave_lib, "winampGetInModule2");
		
		if (pluginGetter)
		{
			in_wave = pluginGetter();
		}
	}
}

void quit() 
{
	if (in_wave_lib)
		FreeLibrary(in_wave_lib);

	in_wave_lib=0;

	in_wave=0;

	if(globalROADoverWAVEproxy._ptrIReader != 0)
		globalROADoverWAVEproxy.release(globalROADoverWAVEproxy._ptrIReader);
}

int isourfile(const in_char *fn) { 
	return !wcsicmp(L".wav", PathFindExtension(fn));
} 


int play(const in_char *fn) 
{ 
	int result = 1;

	int maxlatency;
	int thread_id;

	paused=0;
	decode_pos_ms=0;
	seek_needed=-1;

	lBPS = 0;

	do
	{
		if(globalROADoverWAVEproxy._ptrIReader != 0)
			globalROADoverWAVEproxy.release(globalROADoverWAVEproxy._ptrIReader);

		globalROADoverWAVEproxy = getROADoverWAVEproxy(fn);
		
		if(globalROADoverWAVEproxy.isFractalCompression == 0)
			break;
				
		lBPS = globalROADoverWAVEproxy.bitsPerSample;
		
		lsamplesPerRang = 1;

		lNewSampleRate = globalROADoverWAVEproxy.sampleRate;

		lOutBPS = lBPS;
		
		lChannels = globalROADoverWAVEproxy.fractalFormat._originalAmountOfChannels;
		
		if(lBPS == 16)
			lOutBPS = 32;

		for(lSampleRate = lNewSampleRate;
			lSampleRate <= globalMaxSampleRate;
			lSampleRate = lsamplesPerRang * globalROADoverWAVEproxy.sampleRate)
		{
			int res = mod.outMod->Open(lSampleRate,lChannels,lOutBPS, -1,-1); 

			if(res >= 0)
			{
				lNewSampleRate = lSampleRate;

				result = 0;
			}

			lsamplesPerRang *= 2;

			mod.outMod->Close();
		}

		lsamplesPerRang = lNewSampleRate / globalROADoverWAVEproxy.sampleRate;
		
		globalROADoverWAVEproxy.openFile(fn, lsamplesPerRang, globalROADoverWAVEproxy.fractalFormat, lBPS, lOutBPS, &globalROADoverWAVEproxy._ptrIReader);

		maxlatency = mod.outMod->Open(lNewSampleRate,lChannels,lOutBPS, -1,-1); 

		mod.SetInfo((lNewSampleRate*lOutBPS*lChannels)/1000,lNewSampleRate/1000,lChannels,1);

		mod.SAVSAInit(maxlatency,lNewSampleRate);

		mod.VSASetInfo(lNewSampleRate,lChannels);

		mod.outMod->SetVolume(-666); 

		lengthBuffer = 
			globalROADoverWAVEproxy.fractalFormat._superFrameLength * 
			globalROADoverWAVEproxy.fractalFormat._frameRangeLength * 
			lsamplesPerRang * lChannels * (lOutBPS/8);

		maxReadLength = 576 * lChannels * (lOutBPS/8);

		blockAlign = lChannels * (lOutBPS / 8);

		if(globalPtrData != 0)
			free(globalPtrData);

		globalPtrData = (char *)malloc(lengthBuffer);

	}
	while(0);
	
	if(result == 0)
	{
		formatROAD = 1;

		killDecodeThread=0;
		
		thread_handle = (HANDLE) CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) DecodeThread,NULL,0,&thread_id);		
	}
	else
	{
		if (in_wave != 0 && in_wave->version & IN_UNICODE)
		{
			result = in_wave->Play(fn);
		}
	}
	
	return result; 
}

void pause() 
{ 
	if(formatROAD == 1)
	{
		paused=1; 
	
		mod.outMod->Pause(1); 
	}
	else
	{
		if (in_wave)
			in_wave->Pause();
	}
}

void unpause() 
{ 
	if(formatROAD == 1)
	{
		paused=0; 
	
		mod.outMod->Pause(0); 
	}
	else
	{
		if (in_wave)
			in_wave->UnPause();
	}
}

int ispaused() 
{ 
	if(formatROAD == 1)
	{
		return paused; 
	}
	else
	{
		if (in_wave)
			return in_wave->IsPaused();
	}	
}

void stop() 
{ 
	if(formatROAD == 1)
	{

		if (thread_handle != INVALID_HANDLE_VALUE)
		{
			killDecodeThread=1;

			if (WaitForSingleObject(thread_handle,10000) == WAIT_TIMEOUT)
			{
				MessageBox(mod.hMainWindow,L"error asking thread to die!\n",
					L"error killing decode thread",0);

				TerminateThread(thread_handle,0);
			}

			CloseHandle(thread_handle);

			thread_handle = INVALID_HANDLE_VALUE;
		}

		mod.outMod->Close();
	
		mod.SAVSADeInit();
	
		if (globalROADoverWAVEproxy._ptrIReader != 0)
			globalROADoverWAVEproxy.release(globalROADoverWAVEproxy._ptrIReader);

		globalROADoverWAVEproxy._ptrIReader = 0;

	}
	else
	{
		in_wave->Stop();

		in_wave->SetInfo = mod.SetInfo; 
	}
}

int getlength() 
{
	int durationTime = 0;

	if(formatROAD == 1)
	{
		durationTime = globalROADoverWAVEproxy.getDurationLength(globalROADoverWAVEproxy._ptrIReader, lNewSampleRate);	
	}
	else
	{
		if (in_wave)
		{
			durationTime = in_wave->GetLength();
		}
	}

	return durationTime;
}

int getoutputtime()
{ 
	int time = 0;

	if(formatROAD == 1)
	{
		time = decode_pos_ms + (mod.outMod->GetOutputTime()-mod.outMod->GetWrittenTime()); 		
	}
	else
	{
		if (in_wave)
		{
			time = in_wave->GetOutputTime();
		}
	}
	
	return time;
}


void setoutputtime(int time_in_ms) 
{ 
	if(formatROAD == 1)
	{
		seek_needed=time_in_ms; 		
	}
	else
	{
		if (in_wave)
		{
			in_wave->SetOutputTime(time_in_ms);
		}
	}		
}

void setvolume(int volume) 
{ 
	if(formatROAD == 1)
	{
		mod.outMod->SetVolume(volume); 		
	}
	else
	{
		if (in_wave)
		{
			in_wave->outMod = mod.outMod;

			in_wave->SetVolume(volume);
		}
	}
}
void setpan(int pan) 
{ 
	if(formatROAD == 1)
	{	
		mod.outMod->SetPan(pan); 		
	}
	else
	{
		if (in_wave)
		{
			in_wave->outMod = mod.outMod;

			in_wave->SetPan(pan);
		}
	}
}

int infoDlg(const in_char *fn, HWND hwnd)
{

	MessageBox(hwnd,L"ROAD Player Winamp plugin, by Evgeny Pereguda",
		L"About ROAD Player Winamp plugin",MB_OK);
		
	return 0;
}


void getfileinfo(const in_char *filename, in_char *title, int *length_in_ms)
{
}

void eq_set(int on, char data[10], int preamp) 
{ 
	if (in_wave && in_wave->EQSet)
		in_wave->EQSet(on, data, preamp);
}

DWORD WINAPI DecodeThread(LPVOID b)
{
	
	while (!killDecodeThread) 
	{
		if (seek_needed != -1) 
		{
			int offs;
			decode_pos_ms = seek_needed;
			seek_needed=-1;
			
			mod.outMod->Flush(decode_pos_ms); 
											  
			offs = MulDiv(decode_pos_ms, lNewSampleRate, 1000); 

			globalROADoverWAVEproxy.setPosition(offs, globalROADoverWAVEproxy._ptrIReader);
		}

		if (mod.outMod->CanWrite() >= (maxReadLength*(mod.dsp_isactive()?2:1)))
		{
			
			int readLength = globalROADoverWAVEproxy.readData(globalPtrData, maxReadLength, globalROADoverWAVEproxy._ptrIReader);
			
			if (readLength == -1)
			{
				mod.outMod->CanWrite();

				if (!mod.outMod->IsPlaying())
				{
				
					PostMessage(mod.hMainWindow, WM_WA_MPEG_EOF, 0, 0);
					return 0;	
				}
				Sleep(10);		
			}
			else
			{
				decode_pos_ms += ((readLength / blockAlign) * 1000) / lNewSampleRate;

				mod.outMod->Write(globalPtrData, readLength);
			}
						
		}

	}
	return 0;
}


In_Module mod = 
{
	IN_VER,	
	"ROAD input plugin v0.0 "
#ifdef __alpha
	"(AXP)"
#else
	"(x86)"
#endif
	,
	0,	
	0,  
	"WAV\0ROAD Audio File (*.WAV)\0"
	,
	1,	
	1,	
	config,
	about,
	init,
	quit,
	getfileinfo,
	infoDlg,
	isourfile,
	play,
	pause,
	unpause,
	ispaused,
	stop,
	
	getlength,
	getoutputtime,
	setoutputtime,

	setvolume,
	setpan,

	0,0,0,0,0,0,0,0,0, 

	0,0, 

	eq_set,

	NULL,		

	0 

};

__declspec( dllexport ) In_Module * winampGetInModule2()
{
	return &mod;
}
