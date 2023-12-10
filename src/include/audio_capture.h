#pragma once

#include <windows.h>
#include <mmdeviceapi.h>
#include <winnt.h>
#include <stdio.h>
#include <initguid.h>
#include <endpointvolume.h>
#include <audioclient.h>

#include <cstdint>

#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

void setup(uint64_t* data_length);
void fill_buffer(float* data);
void cleanup();

class AudioCapture {
public:
	AudioCapture();
	~AudioCapture();
	uint64_t fill_buffer();
	float* get_data();
private:
	uint64_t data_length;
	float* data;
	IMMDeviceEnumerator* pEnumerator = NULL;
	WAVEFORMATEX* pwfx = NULL;
	IMMDevice* pDevice = NULL;
	IAudioClient* pAudioClient = NULL;
	IAudioCaptureClient* pCaptureClient = NULL;
	BYTE* pData;
	DWORD flags;
	REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
	UINT32 bufferFrameCount;
	UINT32 numFramesAvailable;
	WORD wBitsPerSample;
	WORD wChannels;

	void winfatal_error(HRESULT hr, const char* fmt, ...);
};
