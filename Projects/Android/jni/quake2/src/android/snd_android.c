



// snd_android.c
// all other sound mixing is portable


#include "../client/client.h"
#include "../client/snd_loc.h"


// like snd_sdl.c

static int  snd_inited;
static dma_t *shm = NULL;

int paint_audio (void *unused, void * stream, int len)
{
	if (!snd_inited) return 0;
	if (shm) {
		shm->buffer = stream;
		shm->samplepos += len / (shm->samplebits / 4);
		// Check for samplepos overflow?
		S_PaintChannels (shm->samplepos);
		return len;
	}
	return 0;
}

qboolean SNDDMA_Init(void)
{
	/*
	 most of the wav files are 16 bits, 22050 Hz, mono

*/


	/* Fill the audio DMA information block */
	shm = &dma;
	shm->samplebits = 16;

	//malloc max : 19 MB
	/*shm->speed = 44100;
	shm->channels = 2;
	*/

	// malloc max : 7 MB  => -12 MB !!
	shm->speed = 22050;
	shm->channels = 2;

	/*

	from snd_arts.c

	=> 46 ms audio per dma transfert

		if (dma.speed == 44100)
			dma.samples = (2048 * dma.channels);
		else if (dma.speed == 22050)
			dma.samples = (1024 * dma.channels);
		else
			dma.samples = (512 * dma.channels);
*/

	// 2048 (= 100 ms) better for multithreading ?

	shm->samples = 2048 * shm->channels;
	shm->samplepos = 0;
	shm->submission_chunk = 1;
	shm->buffer = NULL;

	snd_inited = 1;

	return true;

}

int SNDDMA_GetDMAPos(void)
{
	return shm->samplepos;
}

void SNDDMA_Shutdown(void)
{
	if (snd_inited) {
		snd_inited = 0;
	}
}

void SNDDMA_BeginPainting (void)
{
}

void SNDDMA_Submit(void)
{


}


