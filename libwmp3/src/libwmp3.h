#ifndef _WMP3_LIBWMP3_H__
#define _WMP3_LIBWMP3_H__

/*
 * libwmp3 - multimedia library for playing mp3, mp2 files
 *
 *	NOTE: wrapper functions using __stdcall calling convention
 *        for compatibility with Visual Basic.
 *
 * Copyright (C) 2003-2009 Zoran Cindori ( zcindori@inet.hr )
 *
 * ver: 2.4
 * date: 01 April, 2009.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * or see:
 *  <http://www.gnu.org/licenses/>
 */


#include <windows.h>

/*
*	Define W_STATIC_LIB to build static library without exporting functions
*	Define W_DYNAMIC_LIB to build dynamic library exporting functions with __declspec (dllexport)
*	Define W_EXPORT_WITH_DEF_FILE with W_DYNAMIC_LIB to disable __declspec (dllexport)
*	so you can export functions with def file
*
*	If there is nothing defined, functions are using __declspec (dllimport) and you need
*	dynamic version of libwmp3 library.
*
*	To link static version of library with your application define W_STATIC_LIB to
*	disable __declspec (dllimport)
*
*
*/



#ifdef W_STATIC_LIB
	#define W_DECLSPEC
#else	
	#ifdef W_DYNAMIC_LIB	
		#ifdef W_EXPORT_WITH_DEF_FILE
			#define W_DECLSPEC
		#else
			#define W_DECLSPEC __declspec (dllexport)
		#endif
	#else
		#define W_DECLSPEC __declspec (dllimport)
	#endif
#endif





#define WAVE_OUT_WAVE_MAPPER 0xFFFFFFFF





// ID3 field ID

#define ID3_TITLE 1
#define ID3_ARTIST 2
#define ID3_ALBUM 4
#define ID3_GENRE 8
#define ID3_COMMENT 16
#define ID3_TRACKNUM 32
#define ID3_YEAR 64



#define TIME_FORMAT_MS 1
#define TIME_FORMAT_SEC 2
#define TIME_FORMAT_HMS 4
#define TIME_FORMAT_BYTES 8

#define SONG_BEGIN 1	 
#define SONG_END 2
#define SONG_CURRENT_FORWARD 4
#define SONG_CURRENT_BACKWARD 8

typedef struct {
	unsigned int ms;				// number of milliseconds
	unsigned int sec;				// number of seconds 
	unsigned int bytes;				// number of bytes
	unsigned int frames;			// number of frames
	unsigned int hms_hour;			// HMS format: hours
	unsigned int hms_minute;		// HMS format:minutes
	unsigned int hms_second;		// HMS format:seconds
	unsigned int hms_millisecond;	// HMS format: milliseconds
} MP3_TIME;


#define EQ_MAX_FREQ 96000
#define ECHO_MAX_DELAY_NUMBER 20


// WAVEOUT_INFO Format values

#define FORMAT_1M08	1		// 11.025 kHz, mono, 8-bit
#define FORMAT_1M16	2		// 11.025 kHz, mono, 16-bit
#define FORMAT_1S08	4		// 11.025 kHz, stereo, 8-bit
#define FORMAT_1S16	8		// 11.025 kHz, stereo, 16-bit
#define FORMAT_2M08	16		// 22.05 kHz, mono, 8-bit
#define FORMAT_2M16	32		// 22.05 kHz, mono, 16-bit
#define FORMAT_2S08	64		// 22.05 kHz, stereo, 8-bit
#define FORMAT_2S16	128		// 22.05 kHz, stereo, 16-bit
#define FORMAT_4M08	256		// 44.1 kHz, mono, 8-bit
#define FORMAT_4M16	512		// 44.1 kHz, mono, 16-bit
#define FORMAT_4S08	1024	// 44.1 kHz, stereo, 8-bit
#define FORMAT_4S16	2048	// 44.1 kHz, stereo, 16-bit

// WAVEOUT_INFO Support values

#define CAPS_LRVOLUME 8			// Supports separate left and right volume control.
#define CAPS_PITCH 1			// Supports pitch control.
#define CAPS_PLAYBACKRATE 2		// Supports playback rate control.
#define CAPS_SYNC 16			// The driver is synchronous and will block while playing a buffer.
#define CAPS_VOLUME	4			// Supports volume control.
#define CAPS_SAMPLEACCURATE	32	// Returns sample-accurate position information.
#define CAPS_DIRECTSOUND 64		// 

typedef struct {
	unsigned int ManufacturerID;	// Manufacturer identifier for the device driver for the device.
	unsigned int ProductID;			// Product identifier for the device.
	unsigned int DriverVersion;		// Version number of the device driver for the device.
	unsigned int Formats;			// Standard formats that are supported. Can be a combination of values.
	unsigned int Channels;			// Number specifying whether the device supports mono (1) or stereo (2) output.
	unsigned int Support;			// Optional functionality supported by the device.
	char ProductName[32];			// Product name in a null-terminated string.
} WAVEOUT_INFO;

typedef struct {
	int fPlay;			// if song is playing this value is nonzero 
	int fPause;			// if song is paused this value is nonzero 
	int fStop;			// if song is stoped this value is nonzero 
	int fEcho;			// if echo is enabled this value is nonzero 
	int nSfxMode;		// return current echo mode
	int fExternalEQ;	// if external equalizer is enabled this value is nonzero 
	int fInternalEQ;	// if internal equalizer is enabled this value is nonzero	
	int fVocalCut;		// if vocal cut is enabled this value is nonzero
	int fChannelMix;	// if channel mixing is enabled this value is nonzero
	int fFadeIn;		// if song is in "fade in" interval this value is nonzero
	int fFadeOut;		// if song is in "fade out" interval this value is nonzero
	int fInternalVolume;// if internal volume is enabled this value is nonzero
	int fLoop;			// if song is in loop this value is nonzero
	int fReverse;		// if song is in reverse mode this value is nonzero
	int reservd1;		// reserved, this value is undefined
	int reservd2;		// reserved, this value is undefined
	int reservd3;		// reserved, this value is undefined
	int reservd4;		// reserved, this value is undefined
} MP3_STATUS;

typedef struct {
	char *Title;
	char *Artist;
	char *Album;
	char *Year;
	char *Comment;
	char *TrackNum; 
	char *Genre;
} ID3_INFO;



// MPEG VERSION IDENTIFIER

// MPEG Version 1
#define MPEG_1 1
// MPEG Version 2
#define MPEG_2 2
// MPEG Version 2.5
#define MPEG_25 4


// LAYER VERSION
#define LAYER_1 1
#define LAYER_2 2
#define LAYER_3 4


// CHANNEL MODE

// Single channel (Mono)
#define MODE_SINGLE_CHANNEL 1
// Dual channel (Stereo)
#define MODE_DUAL_CHANNEL 2
// Joint stereo (Stereo)
#define MODE_JOINT_STEREO 4
// Stereo
#define MODE_STEREO 8


// EMPHASISI MODE

// none
#define EMPHASIS_NONE 1
// 50/15 ms
#define EMPHASIS_50_15_US 2
// CCIT J.17
#define EMPHASIS_CCITT_J_17 4
// reserved
#define EMPHASIS_RESERVED 8

typedef struct {
	unsigned int nMPEGVersion;
	unsigned int nLayerVersion;
	unsigned int nChannelMode;
	unsigned int nEmphasis;
	unsigned int nSamplingRate;
	unsigned int nHeaderStart;
	unsigned int nChannelNumber;
	unsigned int fVBR;
	unsigned int nBitrate;
} MP3_STREAM_INFO;

typedef struct {
	unsigned int NumberOfBuffers;
	unsigned int NumberOfBytes;
	unsigned int NumberOfMilliseconds;
} STREAM_LOAD_INFO;

// ID3 TAG
#define ID3_VERSION2	2
#define ID3_VERSION1	1

#define FADE_IN 1
#define FADE_OUT 2



// callback function

typedef int  (__stdcall *t_mp3_callback)(unsigned int message, unsigned int param1, unsigned int param2);

// non blocking callback messages

// maximal value 0x39FF

#define MP3_MSG_STOP_ASYNC  0x00000001
#define MP3_MSG_PLAY_ASYNC  0x00000002
#define MP3_MSG_ENTER_LOOP_ASYNC  0x00000004
#define MP3_MSG_EXIT_LOOP_ASYNC  0x00000008
#define MP3_MSG_ENTER_FADE_OUT_ASYNC  0x00000010
#define MP3_MSG_EXIT_FADE_OUT_ASYNC  0x00000020
#define MP3_MSG_ENTER_FADE_IN_ASYNC  0x00000040
#define MP3_MSG_EXIT_FADE_IN_ASYNC  0x00000080
#define MP3_MSG_STREAM_BUFFER_DONE_ASYNC  0x00000200
#define MP3_MSG_STREAM_OUT_OF_DATA_ASYNC  0x00000400

// blocking callback messages
//
// maximal value 0x39FF << 16
//
//
#define MP3_MSG_STOP 0x00010000
#define MP3_MSG_PLAY 0x00020000 
#define MP3_MSG_ENTER_LOOP 0x00040000
#define MP3_MSG_EXIT_LOOP 0x00080000
#define MP3_MSG_ENTER_FADE_OUT 0x00100000
#define MP3_MSG_EXIT_FADE_OUT 0x00200000
#define MP3_MSG_ENTER_FADE_IN 0x00400000
#define MP3_MSG_EXIT_FADE_IN 0x00800000
#define MP3_MSG_WAVE_BUFFER 0x01000000
#define MP3_MSG_STREAM_BUFFER_DONE 0x02000000
#define MP3_MSG_STREAM_OUT_OF_DATA 0x04000000

#define MP3_MSG_ALL 0xFFFFFFFF
#define MP3_MSG_ALL_ASYNC 0x0000FFFF
#define MP3_MSG_ALL_SYNC 0xFFFF0000


// FFT window 

#define  FFT_RECTANGULAR 1
#define  FFT_HAMMING 2
#define  FFT_HANN 3	
#define  FFT_COSINE	4
#define  FFT_LANCZOS 5	
#define  FFT_BARTLETT 6
#define  FFT_TRIANGULAR	7
#define  FFT_GAUSS 8
#define  FFT_BARTLETT_HANN 9
#define  FFT_BLACKMAN 10
#define  FFT_NUTTALL 11
#define  FFT_BLACKMAN_HARRIS 12
#define  FFT_BLACKMAN_NUTTALL 13
#define  FFT_FLAT_TOP 14

// 
#define FFT_HARMONIC_NUM 1
#define  FFT_HARMONIC_FREQ 2
#define  FFT_LEFT_AMPLITUDE 4
#define  FFT_RIGHT_AMPLITUDE 8
#define  FFT_LEFT_PHASE 16
#define  FFT_RIGHT_PHASE 32



typedef struct {
	int nFFTPoints;			// specify number of fft points. Set this value to:  32, 64, 128, 256, 512, 1024, 2048, 8192, 16384
	int nFFTWindow;			// specify FFT window (	FFT_RECTANGULAR, FFT_HAMMING, FFT_HANN, FFT_COSINE, ... )  	   
	int nHarmonicNumber;	// returns number of harmonics ( nFFTPoints / 2 + 1 ) 
	int *pnHarmonicFreq;	// address of buffer for harmonic frequencies ( can be NULL )
	int *pnLeftAmplitude;	// address of buffer for amplitude of left channel harmonics ( can be NULL )
	int *pnRightAmplitude;	// address of buffer for amplitude of right channel harmonics ( can be NULL )
	int *pnLeftPhase;		// address of buffer for phases of left channel harmonics ( can be NULL )
	int *pnRightPhase;		// address of buffer for phases of right channel harmonics ( can be NULL )
} FFT_STRUCT;


// =============================================================================================================
//
//	INTERFACE FOR WMP3 CLASS
//
// =============================================================================================================


class CWMp3
{
	public:

		// get library version
		//
		// This function is included in library version 220 and above

		virtual int __stdcall GetVersion() = 0;



		//	RETURN VALUES:
		//		Library version number.


// =============================================================================================================


		// get last error string

		virtual char * __stdcall GetError() = 0;

		//	RETURN VALUES:
		//		Pointer to null terminated string with error message. Memory for error message
		//		is allocated by class and always is available. Class is responsible for this
		//		memory.

		//	REMARKS:
		//
		//
		// MessageBox(0, mp3->GetError(), "Error", 0);
		//



// ==============================================================================================================

		// enumerate waveform-audio output devices
    	
		virtual int __stdcall EnumerateWaveOut() = 0;

		//	PARAMETERS:
		//		This function takes no parameters.
		//
		//	RETURN VALUES:
		//		Returns the number of wave out devices.
		//		A return value of zero means that no devices are present or that an error occurred.
		//
		//	REMARKS:
		//

	
// ==============================================================================================================


		// enumerate waveform-audio output devices
    	
		virtual int __stdcall GetWaveOutInfo(
			unsigned int nIndex,					// index of wave out device
			WAVEOUT_INFO *pWaveOutInfo	// pointer to  WAVEOUT_INFO structure
		) = 0;

		//	PARAMETERS:
		//		nIndex
		//			Index of wave out device. Call EnumerateWaveOut to get number of wave out devices.
		//			Then you can retreive information for each device using index value from 0 to
		//			device number - 1.
		//	
		//		pWaveOutInfo
		//			Pointer to WAVEOUT_INFO structure.
		//			
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		// REMARKS:
		//
		// WAVEOUT_INFO Format values
		//
		// #define FORMAT_1M08	1		// 11.025 kHz, mono, 8-bit
		// #define FORMAT_1M16	2		// 11.025 kHz, mono, 16-bit
		// #define FORMAT_1S08	4		// 11.025 kHz, stereo, 8-bit
		// #define FORMAT_1S16	8		// 11.025 kHz, stereo, 16-bit
		// #define FORMAT_2M08	16		// 22.05 kHz, mono, 8-bit
		// #define FORMAT_2M16	32		// 22.05 kHz, mono, 16-bit
		// #define FORMAT_2S08	64		// 22.05 kHz, stereo, 8-bit
		// #define FORMAT_2S16	128		// 22.05 kHz, stereo, 16-bit
		// #define FORMAT_4M08	256		// 44.1 kHz, mono, 8-bit
		// #define FORMAT_4M16	512		// 44.1 kHz, mono, 16-bit
		// #define FORMAT_4S08	1024	// 44.1 kHz, stereo, 8-bit
		// #define FORMAT_4S16	2048	// 44.1 kHz, stereo, 16-bit

		// WAVEOUT_INFO Support values

		// #define CAPS_LRVOLUME 8			// Supports separate left and right volume control.
		// #define CAPS_PITCH 1				// Supports pitch control.
		// #define CAPS_PLAYBACKRATE 2		// Supports playback rate control.
		// #define CAPS_SYNC 16				// The driver is synchronous and will block while playing a buffer.
		// #define CAPS_VOLUME	4			// Supports volume control.
		// #define CAPS_SAMPLEACCURATE	32	// Returns sample-accurate position information.
		// #define CAPS_DIRECTSOUND 64		// 

		// typedef struct {
		// 	unsigned int ManufacturerID;	// Manufacturer identifier for the device driver for the device.
		// 	unsigned int ProductID;			// Product identifier for the device.
		// 	unsigned int DriverVersion;		// Version number of the device driver for the device.
		// 	unsigned int Formats;			// Standard formats that are supported. Can be a combination of values.
		// 	unsigned int Channels;			// Number specifying whether the device supports mono (1) or stereo (2) output.
		// 	unsigned int Support;			// Optional functionality supported by the device.
		// 	char ProductName[32];			// Product name in a null-terminated string.
		// } WAVEOUT_INFO;

	
// ==============================================================================================================

		// set wave out device
    	
		virtual int __stdcall SetWaveOutDevice(
			unsigned int nIndex	// wave out index
		) = 0;

		//	PARAMETERS:
		//		nIndex
		//			Index of wave out device. Call EnumerateWaveOut to get number of wave out devices.
		//			Index value is in range from 0 to device number - 1.
		//
		//			There is special index value WAVE_OUT_WAVE_MAPPER.
		//			This value selects a waveform-audio output device capable of playing the given format.
		//			Default walue for new instance of class is WAVE_OUT_WAVE_MAPPER.		
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function has effect on next call to Play() function.
		//		If you call this function while song is playing there is no effect. 
		//		You need to call Stop and Play again to apply new settings.




// =============================================================================================================

		// open mp3 file from disk to play, seek from begining of file, set custom file size

		virtual int __stdcall OpenFile(
			const char *sFileName,			// pointer to name of the file 
			int nWaveBufferLengthMs,		// size of wave buffer ( milliseconds ), minimal 200
			unsigned int nSeekFromStart,	// number of bytes to move file pointer from file beginning	 
			unsigned int nFileSize			// size of file counting from nSeekFromStart position
		)= 0;
		
		//	PARAMETERS:
		//
		//		sFileName		
		//			Points to a null-terminated string that specifies the name of the file.
		//		
		//		nWaveBufferLengthMs
		//			Size of wave buffer in milliseconds, must be at least 200. Smaller buffer produce
		//			smaller delay in effects ( echo, equalizer, fade .. ) and larger buffer produces
		//			larger delay in sound effects. But with larger buffer you have more data ready to
		//			play and this prevents buffer underrun. If you have problems with sound, maybe 
		//			this buffer is too small.
		//
		//		nSeekFromStart
		//			Number of bytes to move file pointer from file beginning. You can skip data at file beginning
		//			and move pointer to higher position.
		//
		//		nFileSize
		//			Size of file counting from nSeekFromStart position. This value can be smaller than the rest size of
		//			file. This enables you to play only fragment of the file. 
		//			If this value is 0, function opens file from nSeekFromStart to the end of file.
		//			If this value is greater than the rest of file, function fails and returns 0.
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//	EXAMPLE 1:
		//
		// 	if(!mp3->OpenMp3File("mySong.mp3",2000, 48,10000)) // skip 48 bytes and play only next 10000 bytes
		//	{
		//		MessageBox(0,mp3->GetError(),"Error",0);
		//		return 0;
		//	}
		//
		//	EXAMPLE 2:
		//
		// 	if(!mp3->OpenMp3File("mySong.mp3",2000, 0,0)) // play whole file
		//	{
		//		MessageBox(0,mp3->GetError(),"Error",0);
		//		return 0;
		//	}
		


// =============================================================================================================

		// open  stream
    	
		virtual int __stdcall OpenStream(
			int fBuffered,				// flag specifying buffered stream
			int fManaged,				// flag flag for enabling or disabling managed stream
			const void *sMemStream,		// pointer to first memory block
			unsigned int nStreamSize,	// size of memory block in bytes
			int nWaveBufferLengthMs		// size of wave buffer ( milliseconds ), minimal 200
		) = 0;
	
		//	PARAMETERS:
		//
		//		fBuffered
		//			Specifies if stream is buffered stream.
		//			Value 1 specifies buffered stream. This type of stream makes copies of data
		//			you push into stream.
		//
		//			Value 0 specifies unbuffered stream. This type of stream only takes pointer
		//			to memory data. You are responsible for this data.			
		//	
		//		fManaged
		//			Specifies if stream is managed or unmanaged.
		//			Value 1 specifies managed stream. You can add more data into this type
		//			of stream with PushDataToStream. See Remarks section.
		//			NOTE: You cant seek position on this type of stream. Functions Seek will fail.
		//
		//			Value 0 specifies unmanaged stream. You can't add more data into this type of stream.
		//			This stream taks only one data block specified by sMemStream parameter.
		//			NOTE: You can seek on this type of stream.		
		//
		//		sMemStream		
		//			Points to a  memory block. If this value is 0 function fails.
		//
		//		nStreamSize
		//			Size of memory block, in bytes,  with mp3 data. If this value is 0 function fails.
		//		
		//		nWaveBufferLengthMs
		//			Size of wave buffer in milliseconds, must be at least 200. Smaller buffer produce
		//			smaller delay in effects ( echo, equalizer, fade .. ) and larger buffer produces
		//			larger delay in sound effects. But with larger buffer you have more data ready to
		//			play and this prevents buffer underrun. If you have problems with sound, maybe 
		//			this buffer is too small.
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//		First block of data needs to be large enough and must have at least one valid mp3 frame.
		//		If this function fails, call this function again with larger block of data or with another
		//		block of data.
		//		For 128 kbps at 44100 Hz you need at least 426 bytes without ID3v2 data at stream start.
		//		If input block is too small, function will fail. Then you need to send larger block.
		//		Optimal value is 10 KB. 
		//
		//		Buffered stream:
		//		In buffered stream, all data you send in stream are buffered internaly by WMp3 class and
		//		class is responsible for memory management of this data.
		//
		//		Unbuffered strem:
		//		In non buffered stream you send only pointer to data into stream. You are responsible
		//		for this data and memory management of this data. See IsStreamDataFree function.
		//		
		//
		//		Managed stream:
		//		With this function you sends first block of data. With PushDataToStream you will send
		//		next block of data into stream. If stream runs out of data it waits until you push more
		//		data into stream. You can turn off this behavior pushing 0 buffer into stream PushDataToStream(0,0); 
		//		If last pushed buffer into stream was 0 buffer, when stream runs out of data,
		//		it stops.
		//		NOTE: You CAN'T seek on this type of stream.
		//
		//		Not managed stream:
		//		You can't add more data into this type of stream. Only data you can add into
		//		this type of stream are data added with OpenStream function as sMemStream parameter.
		//		NOTE: You CAN seek on this stream because there is only one memory block in stream.

		//	
		//	EXAMPLE 1:
		//
		//	OpenStream(0, 0, mem_block, 8000, 500);	// unbuffered, unmanaged stream length 8000 bytes, 500 ms wave buffer
		//
		//	EXAMPLE 2:
		//
		//	OpenStream(0, 1, mem_block, 8000, 500);	// unbuffered, unmanaged stream length 8000 bytes, 500 ms wave buffer
		//
		//	mp3->PushDataToStream(mem_block1, 8000);	// send another block of 8000 bytes
		//	mp3->PushDataToStream(0, 0); // NULL buffer, indicates stream to stop after runs out of data



// =============================================================================================================

		// push new data to managed stream
    	
		virtual int __stdcall PushDataToStream(
			const void *sMemNewData,	// pointer to memory block
			unsigned int nNewDataize	// size of memory block in bytes
		) = 0;

		//	PARAMETERS:
		//
		//		sMemNewData		
		//			Points to a memory block with mp3 data
		//
		//		nStreamSize
		//			Size of memory block (bytes) with mp3 data
		//		 
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//		NOTE: This function works only on managed stream. If you try to push data into
		//		unmanaged stream function returns 0.
		//
		//		This function takes sMemNewData  and push this into stream queue.
		//
		//		Not buffered stream:
		//		If stream is not buffered, this function pushes just pointer to data,
		//		caller is responsible for data pointed by sMemNewData pointer.
		//		Use IsStreamDataFree to check if you can delete or free sMemNewData when this
		//		data are pulled from queue.
		//		You can't use sMemNewData after you call  PushDataToStream. Call IsStreamDataFree to
		//		check if you can destroy this data.
		//
		//		Buffered stream:
		//		If stream is buffered, with this function you will push all data into internal buffer
		//		allocated by WMP3 class. Class is responsible for this internal buffer, and you can
		//		destroy original source buffer.
		//
		//		If stream runs out of data it waits until you push more
		//		data into stream. You can turn off this behavior by pushing 0 buffer into stream PushDataToStream(0,0); 
		//		If last pushed buffer into stream was 0 buffer, when stream runs out of data,
		//		it stops.
		//
		//		PushDataToStream(mem_block, 8000);	// push more data into stream
		//		PushDataToStream(0,0);	// push null block into stream indicating that this is last block


	     

// =============================================================================================================

		// check if sMemNewData is out of stream

		virtual int __stdcall IsStreamDataFree(
			const void *sMemNewData	// pointer to memory block
		) = 0;

		//	PARAMETERS:
		//
		//		sMemNewData		
		//			Points to a memory to check if this pointer is still in stream. 
		//
		//	RETURN VALUES:
		//		1 - sMemNewData isn't in stream anymore, you can use this data, destroy ....
		//		0 - sMemNewData is still in stream, wait
		//
		//	REMARKS:
		//		When you push memory block to not buffered stream with PushDataToStream you need to wait.
		//		Call IsStreamDataFree to check if data are still in stream.
		//
		//		If stream is buffered you can destroy original data because WMp3 class makes copy of
		//		data pushed into stream.
		//
		//		If you call this function on unmanaged stream, return value is always 1.		
		//
		//		mp3->PushDataToStream(tmp, 8000);
		//		if(mp3->IsStreamDataFree(tmp))
		//		{
		//			free(tmp); // or load ne data into this block
		//		}


// =============================================================================================================

		// return number of buffers in  stream, works only on managed streams
    	
		virtual int __stdcall GetStreamLoad(
			STREAM_LOAD_INFO *pStreamLoadInfo	// pointer to STREAM_LOAD_INFO structure
		) = 0;
	     
		//	PARAMETERS:
		//		pStreamLoadInfo
		//			Pointer to structure receiving informations about stream load. 
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//		Use this function to to check if stream is low with data, so you can push
		//		more data into stream  
		//
		//   typedef struct {
		//		unsigned int NumberOfBuffers;		// number of buffers currently in stream
		//		unsigned int NumberOfBytes;			// number of bytes currently in stream
		//		unsigned int NumberOfMilliseconds;	// number of milliseconds currently in stream
		//	} STREAM_LOAD_INFO;  
		//
		//	  NumberOfMilliseconds
		//		Size of data in stream converted into milliseconds.
		//		This value is average value and isn't precise.	
        


// =============================================================================================================

		// open mp3 stream from application resource

		virtual int __stdcall OpenResource(
			HMODULE hModule,				// resource-module handle 
			const char *sResName,			// pointer to resource name 
			const char *sResType,			// pointer to resource type 
			int nWaveBufferLengthMs,		// size of wave buffer ( milliseconds ), minimal 200
			unsigned int nSeekFromStart,	// number of bytes to move file pointer from beginning of resource block	
			unsigned int nResourceSize		// size of resource block counting from nSeekFromStart position
		) = 0;

		//	PARAMETERS:
		//		
		//		hModule
		//			A handle to the module whose executable file contains the resource. 
		//			A value of NULL specifies the module handle associated with the image file
		//			that the operating system used to create the current process.
		//
		//		sResName
		//			Specifies the name of the resource. For more information, see the Remarks section
		//
		//		sResType
		//			Specifies the resource type. For more information, see the Remarks section.
		//			For standard resource types, this parameter can be RT_RCDATA.
		//
		//		nWaveBufferLengthMs
		//			Size of wave buffer in milliseconds, must be at least 200. Smaller buffer produce
		//			smaller delay in effects ( echo, equalizer, fade .. ) and larger buffer produces
		//			larger delay in sound effects. But with larger buffer you have more data ready to
		//			play and this prevents buffer underrun. If you have problems with sound, maybe 
		//			this buffer is too small.
		//
		//		nSeekFromStart
		//			Number of bytes to move pointer from beginning of resource block. You can skip data
		//			at the beginning and move pointer to higher position.
		//
		//		nResourceSize
		//			Size of resource block counting from nSeekFromStart position. This value can be smaller
		//			than the rest size of resource block. This enables you to play only fragment of the block. 
		//			If this value is 0, function opens resource from nSeekFromStart to the end of resource.
		//			If this value is greater than the rest size of resource, function fails and returns 0.
		//
		//	RETURN VALUES:
		//
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARKS:
		//
		//	If the high-order word of the sResName or sResType parameter is zero,
		//	the low-order word specifies the integer identifier of the name or type of the given resource.
		//	Otherwise, those parameters are long pointers to null-terminated strings.
		//	If the first character of the string is a pound sign (#), the remaining characters
		//	represent a decimal number that specifies the integer identifier of the resource's name or type.
		//	For example, the string "#258" represents the integer identifier 258. 
		//
		//	The MAKEINTRESOURCE macro converts an integer value to a resource type compatible
		//	with Win32 resource-management functions.
		//	This macro is used in place of a string containing the name of the resource. 
		//
		//
		//  If resource identifier is string 
		//
		//	if(!mp3->OpenMp3Resource(GetModuleHandle(NULL), "MYSONG" ,RT_RCDATA, 2000, 100, 28000)
		//	{
		//		MessageBox(0,mp3->GetError(),"Error",0);
		//		return 0;
		//	}
		//
		// or
		//	If resource identifier is integer
		//
  		//	if(!mp3->OpenMp3Resource(GetModuleHandle(NULL), MAKEINTRESOURCE(MYSONG) ,RT_RCDATA, 2000, 0, 0)
		//	{
		//		MessageBox(0,mp3->GetError(),"Error",MB_APPLMODAL|MB_ICONSTOP) ;
		//		return 0;
		//	}
		

// =============================================================================================================

		// close mp3
		
		virtual int __stdcall Close() = 0;

		//	PARAMETERS:
		//		This function has no parameters. . 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function stops playing. Memory is reallocated,  stream buffer are free.
		//		You need to call Open functions again to open new mp3 file or stream or resource ...		 
	

// ----------------------------------------------------------------------------------------

		// start playing from current position

		virtual int __stdcall Play() = 0;

		//	PARAMETERS:
		//		This function has no parameters. . 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//


// =============================================================================================================

		// play loop

		virtual int __stdcall PlayLoop(
			int fFormatStartTime,		// flag specifying start time format
			MP3_TIME *pStartTime,		// pointer to MP3_TIME structure specifying start time
			int fFormatEndTime,			// flag specifying end time format
			MP3_TIME *pEndTime,			// pointer to MP3_TIME structure specifying end time
			unsigned int nNumOfRepeat	// number of loop iterations
		) = 0;

		//	PARAMETERS:
		//
		//		fFormatStartTime
		//			Flag specifying time format of pStartTime.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pStartTime		
		//			Pointer to MP3_TIME structure with loop starting position.
		//
		//		fFormatEndTime
		//			Flag specifying time format of pEndTime.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pEndTime		
		//			Pointer to MP3_TIME structure with loop ending position.
		//
		//		nNumOfRepeat		
		//			Number of loop iterations.
		//
		//		 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function starts playing. If song is already playing, this function seeks to
		//		pStartTime position, makes nNumOfRepeat iterations and then plays forward.
		//


// =============================================================================================================


		// seek position counting from song start

        virtual int __stdcall Seek(
			int fFormat,		// flag specifying time format
			MP3_TIME *pTime,	// pointer to MP3_TIME structure specifying time
			int nMoveMethod	// how to move 
		) = 0;

		//	PARAMETERS:
		//		fFormat
		//			Flag specifying time format used to seek position.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pTime		
		//			Pointer to MP3_TIME structure with new position.
		//
		//		nMoveMethod
		//			Specifies the starting point and direction. This parameter can be one of the following values:
		//
		//			SONG_BEGIN
		//				The starting point is zero or the beginning of the song.
		//				If SONG_BEGIN is specified, pTime is interpreted as a new position
		//				in song counting from song start.
		//	 
		//			SONG_END
		//				The starting point is end of song.
		//				If SONG_END is specified, pTime is interpreted as a new position
		//				in song counting backward from the end of song.
		//
		//			SONG_CURRENT_FORWARD
		//				The current position of song is starting point. Parameter pTime is interpreted
		//				as time offset counting from current position to the end of song.
		//
		//			SONG_CURRENT_BACKWARD
		//				The current position of song is starting point. Parameter pTime is interpreted
		//				as time offset counting from current position to the start of song.
		//	 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function stops playing. You need to call Play  to start playing after Seek function		
		//
		//
		// typedef struct {
		//	unsigned int ms;				// number of milliseconds 
		//	unsigned int sec;				// number of seconds
		//	unsigned int bytes;				// number of bytes
		//	unsigned int frames;			// number of frames
		//	unsigned int hms_hour;			// HMS format: hours
		//	unsigned int hms_minute;		// HMS format:minutes
		//	unsigned int hms_second;		// HMS format:seconds
		//	unsigned int hms_millisecond;	// HMS format: milliseconds
		// } MP3_TIME;


// =============================================================================================================

		// enable reverse mode ( in this mode song plays backward )

		virtual int __stdcall ReverseMode(
			int fEnable	//  flag for enabling or disabling reverse mode
		) = 0;

		//	PARAMETERS:
		//		fEnable
		//			Specifies whether to enable or disable reverse mode.
		//			Value 1 enables reverse mode, 0 disables reverse mode.
		//
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//
		// This function scans whole stream to enumerate all frames. This takes some time( about 1 sec ).
		// This enumeration is just enumeration of frames, function counts all mp3 frames and
		// saves position of each frame into array. This function doesn't makes large buffer
		// with decoded audio samples. No, this is just mp3 frame enumeration. If song has
		// 300 seconds, this is about 11000 frame, so, this function needs 11000 * 4 = 44000 bytes
		// to enumerate all frames. This class doesn't need additional wave buffer to play song reverse.
		// It just decodes mp3 frames reverse and plays like it plays in normal mode.
		// This scan is preformad only once on stream. If you intend to use reverse mode
		// you can call this function when file is open with parameter 0. This will enumerate
		// all frames and prepare stream for reverse mode. 
		// Subsequent calls to this function will not start enumeration of frames. 
		//
		// Enabling this mode, song will play backward. You need to seek from the beginning of
		// song and then play backward to the song start. You can't play backward from 0 position.
		// You need to seek song first and then play backward. 
		// You can change reverse mode while song is playing to change playing direction.
		//
		// NOTE:
		//	You CAN'T use this function on managed stream because reverse mode needs whole stream in one place
		//  to perform bit reservoir recovery when playing reverse.




// =============================================================================================================

		// stop playing

        virtual int __stdcall Stop() = 0;

		//	PARAMETERS:
		//		This function has no parameters. . 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string

 

// =============================================================================================================

		// pause playing

        virtual int __stdcall Pause() = 0;

		//	PARAMETERS:
		//		This function has no parameters. . 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string

// =============================================================================================================

		// continue paused playing

        virtual int __stdcall Resume() = 0;

		//	PARAMETERS:
		//		This function has no parameters. . 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string


// =============================================================================================================
		// get current position


        virtual int __stdcall GetPosition(
			MP3_TIME *pTime	// pointer to MP3_TIME structure
		) = 0;

		
		//	PARAMETERS:
		//		pTime		
		//			Pointer to MP3_TIME structure
		//
		///	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARKS:
		//		This function returns song position in 3 different formats at once:
		//		Format1: milliseconds ( ms )
		//		Format2: seconds ( sec )
		//		Format3: HMS format ( song position presented by hours, minutes, seconds and milliseconds )
		//
		//		
		//
		//
		// typedef struct {
		//	unsigned int ms;				// number of milliseconds ( song position in milliseconds )
		//	unsigned int sec;				// number of seconds ( song position in seconds ) 
		//	unsigned int bytes;				// number of bytes
		//	unsigned int frames;			// number of frames
		//	unsigned int hms_hour;			// HMS format: hours
		//	unsigned int hms_minute;		// HMS format:minutes
		//	unsigned int hms_second;		// HMS format:seconds
		//	unsigned int hms_millisecond;	// HMS format: milliseconds
		// } MP3_TIME;

// =============================================================================================================

		// use internal volume control, modify wave samples, don't change wave out mixer volume
	

		virtual int __stdcall InternalVolume(
			int fEnable	// flag for enabling or disabling internal volume control ( disabled by default )
		) = 0;

		//	PARAMETERS:
		//		fEnable
		//			Specifies whether to enable or disable internal volume control.
		//			If this parameter is 1, internal volume control is enabled.
		//			If the parameter is 0,  internal volume control is disabled ( default ). 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		If internal volume control is enabled, audio volume is controled internally by
		//		modifying audio samples. Using internal volume control, you can separately change volume
		//		for each instance of class.

// =============================================================================================================

        // Set output volume

        virtual int __stdcall SetVolume(
			unsigned int nLeftVolume,	// left channel volume
			unsigned int nRightVolume	// right channel volume
		) = 0;

		//	PARAMETERS:
		//		nLeftVolume
		//			Specifies volume for left channel. Volume range is from 0 to 100
		//
		//		nRightVolume
		//			Specifies volume for right channel. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		If internal volume control is enabled, audio samples are modifyed to control volume.
		//		Wave output volume at soundcard stays unchanged.
		//		If internal volume control is disabled, this function changes wave output volume of
		//		sound card and that has affect on all playing sounds on computer.  


// =============================================================================================================-


        // Set output volume of wave out device driver

        virtual int __stdcall SetMasterVolume(
			unsigned int nLeftVolume,	// left channel volume
			unsigned int nRightVolume	// right channel volume
		) = 0;

		//	PARAMETERS:
		//		nLeftVolume
		//			Specifies volume for left channel. Volume range is from 0 to 100
		//
		//		nRightVolume
		//			Specifies volume for right channel. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function changes wave out volume affecting device driver and all sound on computer 


// =============================================================================================================-


        // Set internal volume ( modify PCM samples to control volume )

        virtual int __stdcall SetPlayerVolume(
			unsigned int nLeftVolume,	// left channel volume
			unsigned int nRightVolume	// right channel volume
		) = 0;

		//	PARAMETERS:
		//		nLeftVolume
		//			Specifies volume for left channel. Volume range is from 0 to 100
		//
		//		nRightVolume
		//			Specifies volume for right channel. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function changes internal volume without affecting wave out device driver.


// =============================================================================================================-



		// get output volume

		virtual int __stdcall GetVolume(
			unsigned int *pnLeftVolume,	// pointer to variable receiving left volume
			unsigned int *pnRightVolume	// pointer to variable receiving right volume
		) = 0;

		//	PARAMETERS:
		//		pnLeftVolume
		//			Pointer to variable receiving left volume. Volume range is from 0 to 100
		//
		//		pnRightVolume
		//			Pointer to variable receiving right volume. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		If internal volume control is enabled, you get internal volume levels.
		//		If internal volume control is disabled, you get volume level of wave out device.

// =============================================================================================================



		// get output volume of wave out device driver

		virtual int __stdcall GetMasterVolume(
			unsigned int *pnLeftVolume,	// pointer to variable receiving left volume
			unsigned int *pnRightVolume	// pointer to variable receiving right volume
		) = 0;

		//	PARAMETERS:
		//		pnLeftVolume
		//			Pointer to variable receiving left volume. Volume range is from 0 to 100
		//
		//		pnRightVolume
		//			Pointer to variable receiving right volume. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//


// =============================================================================================================


		// get internal volume

		virtual int __stdcall GetPlayerVolume(
			unsigned int *pnLeftVolume,	// pointer to variable receiving left volume
			unsigned int *pnRightVolume	// pointer to variable receiving right volume
		) = 0;

		//	PARAMETERS:
		//		pnLeftVolume
		//			Pointer to variable receiving left volume. Volume range is from 0 to 100
		//
		//		pnRightVolume
		//			Pointer to variable receiving right volume. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//


// =============================================================================================================





        // get MPEG version

        virtual int __stdcall GetMp3Info(
			MP3_STREAM_INFO *pInfo	// pointer to MP3_STREAM_INFO structure
		) = 0;

		//	PARAMETERS:
		//		pInfo
		//			Pointer to MP3_STREAM_INFO structure receiving info about mp3 stream
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//	typedef struct {
		//		char *sMPEGVersion;			// Pointer to NULL terminated string specifying MPEG version.
		//		char *sLayerVersion;		// Pointer to NULL terminated string specifying MPEG Layer version.
		//		char *sChannelMode;			// Pointer to NULL terminated string specifying channel mode.
		//		char *sEmphasis;			// Pointer to NULL terminated string specifying emphasis.
		//		unsigned int nSamplingRate;	// Samiling rate in Hz
		//		unsigned int nHeaderStart;	// Position of first valid frame form beginning of file or stream ( in bytes )
		//		unsigned int nChannelNumber;// Channel number
		//		unsigned int fVBR;			// 1 - song is VBR, 0 - song i CBR
		//		unsigned int nBitrate;	// For CBR stream returns stream bitrate, for VBR stream returns average bitrate ( kbps )
		//	} MP3_STREAM_INFO;

// =============================================================================================================

		// get song length
	
		virtual int  __stdcall GetSongLength(
			MP3_TIME *pLength	// pointer to MP3_TIME structure
		) = 0;

		//	PARAMETERS:
		//		pTime		
		//			Pointer to MP3_TIME structure
		//
		///	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARKS:
		//		This function returns song length in 3 different formats at once:
		//		Format1: milliseconds ( ms )
		//		Format2: seconds ( sec )
		//		Format3: HMS format ( song length presented by hours, minutes, seconds and milliseconds )
		//
		//		
		//
		//
		// typedef struct {
		//	unsigned int ms;				// number of milliseconds ( whole song length in milliseconds )
		//	unsigned int sec;				// number of seconds ( whole song length in seconds ) 
		//	unsigned int bytes;				// number of bytes
		//	unsigned int frames;			// number of frames
		//	unsigned int hms_hour;			// HMS format: hours
		//	unsigned int hms_minute;		// HMS format:minutes
		//	unsigned int hms_second;		// HMS format:seconds
		//	unsigned int hms_millisecond;	// HMS format: milliseconds
		// } MP3_TIME;



// =============================================================================================================

		// get bitrate 

        virtual int __stdcall GetBitrate(
			int fAverage	// specifies average bitrate of decoded frame  or current bitrate of decoded frame
		) = 0;

		//	PARAMETERS:
		//		fAverage
		//			Value 1 specifies that function returns average bitrate of last decoded frame.
		//			Value 0 specifies that function returns real bitrate of last decoded frame.
		//
		//	RETURN VALUES:
		//		Return bitrate in kbps.


// =============================================================================================================

		// get current status 

        virtual int __stdcall GetStatus(
			MP3_STATUS *pStatus	// pointer to MP3_STATUS structure
		) = 0;

		//	PARAMETERS:
		//
		//		pStatus		
		//			Pointer to MP3_STATUS structure receiving status informations.
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//typedef struct {
		//	int fPlay;			// if song is playing this value is nonzero 
		//	int fPause;			// if song is paused this value is nonzero 
		//	int fStop;			// if song is stoped this value is nonzero 
		//	int fEcho;			// if echo is enabled this value is nonzero 
		//	int nSfxMode;		// return current echo mode
		//	int fExternalEQ;	// if external equalizer is enabled this value is nonzero 
		//	int fInternalEQ;	// if internal equalizer is enabled this value is nonzero	
		//	int fVocalCut;		// if vocal cut is enabled this value is nonzero
		//	int fChannelMix;	// if channel mixing is enabled this value is nonzero
		//	int fFadeIn;		// if song is in "fade in" interval this value is nonzero
		//	int fFadeOut;		// if song is in "fade out" interval this value is nonzero
		//	int fInternalVolume;// if internal volume is enabled this value is nonzero
		//	int fLoop;			// if song is in loop this value is nonzero
		//	int fReverse;		// if song is in reverse mode this value is nonzero
		//	int reservd1;		// reserved, this value is undefined
		//	int reservd2;		// reserved, this value is undefined
		//	int reservd3;		// reserved, this value is undefined
		//	int reservd4;		// reserved, this value is undefined
		//} MP3_STATUS;
		//
		//
		// MP3_STATUS status;
		// mp3->GetStatus(&status)
		//
		// if(status.play)
		//	printf("Playing song");



// =============================================================================================================

		// mix left and right channel into one mono channel
	
		virtual int __stdcall MixChannels(
			int fEnable,				// flag for enabling or disabling channel mixing
			unsigned int nLeftPercent,	// percent of left channel in resulting sound ( 0 - 100 )
			unsigned int nRightPercent	// percent of right channel in resulting sound ( 0 - 100 )
		) = 0;
		
		//	PARAMETERS:
		//		fEnable
		//			Enables or disables channel mixing. Value 1 enables mixing, value 0 disables mixing.
		//
		//		nLeftPercent
		//			Percent of left channel in resulting sound. Range is from 0 to 100.	
		//
		//		nRightPercent
		//			Percent of right channel in resulting sound. Range is from 0 to 100.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		If you mix 50 % left and 50 % right you get MONO output
		//		If you mix 100 % left and 0 % right you get LEFT channel output
		//		If you mix 0 % left and 100 % right you get RIGHT channel output
		//
		// e.g.
		//
		//	mp3->MixChannels(1, 50,50); // this will convert stereo to mono
		//
		//


// =============================================================================================================

		// return VU data for left and right channel

		virtual int __stdcall GetVUData(
			unsigned int *pnLeftChannel,	// pointer to integer receiving left channel data
			unsigned int *pnRightChannel	// pointer to integer receiving right channel data
		) = 0;

		//	PARAMETERS:
		//		pnLeftChannel
		//			Pointer to integer receiving left channel VU level. Range is from 0 to 100
		//
		//		pnRightChannel
		//			Pointer to integer receiving right channel VU level. Range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string

// =============================================================================================================

		// enable simple vocal cut

		virtual int __stdcall VocalCut(
			int fEnable	// flag for enabling or disabling vocal cut
		) = 0;

		//	PARAMETERS:
		//		fEnable
		//			Enables or disables vocal cut. Value 1 enables vocal cut, value 0 disables vocal cut
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		This function has effect only on stereo channel mode.


// =============================================================================================================

		// fade volume

		virtual int __stdcall FadeVolume(
			int fMode,			// specifies fade mode ( fade in ot fade out )
			int fFormat,		// flag specifying time format
			MP3_TIME *pTime	// pointer to MP3_TIME structure specifying fade interval
		) = 0;

		//	PARAMETERS:
		//		fMode
		//			Specifies fade mode. This parameter can be one of the following values:
		//
		//			FADE_IN
		//				Using this mode, in specified interval volume will rise up
		//				from fade out volume to current volume ( maximum ) 
		//				This mode restores "fade out" volume to normal volume.
		//
		//			FADE_IN
		//				Using this mode, in specified interval volume will drop down
		//				from current volume to 0 (silence) 
		//				Use FADE_IN mode to restore volume back to normal.				
		//
		//		fFormat
		//			Flag specifying time format.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pTime		
		//			Pointer to MP3_TIME structure with fade interval.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		Stop() and Seek() functions cancel fade effect

// =============================================================================================================

// fade volume 

		virtual int __stdcall FadeVolumeEx(
			int fMode,			// specifies fade mode ( fade in ot fade out )
			int fFormat,		// flag specifying time format
			MP3_TIME *pTime	// pointer to MP3_TIME structure specifying fade interval
		) = 0;

		//	PARAMETERS:
		//		fMode
		//			Specifies fade mode. This parameter can be one of the following values:
		//
		//			FADE_IN
		//				Using this mode, volume will immediately drop down to 0 (silence) and then rise up
		//				 to current volume ( maximum ) in specified interval 
		//
		//			FADE_IN
		//				Using this mode, volume will be immediately set to maximum and then drop down
		//				from current volume to 0 (silence)  in specified interval.
		//				Use FADE_IN mode to restore volume back to normal.				
		//
		//		fFormat
		//			Flag specifying time format.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pTime		
		//			Pointer to MP3_TIME structure with fade interval.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		Stop() and Seek() functions cancel fade effect




// =============================================================================================================



		// enable equalizer or disable equalizer

		virtual int __stdcall EnableEQ(
			int fEnable,	//  flag for enabling or disabling equalizer
			int fExternal	//  flag for internal or external equalizer
		) = 0;

		//	PARAMETERS:
		//		fEnable
		//			Specifies whether to enable or disable equalizer.
		//			Value 1 enables equalizer, 0 disables equalizer.
		//
		//		fExternal
		//			Specifies whether to enable or disable internal or external equalizer.
		//			Value 1 specifies external built-in Shibatch Super Equalizer,
		//			slow but accurate with additional functions.
		//			Value 0 specifies libmad internal subband equalizer, fast equalizer,
		//			not accurate.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		There are two equalizers in this class. Internal equalizer is based on
		//		libmad decoding	engine and this equalizer is part of decoding process.
		//		External Shibatch Super Equalizer is based on advanced equalizer engine and
		//		modifies audio samples after samples are decoded from mp3 frames. This eualizer
		//		has multiple features. See function CreateEqBands.
		//
		//		You can enable both equalizers.



// =============================================================================================================


		// create new equalizer bands for external equalizer

		virtual int __stdcall CreateEqBands(
			int *pnFreqPoint,	// pointer to array of integers
			int nNumOfPoints	// number of elements in pnFreqPoint array( min value is 2)
		) = 0;

		//	PARAMETERS:
		//		pnFreqPoint
		//			Specifies frequency points for band limits. Frequency band has lower and upper point.
		//			For one band you need 2 points. Two bands needs 3 points because middle point is
		//			upper point for first band and lower point for second band at the same time.
		//			Number of created bands is nNumOfPoints - 1
		//	
		//		nNumOfPoints
		//			Number of points in pnFreqPoint. Must be at least 2 because you need 2 points
		//			to define first band.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		Use this function to specify new bands. You need to specify limit frequencies for bands.
		//		Lowest frequency is 0 and highest frequency is EQ_MAX_FREQ (samplerate). 
		//		Highest frequency depends on samplerate. If you set highest frequency to EQ_MAX_FREQ then highest
		//		fequency is set to samplerate frequency.
		//		Basicly, you need to specify frequency points to divide whole band into subbands.
		//		You don't need to start from 0 Hz. First band can start from higher frequency. And you don't need to end
		//		with EQ_MAX_FREQ. You can end with lower frequency.
		//
		//		Number of bands created is nNumOfPoints - 1
		//
		//		Class has 10 frequency bands by default. You can create your bands.
		//		There is no limit on number of bands.
		//
		//	Default bands on new created class: 
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		// Example 1: ( create your frequency bands )
		//
		//	int freq_points[7] = { 100, 400, 1000, 3000, 5000, 10000, 15000};
		//	CreateEqBands(freq_points, 7);
		//
		// this function creates 6 bands: 
		//
		//			band:		        0     1      2      3      4       5       
		//			FreqPoint (Hz): 100 - 400 - 1000 - 3000 - 5000 - 10000 - 15000 
		//
		//	In this example band 0 controls range 100 - 400 Hz. Range 0 - 100 isn't available with
		//	this set of FreqPoint. Also range 1500 - EQ_MAX_FREQ isn't available with this set of FreqPoint
		//
		//
		// Example 2: ( create your frequency bands )
		//
		//	int freq_points[7] = { 0, 400, 1000, 3000, 5000, 10000, 15000};
		//	CreateEqBands(freq_points, 7);
		//
		// this function creates 6 bands: 
		//
		//			band:		       0     1      2      3      4       5       
		//			FreqPoint (Hz):  0 - 400 - 1000 - 3000 - 5000 - 10000 - 15000 
		//
		//	In this example band 0 controls range 0 - 400 Hz.
		//	Range 1500 - EQ_MAX_FREQ isn't available with this set of FreqPoint


// =============================================================================================================

		// get eq bands limit frequencies for external equelizer

		virtual int __stdcall GetEqBands(
			int *pnFreqPoint	// pointer to array of integers
		) = 0;

		//	PARAMETERS:
		//		pnFreqPoint
		//			Pointer to array of integers receiving band limit points.
		//			If this value is NULL, the function returns the required number of elements
		//			in pnFreqPoint array.
		//
		//	RETURN VALUES:
		//		Function returns the required number of elements
		//		in pnFreqPoint array.
		//
		//
		//	REMARKS:
		//		New created class has 11 frequency points ( for 10 bands ) 	
		//
		//	Default bands on new created class: 
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ


// =============================================================================================================

		// set equalizer data

		virtual int __stdcall SetEQParam(
			int fExternal,		// flag specifying internal or external equalizer
			int nPreAmpGain,	// preamp gain ( decibel )
			int *pnBandGain,	// array of gain for each band (decibel)
			int nNumberOfBands	// number of frequency bands
		) = 0;


		//	PARAMETERS:
		//
		//		fExternal		
		//			Specifies external or internal equalizer.
		//			Value 1 specifies external (advanced) equalizer.
		//			Value 0 specifies internal equalizer 
		//
		//		nPreAmpGain		
		//			Preamp gain in decibels. Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands.
		//
		//		pnBandGain		
		//			Array of gain for each band ( decibels ). Positive values boost volume,
		//			negative value drops volume.
		//
		//		nNumberOfBands	 
		//			Number of frequency bands. Class has by default 10 eq bands, but you can create
		//			new bands using CreateEqBands function ( only for external equalizer ).
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//	Default bands on new created class: 
		//
		//			SUBBAND FREQUENCY for external Shibatch Super Equalizer
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		//
		//
		//			SUBBAND FREQUENCY for libmad internal  equalizer
		//
		//			index:		       0     1      2      3      4      5      6        7       8       9 
		//			FreqPoint (Hz):  0 - 600 - 1600 - 2000 - 3000 - 4000 - 6000 - 10000  - 13000 - 17000 - EQ_MAX_FREQ
		//
		//
		//		If you use your own eq bands ( CreateEqBands ) you need to send gain for each your band.
		//		If you create 20 eq bands, then you need to send pointer to 20 values as pnBandValue parameter
		//
		//
		// Example:
		//
		// int eq_values[10];
		// eq_values[0] = -12;
		// eq_values[1] = -12;  // cut bas 12 db
		// eq_values[2] = 0;
		// eq_values[3] = 0;  // unchanged
		// eq_values[4] = 0;
		// eq_values[5] = 0;
		// eq_values[6] = 0;
		// eq_values[7] = 12; // boost high tones 12 db
		// eq_values[8] = 12;
		// eq_values[9] = 0;
		// SetEQParam(1, 0, eq_values, 10);


// =============================================================================================================


	// set equalizer data ( millidecibels )

		virtual int __stdcall SetEQParamEx(
			int fExternal,		// flag specifying internal or external equalizer
			int nPreAmpGain,	// preamp gain ( millidecibel)
			int *pnBandGain,	// array of gain for each band ( millidecibels )
			int nNumberOfBands	// number of frequency bands
		) = 0;


		//	PARAMETERS:
		//
		//		fExternal		
		//			Specifies external or internal equalizer.
		//			Value 1 specifies external (advanced) equalizer.
		//			Value 0 specifies internal equalizer 
		//
		//		nPreAmpGain		
		//			Preamp gain in millidecibels ( thousandth of decibel ). Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands.
		//
		//		pnBandGain		
		//			Array of gain for each band millidecibels ( thousandth of decibel ). Positive values boost volume,
		//			negative value drops volume.
		//
		//		nNumberOfBands	 
		//			Number of frequency bands. Class has by default 10 eq bands, but you can create
		//			new bands using CreateEqBands function ( only for external equalizer ).
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//	Default bands on new created class: 
		//
		//			SUBBAND FREQUENCY for external Shibatch Super Equalizer
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		//
		//
		//			SUBBAND FREQUENCY for libmad internal  equalizer
		//
		//			index:		       0     1      2      3      4      5      6        7       8       9 
		//			FreqPoint (Hz):  0 - 600 - 1600 - 2000 - 3000 - 4000 - 6000 - 10000  - 13000 - 17000 - EQ_MAX_FREQ
		//
		//
		//		If you use your own eq bands ( CreateEqBands ) you need to send gain for each your band.
		//		If you create 20 eq bands, then you need to send pointer to 20 values as pnBandValue parameter
		//
		//
		// Example:
		//
		// int eq_values[10];
		// eq_values[0] = -12000;
		// eq_values[1] = -12000;  // cut bas 12 db
		// eq_values[2] = 0;
		// eq_values[3] = 0;  // unchanged
		// eq_values[4] = 0;
		// eq_values[5] = 0;
		// eq_values[6] = 0;
		// eq_values[7] = 12000; // boost high tones 12 db
		// eq_values[8] = 12500;
		// eq_values[9] = 0;
		// SetEQParam(1, 0, eq_values, 10);


// =============================================================================================================


		// get equalizer data

		virtual int __stdcall GetEQParam(
			int fExternal,		// flag specifying internal or external equalizer
			int *pnPreAmpGain,	// pointer to integer receiving preamp gain
			int *pnBandGain		// pointer to variable receiving gain for each band
		) = 0;

		//	PARAMETERS:
		//
		//		fExternal		
		//			Specifies external or internal equalizer.
		//			Value 1 specifies external (advanced) equalizer.
		//			Value 0 specifies internal equalizer 
		//
		//		pnPreAmpGain		
		//			Pointer to integer receiving preamp gain in decibels.
		//			If this value is NULL function returns number of equalizer bands.
		//
		//		pnBandGain		
		//			Pointer to variable receiving gain for each band in decibels.
		//			If this value is NULL function returns number of equalizer bands.
		//
		//
		//	RETURN VALUES:
		//		number of bands
		//
		//	REMARKS:
		//
		//	Default bands on new created class: 
		//
		//			SUBBAND FREQUENCY for external Shibatch Super Equalizer
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		//
		//
		//			SUBBAND FREQUENCY for libmad internal  equalizer
		//
		//			index:		       0     1      2      3      4      5      6        7       8       9 
		//			FreqPoint (Hz):  0 - 600 - 1600 - 2000 - 3000 - 4000 - 6000 - 10000  - 13000 - 17000 - EQ_MAX_FREQ
		//
		//

// =============================================================================================================


		// get equalizer data ( millidecibels )

		virtual int __stdcall GetEQParamEx(
			int fExternal,		// flag specifying internal or external equalizer
			int *pnPreAmpGain,	// pointer to integer receiving preamp gain ( millidecibels)
			int *pnBandGain		// pointer to variable receiving gain for each band ( millidecibels)
		) = 0;

		//	PARAMETERS:
		//
		//		fExternal		
		//			Specifies external or internal equalizer.
		//			Value 1 specifies external (advanced) equalizer.
		//			Value 0 specifies internal equalizer 
		//
		//		pnPreAmpGain		
		//			Pointer to integer receiving preamp gain in millidecibels.
		//			If this value is NULL function returns number of equalizer bands.
		//
		//		pnBandGain		
		//			Pointer to variable receiving gain for each band in millidecibels.
		//			If this value is NULL function returns number of equalizer bands.
		//
		//
		//	RETURN VALUES:
		//		number of bands
		//
		//	REMARKS:
		//
		//	Default bands on new created class: 
		//
		//			SUBBAND FREQUENCY for external Shibatch Super Equalizer
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		//
		//
		//			SUBBAND FREQUENCY for libmad internal  equalizer
		//
		//			index:		       0     1      2      3      4      5      6        7       8       9 
		//			FreqPoint (Hz):  0 - 600 - 1600 - 2000 - 3000 - 4000 - 6000 - 10000  - 13000 - 17000 - EQ_MAX_FREQ
		//
		//

// =============================================================================================================

		// load ID3 data
	
        virtual int __stdcall LoadID3(
			int nId3Version,	// ID3 version
			ID3_INFO *pId3Info	// pointer to ID3_INFO structure
		) = 0;

		//	PARAMETERS:
		//		nId3Version
		//			Specifies ID3 version. Value ID3_VERSION1 loads ID3v1 data.
		//			Value ID3_VERSION2 loads ID3v2 data.
		//
		//		pId3Info
		//			Pointer tu structure receiving ID3 data.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// typedef struct {
		//	char *Title;
		//	char *Artist;
		//	char *Album;
		//	char *Year;
		//	char *Comment;
		//	char *TrackNum; 
		// } ID3_INFO;


// =============================================================================================================	



		// sound processing echo and reverb
		// enable echo and set echo parematers

		
		virtual int __stdcall SetSfxParam(
			int fEnable,		// flag for enabling or disabling sfx processing
			int nMode,			// echo mode
			int nDelayMs,		// delay
			int nInputGain,		// gain of input sound
			int nEchoGain,		// gain of added echo sound
			int nOutputGain		// gain of output sound
		) = 0;

		//	PARAMETERS:
		//
		//		fEnable		
		//			Specifies whether to enable or disable the sfx engine.
		//			If this parameter is 1 sfx engine is enabled.
		//			If this parameter is 0 sfx engine is disables.
		//
		//		nMode		
		//			Specifies echo mode. Range is from 0 to 9.
		//
		//		nDelayMs		
		//			Echo delay in millisecond ( 50 milliseconds step ), max 1000 ms
		//
		//		nInputGain
		//			Gain of input sound in decibels.
		//			Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands. 
		//
		//		nEchoGain
		//			Gain of added echo sound in decibels
		//			Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands
		//
		//		nOutputGain
		//			Gain of output sound in decibels
		//			Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string


// =============================================================================================================

		// get sfx param

		
		virtual int __stdcall GetSfxParam(
			int *pnMode,		// pointer to variable receiving current mode
			int *pnDelayMs,		// pointer to variable receiving echo delay in millisecond
			int *pnInputGain,	// pointer to variable receiving gain of input sound in decibels
			int *pnEchoGain,	// pointer to variable receiving  gain of added echo sound in decibels
			int *pnOutputGain	// pointer to variable receiving gain of output sound in decibels
		) = 0;


		//	PARAMETERS:
		//
		//		pnMode		
		//			Pointer to variable receiving current mode.
		//			Mode range is from 0 to 9.
		//
		//		nDelayMs		
		//			Pointer to variable receiving echo delay in millisecond.
		//
		//		pnInputGain
		//			Pointer to variable receiving gain of input sound in decibels.
		//			Gain 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands. 
		//
		//		pnEchoGain
		//			Pointer to variable receiving  gain of added echo sound in decibels.
		//			Gain 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands
		//
		//		pnOutputGain
		//			Pointer to variable receiving gain of output sound in decibels.
		//			Gain 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string



// =============================================================================================================

		// set sfx mode data

		virtual int __stdcall SetSfxModeData(
			int nMode,				// specifies sfx mode
			int *pnModeDataLeft,	// pointer to sfx mode data for left channel
			int *pnModeDataRight,	// pointer to sfx mode data for right channel
			int nSize				// must be ECHO_MAX_DELAY_NUMBER ( 20 )
		) = 0;


		//	PARAMETERS:
		//		nMode		
		//			Specifies echo mode. Range is from 0 to 9.
		//
		//		pnModeDataLeft		
		//			Pointer to array of 20 integers specifying mode data for left channel.
		//			See Remarks section.
		//
		//		pnModeDataRight
		//			Pointer to array of 20 integers specifying mode data for right channel.
		//			See Remarks section. 
		//
		//		nSize
		//			This value must be 20.
		//
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//
		// REMARKS:
		//	
		//		New created instance of class has all mode set to default values.		
		//
		//		Sfx engine has 	20 buffers, each buffer has about 50 milliseconds audio data.
		//		20 bufers * 50 ms = 1 second of audio data.
		//		First buffer (pnModeDataLeft[0])  represents current playing buffer 
		//		Second buffer (pnModeDataLeft[1])  is 50 ms old ( 50 ms delay) , third is 100 ms old ( 100 ms delay) ....
		//		Last buffer (pnModeDataLeft[19]) is 1000 ms old ( 1000 ms delay)
		// 
		//		Data in these buffers are half volume of original data. And these buffers will mix with half volume
		//		of current playing data.
		//
		//		In pnModeDataLeft and pnModeDataRight you need to specify these mixing ratios for each buffer.
		//
		//	Example 1: { 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
		//
		//	This settings mix half volume original data and 100 %  volume of second buffer (50 ms delay) and you get
		//	simple full volume echo of 50 ms delay
		//
		//  Example 2: { 0, 50, 0, 0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
		//
		//	This settings mix half volume original data + 50 %  volume of second buffer (50 ms delay) and 
		//	half volume original + 50 %  volume of seventh buffer (300 ms delay) and
		//  you get full volume output data wit double echo ( first echo at 50 ms delay and second at 300 ms delay )
		//
		//
		//	Example 3: { 0, 10, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 40, 10, 5, 3, 0, 0, 0 }
		//
		//		Advanced multiple echo.
		//
		//
		//	You can set echo mode for left and right channel separately. You can create different echo effect
		//	on left and right channel at the same time.


// =============================================================================================================	


		// get sfx mode data
		// 
		//
		// INPUT:
		//			int nMode				- identify sfx mode ( 0 - 9 ) 
		//			int *pnModeDataLeft		- pointer to variable receiving mode data for left channel
		//			int *pnModeDataRight	- pointer to variable receiving mode data for right channel
		// RETURN:
		//		number of elements in pnModeDataLeft array ( ECHO_MAX_DELAY_NUMBER )
		//
		// REMARKS:
		//		If pnModeDataLeft is 0, function return number of elements needed for pnModeDataLeft array
		//		Read Remarks section for SetSfxModeData function

		
		virtual int __stdcall GetSfxModeData(
			int nMode,				// identify sfx mode
			int *pnModeDataLeft,	// pointer to variable receiving mode data for left channel
			int *pnModeDataRight	// pointer to variable receiving mode data for right channel
		) = 0;


		
		//	PARAMETERS:
		//
		//
		//		nMode		
		//			Specifies echo mode. Range is from 0 to 9.
		//
		//		pnModeDataLeft
		//			Pointer to variable receiving mode data for left channel.
		//			If this value is 0 function returns number of elements
		//			needed for pnModeDataLeft array 
		//
		//		pnModeDataRight
		//			Pointer to variable receiving mode data for right channel
		//			If this value is 0 function returns number of elements
		//			needed for pnModeDataLeft array 
		//
		// RETURN:
		//		number of elements in pnModeDataLeft array ( ECHO_MAX_DELAY_NUMBER )
		//
		// REMARKS:
		//		If pnModeDataLeft is 0, function return number of elements needed for pnModeDataLeft array
		//		Read Remarks section for SetSfxModeData function

// =============================================================================================================

		// destroy class

		virtual void __stdcall Release() = 0;

		//	PARAMETERS:
		//		This function has no parameters.  
		//
		//	RETURN VALUES:
		//		This function has no return value. 
		//
		//	REMARKS:
		//		Call this function to destroy class created by class factory CreateCWMp3.




// =============================================================================================================


		// set callback function to receive callback messages from decoding thread
    	
		virtual int __stdcall SetCallbackFunc(
								t_mp3_callback pCallbackFunc, // pointert to callback function
								unsigned int nMessages		// specify callback mesages
) = 0;

		//	PARAMETERS:
		//		pCallbackFunc
		//			Pointer to callback function.
		//			int __stdcall CallbackFunc(unsigned int message, unsigned int param1, unsigned int param2);
		//
		//		nMessages
		//			Enable callback messages. There are 2 groups of messages. Blocking and non blocking messages.
		//			Blocking message block decoding thread until callback function returns.
		//			Non blocking message ( async ) doesn't block decoding thread.
		//
		//		NOTE:
		//			DON'T CALL CWMP3 FUNCTIONS FROM BLOCKING CALLBACK MESSAGES BECAUSE YOU WILL FREEZE
		//			DECODING THREAD AND CALLING THREAD ( YOUR APPLICATION ).
		//			IF YOU NEED TO CALL CWMP3 FUNCTIONS FROM CALLBACK, USE NON BLOCKING MESSAGES.
		//
		//			BlOCKING MESSAGE IS ALWAYS SENT BEFORE NON BLOCKING MESSAGE.
		//
		//			 This parameter can be any combination of the following values:

		//				MP3_MSG_ALL					- enable all callback messages ( blocking and non blocking )
		//				MP3_MSG_ALL_ASYNC			- enable all non blocking messages
		//				MP3_MSG_ALL_SYNC			- enable all blocking messages
		//
		//
		//				blocking messages:
		//
		//				MP3_MSG_STOP				- send this message when decoding thread ends
		//				MP3_MSG_PLAY				- send this message when decoding thread starts
		//				MP3_MSG_ENTER_LOOP			- send this message wneh decoding thread enters loop
		//				MP3_MSG_EXIT_LOOP			- send this message when decoding thread leaves  loop
		//				MP3_MSG_ENTER_FADE_OUT		- send this mesage when decoding thread enters fade out interval
		//				MP3_MSG_EXIT_FADE_OUT		- send this mesage when decoding thread leaves fade out interval
		//				MP3_MSG_ENTER_FADE_IN		- send this mesage when decoding thread enters fade in interval
		//				MP3_MSG_EXIT_FADE_IN		- send this mesage when decoding thread leaves fade out interval
		//				MP3_MSG_WAVE_BUFFER			- send this message when decoding thread is about to send decoded data to soundcard
		//				MP3_MSG_STREAM_BUFFER_DONE	- send this message when one or more buffers are done in managed stream
		//				MP3_MSG_STREAM_OUT_OF_DATA	- send this message when managed stream runs out of data


		//				non blocking messages ( async)

		//
		//				MP3_MSG_STOP_ASYNC				- send this message when decoding thread ends
		//				MP3_MSG_PLAY_ASYNC				- send this message when decoding thread starts
		//				MP3_MSG_ENTER_LOOP_ASYNC			- send this message wneh decoding thread enters loop
		//				MP3_MSG_EXIT_LOOP_ASYNC			- send this message when decoding thread leaves  loop
		//				MP3_MSG_ENTER_FADE_OUT_ASYNC		- send this mesage when decoding thread enters fade out interval
		//				MP3_MSG_EXIT_FADE_OUT_ASYNC		- send this mesage when decoding thread leaves fade out interval
		//				MP3_MSG_ENTER_FADE_IN_ASYNC		- send this mesage when decoding thread enters fade in interval
		//				MP3_MSG_EXIT_FADE_IN_ASYNC		- send this mesage when decoding thread leaves fade out interval
		//				MP3_MSG_WAVE_BUFFER_ASYNC		- send this message when decoding thread is about to send decoded data to soundcard
		//				MP3_MSG_STREAM_BUFFER_DONE_ASYNC	- send this message when one or more buffers are done in managed stream
		//				MP3_MSG_STREAM_OUT_OF_DATA_ASYNC	- send this message when managed stream runs out of data
		//

		//
		//
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, use GetError to get error message
		//
		//	REMARKS:
		//
		//  NOTE:
		//	Callback function must have __stdcall calling convention
		//	Callback function prototype:
		//  int __stdcall callback_func(unsigned int message, unsigned int param1, unsigned int param2);
		//
		//	NOTE:
		//		DON'T CALL CWMP3 FUNCTIONS FROM BLOCKING CALLBACK MESSAGES BECAUSE YOU WILL FREEZE
		//		DECODING THREAD AND CALLING THREAD ( YOUR APPLICATION ).
		//		IF YOU NEED TO CALL CWMP3 FUNCTIONS FROM CALLBACK, USE NON BLOCKING MESSAGES.
		//
		//
		//
		// callback function parameters for message:
		//
		
		// =====================================================================================	
		// NON BLOCKING MESSAGES ( ASYNC )
		// =====================================================================================	

		//	MP3_MSG_PLAY_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		Return value has no effect.
		//
		//
		//--------------------------------------------------------------------------------------
		//
		//	MP3_MSG_STOP_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_LOOP_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_LOOP_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.
		
		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_FADE_OUT_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_FADE_OUT_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

				//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_FADE_IN_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_FADE_IN_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.


		//--------------------------------------------------------------------------------------

		//	MP3_MSG_STREAM_BUFFER_DONE_ASYNC
		//		param1		- number of remaining bufferes in stream
		//		param2		- number of remaining bytes in stream
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_STREAM_OUT_OF_DATA_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.



		// =====================================================================================	
		// BLOCKING MESSAGES ( SYNC )
		// =====================================================================================	

		//	MP3_MSG_PLAY
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		0	- thread continue to play
		//		1	- thread exits, playing isn't started at all
		//
		//	NOTE:
		//		Don't call Play, PlayLoop or ReverseMode from this message because you will
		//		enter MP3_MSG_PLAY_BLOCKING callback loop.
		//
		//--------------------------------------------------------------------------------------
		//
		//	MP3_MSG_STOP_BLOCKING
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_LOOP
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		0	- continue loop playing
		//		1	- exit loop and continue playing normal

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_LOOP
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_FADE_OUT
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		0	- continue fade out
		//		1	- exit fade out, fade out has no effect


		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_FADE_OUT
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_FADE_IN
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		0	- continue fade in
		//		1	- exit fade in, fade in has no effect


		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_FADE_IN
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_WAVE_BUFFER
		//		param1	- pointer to memory with PCM wave decoded data ( 16 bit samples )
		//		param2	- size, in bytes, of memory pointed by param1 ( in bytes )
		//	  Return Value
		//		0	-  data will be sent to soundcard.
		//		1	-  data will not be sent to soundcard 
		//		2	-  data will not be sent to soundcard and decoding thread will end

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_WAVE_BUFFER
		//		param1	- pointer to memory with PCM wave decoded data ( 16 bit samples )
		//		param2	- size, in bytes, of memory pointed by param1 ( in bytes )
		//	  Return Value
		//		0	-  data will be sent to soundcard.
		//		1	-  data will not be sent to soundcard 
		//		2	-  data will not be sent to soundcard and decoding thread will end

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_STREAM_BUFFER_DONE
		//		param1		- number of remaining bufferes in stream
		//		param2		- number of remaining bytes in stream
		//	  Return Value
		//		Return value has no effect.


		//--------------------------------------------------------------------------------------

		//	MP3_MSG_STREAM_OUT_OF_DATA
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		0	-  wait for PushDataToStream
		//		1	-  stop playing, exit decoding thread
		//		2	-  don't wait, try to load new data from queue ( danger of endless loop !!! )





// =============================================================================================================

		// calculate FFT values on currently playing PCM data
    	
		virtual int __stdcall GetFFTValues(
								FFT_STRUCT *fftStruct
) = 0;

		//	PARAMETERS:
		//		fftStruct
		//			Pointer to FFT struct.
		//			If this value is 0, internal memory for FFT analysis is deallocated. This memory is allocated when
		//			you call GetFFTValues first time with valid fftStruct parameter.
		//
		//		You need to fill this structure vith valid data:
		//			
		//			nFFTPoints
		//				Set this value to specify FFT size ( number of samples to proccess with FFT algorithm.
		//				This parameter can be one of following values: 32, 64, 128, 256, 512, 1024, 2048, 8192, 16384
		//				Harmonic frequencies and band size depends on this value. Use Google to get more info about FFT, harmonics, ...
		//
		//			nFFTWindow
		//				Set this value to specify FFT window. Use one of the following values:
		//
		//				FFT_RECTANGULAR
		//				FFT_HAMMING
		//				FFT_HANN 
		//				FFT_COSINE
		//				FFT_LANCZOS 
		//				FFT_BARTLETT
		//				FFT_TRIANGULAR
		//				FFT_GAUSS
		//				FFT_BARTLETT_HANN
		//				FFT_BLACKMAN 
		//				FFT_NUTTALL
		//				FFT_BLACKMAN_HARRIS
		//				FFT_BLACKMAN_NUTTALL
		//				FFT_FLAT_TOP
		//
		//				Use Google to get more info about FFT windows.
		//
		//			nHarmonicNumber
		//				This parameter is returned value and specifies number of harmonics returned from FFT analysis = (nFFTPoints/2 + 1)
		//
		//			pnHarmonicFreq
		//				Set this parameter to adress of int array to receive harmonics frequencies in Hz.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If you don't need harmonic frequencies, set pnHarmonicFreq to 0 or NULL.
		//
		//				pnHarmonicFreq[0] is 0 Hz, pnHarmonicFreq[0] is sampling_rate / nFFTPoints ( first harmonic ), pnHarmonicFreq[1] is sampling_rate / nFFTPoints * 2 ( second harmonic ), ...
		//			
		//			pnLeftAmplitude
		//				Set this value to address of int array to receive amplitude for each harmonic of left channel.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If you don't need these information, set this parameter to 0.
		//
		//				Amplitude range is from 0 to about 120 dB.
		//
		//			pnRightAmplitude
		//				Set this value to address of int array to receive amplitude for each harmonic of right channel.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If you don't need these information, set this parameter to 0.
		//
		//				Amplitude range is from 0 to about 120 dB.
		//
		//			pnLeftPhase
		//				Set this value to address of int array to receive phase for each harmonic of left channel.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If you don't need these information, set this parameter to 0.
		//
		//				Phase range is from -90 to 90 degrees.
		//
		//			pnRighttPhase
		//				Set this value to address of int array to receive phase for each harmonic of right channel.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If you don't need these information, set this parameter to 0.
		//
		//				Phase range is from -90 to 90 degrees.
		//
		//		You must specify valid nFFTPoints and nFFTWindow parameter. And you must specify valid pointers for
		//		pnHarmonicFreq, pnLeftAmplitude, pnRightAmplitude, pnLeftPhase and  pnRighttPhase.
		//		Or set these pointers to 0 ( NULL ). If you call this function with wrong, or uninitialized pointers,
		//		you will have memory error or application crash.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARKS:
		//
		//	typedef struct {
		//		int nFFTPoints;			// specify number of fft points. Set this value to:  32, 64, 128, 256, 512, 1024, 2048, 8192, 16384
		//		int nFFTWindow;			// specify FFT window (	FFT_RECTANGULAR, FFT_HAMMING, FFT_HANN, FFT_COSINE, ... )  	   
		//		int nHarmonicNumber;	// returns number of harmonics ( nFFTPoints / 2 + 1 ) 
		//		int *pnHarmonicFreq;	// address of buffer for harmonic frequencies ( can be NULL ), these values changes when sampling rate or nFFTPoints changes 
		//		int *pnLeftAmplitude;	// address of buffer for amplitude of left channel harmonics ( can be NULL )
		//		int *pnRightAmplitude;	// address of buffer for amplitude of right channel harmonics ( can be NULL )
		//		int *pnLeftPhase;		// address of buffer for phases of left channel harmonics ( can be NULL )
		//		int *pnRightPhase;		// address of buffer for phases of right channel harmonics ( can be NULL )
		//	} FFT_STRUCT;
		//
		//
		//	EXAMPLE: ( get harmonics amplitude for left channel on PCM buffer with 512 samples using FFT_BLACKMAN_HARRIS FFT window
		//
		//	FFT_STRUCT fft;
		//	fft.nFFTPoints = 512;					// set FFT size
		//	fft.nFFTWindow = FFT_BLACKMAN_HARRIS;	// set FFT window
		//	fft.pnHarmonicFreq = 0;					// we don't need harmonics frequencies
		//	fft.pnRightAmplitude = 0;				// we don't need right channel amplitudes
		//	fft.pnLeftPhase = 0;						// we don't need phase value
		//	fft.pnRightPhase = 0;					// we don't need phase value 
		//
		//	fft.pnLeftAmplitude = (int*) malloc(512/2 + 1);	// if we use FFT size of 512 samples, we will have 257 frequencies
		//													// where first frequency will be 0 Hz
		//
		//	if(!GetFFTValues(&fft)) // first call will allocate internal memory for FFT algorithm and return valid FFT data
		//	{
		//		// error handling message
		//	}
		//
		//
		//
		//	GetFFTValues(0);	// call this when you don't need FFT processing anymore to free internal buffers ( sample buffer, reverse buffer, cos/sin tables, window buffer )

// =============================================================================================================


  
    
};


// =============================================================================================================
//
//	END OF INTERFACE FOR WMP3 CLASS
//
// =============================================================================================================


#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================================================
//
//	CLASS FACTORY FOR CWMP3 INTERFACE
//
// =============================================================================================================

// class factory

W_DECLSPEC CWMp3 * __stdcall CreateCWMp3(); 

//	PARAMETERS:
//		This function has no parameters.  
//
//	RETURN VALUES:
//		Pointer to instance of new created class.
//
//	REMARKS:
//		This function creates new instance of WMp3 class. Use this function
//		to create new class for your CWMp3 interface.
//		At the end, call member function Release() to delete class instance

// =============================================================================================================
//
//	END OF CLASS FACTORY FOR CWMP3 INTERFACE
//
// =============================================================================================================





// =============================================================================================================
//
//	C/C++ WRAPPER FOR WMP3 CLASS
//
// =============================================================================================================


//	create class instance

W_DECLSPEC char * __stdcall Mp3_Initialize(); 

//	PARAMETERS:
//		This function has no parameters.  
//
//	RETURN VALUES:
//		Pointer to instance of new created class.
//
//	REMARKS:
//		This function creates new instance of WMp3 class.
//		To free class instance call Mp3_Destroy(char *objptr) function.


// =============================================================================================================



W_DECLSPEC int __stdcall Mp3_Destroy(char *objptr); 

//	PARAMETERS:
//		objptr
//			Specifies class instance to delete.
//
//	RETURN VALUES:
//		No return value.
//
//	REMARKS:
//		Call this function to destroy class instance. Use returned value from Mp3_Initialize().
//		Call this function as last function.

// =============================================================================================================


// get library version
//
// This function is included in library version 220 and above

W_DECLSPEC int __stdcall Mp3_GetVersion(
							char *objptr	// Pointer to class instance.
);

//	PARAMETERS:
//		objptr
//			Pointer to class instance.

//	RETURN VALUES:
//		Library version number.

// =============================================================================================================



// get error message

W_DECLSPEC int __stdcall Mp3_GetError(
							char *objptr,	// Pointer to class instance.
							char *pBuffer,	// Pointer to buffer receiving NULL terminated error message string.
							int nSize);		// Size of receiving buffer
//
//	PARAMETERS:
//		objptr
//			Pointer to class instance.
//
//		pBuffer
//			Pointer to buffer receiving NULL terminated error message string.	
//			If this value is zero, the function returns the required buffer size, in bytes,
//			and makes no use of the pBuffer. 
//
//		nSize
//			Size of receiving buffer.
//			If this value is zero, the function returns the required buffer size, in bytes,
//			and makes no use of the pBuffer. 
//
//	RETURN VALUES:
//		If pBuffer or nSize is zero, the function returns the required buffer size, in bytes.
//		If the function succeeds, the return value is number of bytes copied into pBuffer.
//		If function fails return value is 0.
//

// =============================================================================================================

	// set callback function
    	
W_DECLSPEC int __stdcall Mp3_SetCallbackFunc(
							char *objptr,
							t_mp3_callback pCallbackFunc, // pointert to callback function
							unsigned int nMessages
) ;

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.

		//		pCallbackFunc
		//			Pointer to callback function.
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error
		//
		//	REMARKS:
		//
		//	Callback function prototype:
		//  int callback_func(unsigned int message, unsigned int param1, unsigned int param2);


		//	PARAMETERS:
		//		pCallbackFunc
		//			Pointer to callback function.
		//			int __stdcall CallbackFunc(unsigned int message, unsigned int param1, unsigned int param2);
		//
		//		nMessages
		//			Enable callback messages. There are 2 groups of messages. Blocking and non blocking messages.
		//			Blocking message block decoding thread until callback function returns.
		//			Non blocking message ( async ) doesn't block decoding thread.
		//
		//		NOTE:
		//			DON'T CALL CWMP3 FUNCTIONS FROM BLOCKING CALLBACK MESSAGES BECAUSE YOU WILL FREEZE
		//			DECODING THREAD AND CALLING THREAD ( YOUR APPLICATION ).
		//			IF YOU NEED TO CALL CWMP3 FUNCTIONS FROM CALLBACK, USE NON BLOCKING MESSAGES.
		//
		//			BlOCKING MESSAGE IS ALWAYS SENT BEFORE NON BLOCKING MESSAGE.
		//
		//			 This parameter can be any combination of the following values:

		//				MP3_MSG_ALL					- enable all callback messages ( blocking and non blocking )
		//				MP3_MSG_ALL_ASYNC			- enable all non blocking messages
		//				MP3_MSG_ALL_SYNC			- enable all blocking messages
		//
		//
		//				blocking messages:
		//
		//				MP3_MSG_STOP				- send this message when decoding thread ends
		//				MP3_MSG_PLAY				- send this message when decoding thread starts
		//				MP3_MSG_ENTER_LOOP			- send this message wneh decoding thread enters loop
		//				MP3_MSG_EXIT_LOOP			- send this message when decoding thread leaves  loop
		//				MP3_MSG_ENTER_FADE_OUT		- send this mesage when decoding thread enters fade out interval
		//				MP3_MSG_EXIT_FADE_OUT		- send this mesage when decoding thread leaves fade out interval
		//				MP3_MSG_ENTER_FADE_IN		- send this mesage when decoding thread enters fade in interval
		//				MP3_MSG_EXIT_FADE_IN		- send this mesage when decoding thread leaves fade out interval
		//				MP3_MSG_WAVE_BUFFER			- send this message when decoding thread is about to send decoded data to soundcard
		//				MP3_MSG_STREAM_BUFFER_DONE	- send this message when one or more buffers are done in managed stream
		//				MP3_MSG_STREAM_OUT_OF_DATA	- send this message when managed stream runs out of data


		//				non blocking messages ( async)

		//
		//				MP3_MSG_STOP_ASYNC				- send this message when decoding thread ends
		//				MP3_MSG_PLAY_ASYNC				- send this message when decoding thread starts
		//				MP3_MSG_ENTER_LOOP_ASYNC			- send this message wneh decoding thread enters loop
		//				MP3_MSG_EXIT_LOOP_ASYNC			- send this message when decoding thread leaves  loop
		//				MP3_MSG_ENTER_FADE_OUT_ASYNC		- send this mesage when decoding thread enters fade out interval
		//				MP3_MSG_EXIT_FADE_OUT_ASYNC		- send this mesage when decoding thread leaves fade out interval
		//				MP3_MSG_ENTER_FADE_IN_ASYNC		- send this mesage when decoding thread enters fade in interval
		//				MP3_MSG_EXIT_FADE_IN_ASYNC		- send this mesage when decoding thread leaves fade out interval
		//				MP3_MSG_WAVE_BUFFER_ASYNC		- send this message when decoding thread is about to send decoded data to soundcard
		//				MP3_MSG_STREAM_BUFFER_DONE_ASYNC	- send this message when one or more buffers are done in managed stream
		//				MP3_MSG_STREAM_OUT_OF_DATA_ASYNC	- send this message when managed stream runs out of data
		//

		//
		//
		//
		//	RETURN VALUES:
		//		Return value depends on message. See Remarks section
		//
		//	REMARKS:
		//
		//  NOTE:
		//	Callback function must have __stdcall calling convention
		//	Callback function prototype:
		//  int __stdcall callback_func(unsigned int message, unsigned int param1, unsigned int param2);
		//
		//	NOTE:
		//		DON'T CALL CWMP3 FUNCTIONS FROM BLOCKING CALLBACK MESSAGES BECAUSE YOU WILL FREEZE
		//		DECODING THREAD AND CALLING THREAD ( YOUR APPLICATION ).
		//		IF YOU NEED TO CALL CWMP3 FUNCTIONS FROM CALLBACK, USE NON BLOCKING MESSAGES.
		//
		//
		//
		// callback function parameters for message:
		//
		
		// =====================================================================================	
		// NON BLOCKING MESSAGES ( ASYNC )
		// =====================================================================================	

		//	MP3_MSG_PLAY_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		Return value has no effect.
		//
		//
		//--------------------------------------------------------------------------------------
		//
		//	MP3_MSG_STOP_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_LOOP_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_LOOP_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.
		
		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_FADE_OUT_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_FADE_OUT_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

				//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_FADE_IN_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_FADE_IN_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.


		//--------------------------------------------------------------------------------------

		//	MP3_MSG_STREAM_BUFFER_DONE_ASYNC
		//		param1		- number of remaining bufferes in stream
		//		param2		- number of remaining bytes in stream
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_STREAM_OUT_OF_DATA_ASYNC
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.



		// =====================================================================================	
		// BLOCKING MESSAGES ( SYNC )
		// =====================================================================================	

		//	MP3_MSG_PLAY
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		0	- thread continue to play
		//		1	- thread exits, playing isn't started at all
		//
		//	NOTE:
		//		Don't call Play, PlayLoop or ReverseMode from this message because you will
		//		enter MP3_MSG_PLAY_BLOCKING callback loop.
		//
		//--------------------------------------------------------------------------------------
		//
		//	MP3_MSG_STOP
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_LOOP
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		0	- continue loop playing
		//		1	- exit loop and continue playing normal

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_LOOP
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_FADE_OUT
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		0	- continue fade out
		//		1	- exit fade out, fade out has no effect


		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_FADE_OUT
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_ENTER_FADE_IN
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//   Return Value
		//		0	- continue fade in
		//		1	- exit fade in, fade in has no effect


		//--------------------------------------------------------------------------------------

		//	MP3_MSG_EXIT_FADE_IN
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		Return value has no effect.

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_WAVE_BUFFER
		//		param1	- pointer to memory with PCM wave decoded data ( 16 bit samples )
		//		param2	- size, in bytes, of memory pointed by param1 ( in bytes )
		//	  Return Value
		//		0	-  data will be sent to soundcard.
		//		1	-  data will not be sent to soundcard 
		//		2	-  data will not be sent to soundcard and decoding thread will end

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_WAVE_BUFFER
		//		param1	- pointer to memory with PCM wave decoded data ( 16 bit samples )
		//		param2	- size, in bytes, of memory pointed by param1 ( in bytes )
		//	  Return Value
		//		0	-  data will be sent to soundcard.
		//		1	-  data will not be sent to soundcard 
		//		2	-  data will not be sent to soundcard and decoding thread will end

		//--------------------------------------------------------------------------------------

		//	MP3_MSG_STREAM_BUFFER_DONE
		//		param1		- number of remaining bufferes in stream
		//		param2		- number of remaining bytes in stream
		//	  Return Value
		//		Return value has no effect.


		//--------------------------------------------------------------------------------------

		//	MP3_MSG_STREAM_OUT_OF_DATA
		//		param1 = 0;	// not used, always is 0
		//		param2 = 0;	// not used, always is 0
		//	  Return Value
		//		0	-  wait for PushDataToStream
		//		1	-  stop playing, exit decoding thread
		//		2	-  don't wait, try to load new data from queue ( danger of endless loop !!! )




	
// ==============================================================================================================



// VISUAL BASIC FIX

// get ID3 field

W_DECLSPEC int __stdcall Mp3_GetID3Field(
							char *objptr,		// Pointer to class instance.
							int nId3Version,	// ID3 version
							int nFieldID,		// field ID
							char *pBuffer,		// Pointer to buffer receiving NULL terminated string.
							int nSize			// Size of receiving buffer
);		
	
//
//	PARAMETERS:
//		objptr
//			Pointer to class instance.
//
//		nId3Version
//			Specifies ID3 version. Value ID3_VERSION1 loads ID3v1 data.
//			Value ID3_VERSION2 loads ID3v2 data.
//
//		nFieldID
//			Specifies ID3 field you need to retreivie.
//
//			ID3_TITLE		- retreive song title
//			ID3_ARTIST		- retreive song artist
//			ID3_ALBUM		- retreive album
//			ID3_GENRE		- retreive genre
//			ID3_COMMENT		- retreive comment
//			ID3_TRACKNUM	- retreive track number 
//			ID3_YEAR		- retreive year
//			
//
//		pBuffer
//			Pointer to buffer receiving NULL terminated ID3 field string.	
//			If this value is zero, the function returns the required buffer size, in bytes,
//			and makes no use of the pBuffer. 
//
//		nSize
//			Size of receiving buffer.
//			If this value is zero, the function returns the required buffer size, in bytes,
//			and makes no use of the pBuffer. 
//
//	RETURN VALUES:
//		If pBuffer or nSize is zero, the function returns the required buffer size, in bytes.
//		If the function succeeds, the return value is number of bytes copied into pBuffer.
//		If function fails, return value is 0;
//

// =============================================================================================================




		// open mp3 file from disk to play, seek from begining of file, set custom file size

W_DECLSPEC int __stdcall Mp3_OpenFile(
			char *objptr,					// Pointer to class instance.
			const char *sFileName,			// pointer to name of the file 
			int nWaveBufferLengthMs,		// size of wave buffer ( milliseconds ), minimal 200
			unsigned int nSeekFromStart,	// number of bytes to move file pointer from file beginning	 
			unsigned int nFileSize			// size of file counting from nSeekFromStart position
);
		
		//	PARAMETERS:
		//
		//		objptr
		//			Pointer to class instance.

		//		sFileName		
		//			Points to a null-terminated string that specifies the name of the file.
		//		
		//		nWaveBufferLengthMs
		//			Size of wave buffer in milliseconds, must be at least 200. Smaller buffer produce
		//			smaller delay in effects ( echo, equalizer, fade .. ) and larger buffer produces
		//			larger delay in sound effects. But with larger buffer you have more data ready to
		//			play and this prevents buffer underrun. If you have problems with sound, maybe 
		//			this buffer is too small.
		//
		//		nSeekFromStart
		//			Number of bytes to move file pointer from file beginning. You can skip data at file beginning
		//			and move pointer to higher position.
		//
		//		nFileSize
		//			Size of file counting from nSeekFromStart position. This value can be smaller than the rest size of
		//			file. This enables you to play only fragment of the file. 
		//			If this value is 0, function opens file from nSeekFromStart to the end of file.
		//			If this value is greater than the rest of file, function fails and returns 0.
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string


// =============================================================================================================

		// open  stream
    	
W_DECLSPEC int __stdcall Mp3_OpenStream(
			char *objptr,				// Pointer to class instance.
			int fBuffered,				// flag specifying buffered stream
			int fManaged,				// flag flag for enabling or disabling managed stream
			const void *sMemStream,		// pointer to first memory block
			unsigned int nStreamSize,	// size of memory block in bytes
			int nWaveBufferLengthMs		// size of wave buffer ( milliseconds ), minimal 200
);
	
		//	PARAMETERS:
		//
		//		objptr
		//			Pointer to class instance.
		//
		//		fBuffered
		//			Specifies if stream is buffered stream.
		//			Value 1 specifies buffered stream. This type of stream makes copies of data
		//			you push into stream.
		//
		//			Value 0 specifies unbuffered stream. This type of stream only takes pointer
		//			to memory data. You are responsible for this data.			
		//	
		//		fManaged
		//			Specifies if stream is managed or unmanaged.
		//			Value 1 specifies managed stream. You can add more data into this type
		//			of stream with PushDataToStream. See Remarks section.
		//			NOTE: You cant seek position on this type of stream. Functions Seek will fail.
		//
		//			Value 0 specifies unmanaged stream. You can't add more data into this type of stream.
		//			This stream taks only one data block specified by sMemStream parameter.
		//			NOTE: You can seek on this type of stream.		
		//
		//		sMemStream		
		//			Points to a  memory block. If this value is 0 function fails.
		//
		//		nStreamSize
		//			Size of memory block, in bytes,  with mp3 data. If this value is 0 function fails.
		//		
		//		nWaveBufferLengthMs
		//			Size of wave buffer in milliseconds, must be at least 200. Smaller buffer produce
		//			smaller delay in effects ( echo, equalizer, fade .. ) and larger buffer produces
		//			larger delay in sound effects. But with larger buffer you have more data ready to
		//			play and this prevents buffer underrun. If you have problems with sound, maybe 
		//			this buffer is too small.
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//		First block of data needs to be large enough and must have at least one valid mp3 frame.
		//		If this function fails, call this function again with larger block of data or with another
		//		block of data.
		//		For 128 kbps at 44100 Hz you need at least 426 bytes without ID3v2 data at stream start.
		//		If input block is too small, function will fail. Then you need to send larger block.
		//		Optimal value is 10 KB. 
		//
		//		Buffered stream:
		//		In buffered stream, all data you send in stream are buffered internaly by WMp3 class and
		//		class is responsible for memory management of this data.
		//
		//		Unbuffered strem:
		//		In non buffered stream you send only pointer to data into stream. You are responsible
		//		for this data and memory management of this data. See IsStreamDataFree function.
		//		
		//
		//		Managed stream:
		//		With this function you sends first block of data. With PushDataToStream you will send
		//		next block of data into stream. If stream runs out of data it waits until you push more
		//		data into stream. You can turn off this behavior pushing 0 buffer into stream PushDataToStream(0,0); 
		//		If last pushed buffer into stream was 0 buffer, when stream runs out of data,
		//		it stops.
		//		NOTE: You CAN'T seek on this type of stream.
		//
		//		Not managed stream:
		//		You can't add more data into this type of stream. Only data you can add into
		//		this type of stream are data added with OpenStream function as sMemStream parameter.
		//		NOTE: You CAN seek on this stream because there is only one memory block in stream.



// =============================================================================================================

		// open mp3 stream from application resource

W_DECLSPEC int __stdcall Mp3_OpenResource(
			char *objptr,				// Pointer to class instance.
			HMODULE hModule,				// resource-module handle 
			const char *sResName,			// pointer to resource name 
			const char *sResType,			// pointer to resource type 
			int nWaveBufferLengthMs,		// size of wave buffer ( milliseconds ), minimal 200
			unsigned int nSeekFromStart,	// number of bytes to move file pointer from beginning of resource block	
			unsigned int nResourceSize		// size of resource block counting from nSeekFromStart position
);

		//	PARAMETERS:
		//	
		//		objptr
		//			Pointer to class instance.
		//	
		//		hModule
		//			A handle to the module whose executable file contains the resource. 
		//			A value of NULL specifies the module handle associated with the image file
		//			that the operating system used to create the current process.
		//
		//		sResName
		//			Specifies the name of the resource. For more information, see the Remarks section
		//
		//		sResType
		//			Specifies the resource type. For more information, see the Remarks section.
		//			For standard resource types, this parameter can be RT_RCDATA.
		//
		//		nWaveBufferLengthMs
		//			Size of wave buffer in milliseconds, must be at least 200. Smaller buffer produce
		//			smaller delay in effects ( echo, equalizer, fade .. ) and larger buffer produces
		//			larger delay in sound effects. But with larger buffer you have more data ready to
		//			play and this prevents buffer underrun. If you have problems with sound, maybe 
		//			this buffer is too small.
		//
		//		nSeekFromStart
		//			Number of bytes to move pointer from beginning of resource block. You can skip data
		//			at the beginning and move pointer to higher position.
		//
		//		nResourceSize
		//			Size of resource block counting from nSeekFromStart position. This value can be smaller
		//			than the rest size of resource block. This enables you to play only fragment of the block. 
		//			If this value is 0, function opens resource from nSeekFromStart to the end of resource.
		//			If this value is greater than the rest size of resource, function fails and returns 0.
		//
		//	RETURN VALUES:
		//
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARKS:
		//
		//	If the high-order word of the sResName or sResType parameter is zero,
		//	the low-order word specifies the integer identifier of the name or type of the given resource.
		//	Otherwise, those parameters are long pointers to null-terminated strings.
		//	If the first character of the string is a pound sign (#), the remaining characters
		//	represent a decimal number that specifies the integer identifier of the resource's name or type.
		//	For example, the string "#258" represents the integer identifier 258. 
		//
		//	The MAKEINTRESOURCE macro converts an integer value to a resource type compatible
		//	with Win32 resource-management functions.
		//	This macro is used in place of a string containing the name of the resource. 



// =============================================================================================================

		// close mp3
		
W_DECLSPEC int __stdcall Mp3_Close(
							char *objptr	// Pointer to class instance.
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function stops playing. Memory is reallocated,  stream buffer are free.
		//		You need to call Open functions again to open new mp3 file or stream or resource ...		 
	


// ==============================================================================================================

		// enumerate waveform-audio output devices
    	
W_DECLSPEC int __stdcall Mp3_EnumerateWaveOut(
										char *objptr	// Pointer to class instance.
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//	RETURN VALUES:
		//		Returns the number of wave out devices.
		//		A return value of zero means that no devices are present or that an error occurred.
		//
		//	REMARKS:
		//

	
// ==============================================================================================================


		// enumerate waveform-audio output devices
    	
W_DECLSPEC int __stdcall Mp3_GetWaveOutInfo(
							char *objptr,				// Pointer to class instance.
							unsigned int nIndex,		// index of wave out device
							WAVEOUT_INFO *pWaveOutInfo	// pointer to  WAVEOUT_INFO structure
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		nIndex
		//			Index of wave out device. Call EnumerateWaveOut to get number of wave out devices.
		//			Then you can retreive information for each device using index value from 0 to
		//			device number - 1.
		//	
		//		pWaveOutInfo
		//			Pointer to WAVEOUT_INFO structure.
		//			
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		// REMARKS:
		//
		// WAVEOUT_INFO Format values
		//
		// #define FORMAT_1M08	1		// 11.025 kHz, mono, 8-bit
		// #define FORMAT_1M16	2		// 11.025 kHz, mono, 16-bit
		// #define FORMAT_1S08	4		// 11.025 kHz, stereo, 8-bit
		// #define FORMAT_1S16	8		// 11.025 kHz, stereo, 16-bit
		// #define FORMAT_2M08	16		// 22.05 kHz, mono, 8-bit
		// #define FORMAT_2M16	32		// 22.05 kHz, mono, 16-bit
		// #define FORMAT_2S08	64		// 22.05 kHz, stereo, 8-bit
		// #define FORMAT_2S16	128		// 22.05 kHz, stereo, 16-bit
		// #define FORMAT_4M08	256		// 44.1 kHz, mono, 8-bit
		// #define FORMAT_4M16	512		// 44.1 kHz, mono, 16-bit
		// #define FORMAT_4S08	1024	// 44.1 kHz, stereo, 8-bit
		// #define FORMAT_4S16	2048	// 44.1 kHz, stereo, 16-bit

		// WAVEOUT_INFO Support values

		// #define CAPS_LRVOLUME 8			// Supports separate left and right volume control.
		// #define CAPS_PITCH 1				// Supports pitch control.
		// #define CAPS_PLAYBACKRATE 2		// Supports playback rate control.
		// #define CAPS_SYNC 16				// The driver is synchronous and will block while playing a buffer.
		// #define CAPS_VOLUME	4			// Supports volume control.
		// #define CAPS_SAMPLEACCURATE	32	// Returns sample-accurate position information.
		// #define CAPS_DIRECTSOUND 64		// 

		// typedef struct {
		// 	unsigned int ManufacturerID;	// Manufacturer identifier for the device driver for the device.
		// 	unsigned int ProductID;			// Product identifier for the device.
		// 	unsigned int DriverVersion;		// Version number of the device driver for the device.
		// 	unsigned int Formats;			// Standard formats that are supported. Can be a combination of values.
		// 	unsigned int Channels;			// Number specifying whether the device supports mono (1) or stereo (2) output.
		// 	unsigned int Support;			// Optional functionality supported by the device.
		// 	char ProductName[32];			// Product name in a null-terminated string.
		// } WAVEOUT_INFO;

	
// ==============================================================================================================

		// set wave out device
    	
W_DECLSPEC int __stdcall Mp3_SetWaveOutDevice(
							char *objptr,			// Pointer to class instance.
							unsigned int nIndex		// wave out index
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//		
		//		nIndex
		//			Index of wave out device. Call EnumerateWaveOut to get number of wave out devices.
		//			Index value is in range from 0 to device number - 1.
		//
		//			There is special index value WAVE_OUT_WAVE_MAPPER.
		//			This value selects a waveform-audio output device capable of playing the given format.
		//			Default walue for new instance of class is WAVE_OUT_WAVE_MAPPER.		
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function has effect on next call to Play() function.
		//		If you call this function while song is playing there is no effect. 
		//		You need to call Stop and Play again to apply new settings.




		



// =============================================================================================================

		// push new data to managed stream
  	
W_DECLSPEC int __stdcall Mp3_PushDataToStream(
			char *objptr,				// Pointer to class instance.
			const void *sMemNewData,	// pointer to memory block
			unsigned int nNewDataize	// size of memory block in bytes
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		sMemNewData		
		//			Points to a memory block with mp3 data
		//
		//		nStreamSize
		//			Size of memory block (bytes) with mp3 data
		//		 
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//		NOTE: This function works only on managed stream. If you try to push data into
		//		unmanaged stream function returns 0.
		//
		//		This function takes sMemNewData  and push this into stream queue.
		//
		//		Not buffered stream:
		//		If stream is not buffered, this function pushes just pointer to data,
		//		caller is responsible for data pointed by sMemNewData pointer.
		//		Use IsStreamDataFree to check if you can delete or free sMemNewData when this
		//		data are pulled from queue.
		//		You can't use sMemNewData after you call  PushDataToStream. Call IsStreamDataFree to
		//		check if you can destroy this data.
		//
		//		Buffered stream:
		//		If stream is buffered, with this function you will push all data into internal buffer
		//		allocated by WMP3 class. Class is responsible for this internal buffer, and you can
		//		destroy original source buffer.
		//
		//		If stream runs out of data it waits until you push more
		//		data into stream. You can turn off this behavior by pushing 0 buffer into stream PushDataToStream(0,0); 
		//		If last pushed buffer into stream was 0 buffer, when stream runs out of data,
		//		it stops.
		//
		//		PushDataToStream(mem_block, 8000);	// push more data into stream
		//		PushDataToStream(0,0);	// push null block into stream indicating that this is last block


	     

// =============================================================================================================

		// check if sMemNewData is out of stream

W_DECLSPEC int __stdcall Mp3_IsStreamDataFree(
			char *objptr,				// Pointer to class instance.
			const void *sMemNewData		// pointer to memory block
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		sMemNewData		
		//			Points to a memory to check if this pointer is still in stream. 
		//
		//	RETURN VALUES:
		//		1 - sMemNewData isn't in stream anymore, you can use this data, destroy ....
		//		0 - sMemNewData is still in stream, wait
		//
		//	REMARKS:
		//		When you push memory block to not buffered stream with PushDataToStream you need to wait.
		//		Call IsStreamDataFree to check if data are still in stream.
		//
		//		If stream is buffered you can destroy original data because WMp3 class makes copy of
		//		data pushed into stream.
		//
		//		If you call this function on unmanaged stream, return value is always 1.		
		//
		//		mp3->PushDataToStream(tmp, 8000);
		//		if(mp3->IsStreamDataFree(tmp))
		//		{
		//			free(tmp); // or load ne data into this block
		//		}


// =============================================================================================================

		// return number of buffers in  stream, works only on managed streams
    	
W_DECLSPEC int __stdcall Mp3_GetStreamLoad(
			char *objptr,						// Pointer to class instance.
			STREAM_LOAD_INFO *pStreamLoadInfo	// pointer to STREAM_LOAD_INFO structure
);
	     
		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pStreamLoadInfo
		//			Pointer to structure receiving informations about stream load. 
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//		Use this function to to check if stream is low with data, so you can push
		//		more data into stream  
		//
		//   typedef struct {
		//		unsigned int NumberOfBuffers;		// number of buffers currently in stream
		//		unsigned int NumberOfBytes;			// number of bytes currently in stream
		//		unsigned int NumberOfMilliseconds;	// number of milliseconds currently in stream
		//	} STREAM_LOAD_INFO;  
		//
		//	  NumberOfMilliseconds
		//		Size of data in stream converted into milliseconds.
		//		This value is average value and isn't precise.	
        



// ----------------------------------------------------------------------------------------

		// start playing from current position

W_DECLSPEC int __stdcall Mp3_Play(
			char *objptr	// Pointer to class instance.
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//


// =============================================================================================================

		// stop playing

W_DECLSPEC int __stdcall Mp3_Stop(
			char *objptr	// Pointer to class instance.
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string

 
// ============================================================================================================

		// play loop

W_DECLSPEC int __stdcall Mp3_PlayLoop(
			char *objptr,				// Pointer to class instance.
			int fFormatStartTime,		// flag specifying start time format
			MP3_TIME *pStartTime,		// pointer to MP3_TIME structure specifying start time
			int fFormatEndTime,			// flag specifying end time format
			MP3_TIME *pEndTime,			// pointer to MP3_TIME structure specifying end time
			unsigned int nNumOfRepeat	// number of loop iterations
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fFormatStartTime
		//			Flag specifying time format of pStartTime.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pStartTime		
		//			Pointer to MP3_TIME structure with loop starting position.
		//
		//		fFormatEndTime
		//			Flag specifying time format of pEndTime.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pEndTime		
		//			Pointer to MP3_TIME structure with loop ending position.
		//
		//		nNumOfRepeat		
		//			Number of loop iterations.
		//
		//		 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function starts playing. If song is already playing, this function seeks to
		//		pStartTime position, makes nNumOfRepeat iterations and then plays forward.
		//


// =============================================================================================================


		// seek position counting from song start

W_DECLSPEC int __stdcall Mp3_Seek(
			char *objptr,				// Pointer to class instance.
			int fFormat,		// flag specifying time format
			MP3_TIME *pTime,	// pointer to MP3_TIME structure specifying time
			int nMoveMethod	// how to move 
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fFormat
		//			Flag specifying time format used to seek position.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pTime		
		//			Pointer to MP3_TIME structure with new position.
		//
		//		nMoveMethod
		//			Specifies the starting point and direction. This parameter can be one of the following values:
		//
		//			SONG_BEGIN
		//				The starting point is zero or the beginning of the song.
		//				If SONG_BEGIN is specified, pTime is interpreted as a new position
		//				in song counting from song start.
		//	 
		//			SONG_END
		//				The starting point is end of song.
		//				If SONG_END is specified, pTime is interpreted as a new position
		//				in song counting backward from the end of song.
		//
		//			SONG_CURRENT_FORWARD
		//				The current position of song is starting point. Parameter pTime is interpreted
		//				as time offset counting from current position to the end of song.
		//
		//			SONG_CURRENT_BACKWARD
		//				The current position of song is starting point. Parameter pTime is interpreted
		//				as time offset counting from current position to the start of song.
		//	 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function stops playing. You need to call Play  to start playing after Seek function		
		//
		//
		// typedef struct {
		//	unsigned int ms;				// number of milliseconds 
		//	unsigned int sec;				// number of seconds
		//	unsigned int bytes;				// number of bytes
		//	unsigned int frames;			// number of frames
		//	unsigned int hms_hour;			// HMS format: hours
		//	unsigned int hms_minute;		// HMS format:minutes
		//	unsigned int hms_second;		// HMS format:seconds
		//	unsigned int hms_millisecond;	// HMS format: milliseconds
		// } MP3_TIME;




// =============================================================================================================

		// pause playing

W_DECLSPEC int __stdcall Mp3_Pause(
			char *objptr		// Pointer to class instance.
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string

// =============================================================================================================

		// continue paused playing

W_DECLSPEC int __stdcall Mp3_Resume(
			char *objptr	// Pointer to class instance.
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string


// =============================================================================================================
		// get current position


W_DECLSPEC int __stdcall Mp3_GetPosition(
			char *objptr,	// Pointer to class instance.
			MP3_TIME *pTime	// pointer to MP3_TIME structure
);

		
		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pTime		
		//			Pointer to MP3_TIME structure
		//
		///	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARKS:
		//		This function returns song position in 3 different formats at once:
		//		Format1: milliseconds ( ms )
		//		Format2: seconds ( sec )
		//		Format3: HMS format ( song position presented by hours, minutes, seconds and milliseconds )
		//
		//		
		//
		//
		// typedef struct {
		//	unsigned int ms;				// number of milliseconds ( song position in milliseconds )
		//	unsigned int sec;				// number of seconds ( song position in seconds ) 
		//	unsigned int bytes;				// number of bytes
		//	unsigned int frames;			// number of frames
		//	unsigned int hms_hour;			// HMS format: hours
		//	unsigned int hms_minute;		// HMS format:minutes
		//	unsigned int hms_second;		// HMS format:seconds
		//	unsigned int hms_millisecond;	// HMS format: milliseconds
		// } MP3_TIME;

// =============================================================================================================

		// use internal volume control, modify wave samples, don't change wave out mixer volume

W_DECLSPEC int __stdcall Mp3_InternalVolume(
			char *objptr,	// Pointer to class instance.
			int fEnable		// flag for enabling or disabling internal volume control ( disabled by default )
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fEnable
		//			Specifies whether to enable or disable internal volume control.
		//			If this parameter is 1, internal volume control is enabled.
		//			If the parameter is 0,  internal volume control is disabled ( default ). 
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		If internal volume control is enabled, audio volume is controled internally by
		//		modifying audio samples. Using internal volume control, you can separately change volume
		//		for each instance of class.

// =============================================================================================================

        // Set output volume

W_DECLSPEC int __stdcall Mp3_SetVolume(
			char *objptr,				// Pointer to class instance.
			unsigned int nLeftVolume,	// left channel volume
			unsigned int nRightVolume	// right channel volume
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		nLeftVolume
		//			Specifies volume for left channel. Volume range is from 0 to 100
		//
		//		nRightVolume
		//			Specifies volume for right channel. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		If internal volume control is enabled, audio samples are modifyed to control volume.
		//		Wave output volume at soundcard stays unchanged.
		//		If internal volume control is disabled, this function changes wave output volume of
		//		sound card and that has affect on all playing sounds on computer.  


// =============================================================================================================-

		// get output volume

W_DECLSPEC int __stdcall Mp3_GetVolume(
			char *objptr,				// Pointer to class instance.
			unsigned int *pnLeftVolume,	// pointer to variable receiving left volume
			unsigned int *pnRightVolume	// pointer to variable receiving right volume
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pnLeftVolume
		//			Pointer to variable receiving left volume. Volume range is from 0 to 100
		//
		//		pnRightVolume
		//			Pointer to variable receiving right volume. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		If internal volume control is enabled, you get internal volume levels.
		//		If internal volume control is disabled, you get volume level of wave out device.

// =============================================================================================================

        // get MPEG version

W_DECLSPEC int __stdcall Mp3_GetMp3Info(
			char *objptr,			// Pointer to class instance.
			MP3_STREAM_INFO *pInfo	// pointer to MP3_STREAM_INFO structure
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pInfo
		//			Pointer to MP3_STREAM_INFO structure receiving info about mp3 stream
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//	typedef struct {
		//		char *sMPEGVersion;			// Pointer to NULL terminated string specifying MPEG version.
		//		char *sLayerVersion;		// Pointer to NULL terminated string specifying MPEG Layer version.
		//		char *sChannelMode;			// Pointer to NULL terminated string specifying channel mode.
		//		char *sEmphasis;			// Pointer to NULL terminated string specifying emphasis.
		//		unsigned int nSamplingRate;	// Samiling rate in Hz
		//		unsigned int nHeaderStart;	// Position of first valid frame form beginning of file or stream ( in bytes )
		//		unsigned int nChannelNumber;// Channel number
		//		unsigned int fVBR;			// 1 - song is VBR, 0 - song i CBR
		//		unsigned int nBitrate;	// For CBR stream returns stream bitrate, for VBR stream returns average bitrate ( kbps )
		//	} MP3_STREAM_INFO;

// =============================================================================================================

		// get song length
	
W_DECLSPEC int  __stdcall Mp3_GetSongLength(
			char *objptr,		// Pointer to class instance.
			MP3_TIME *pLength	// pointer to MP3_TIME structure
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pTime		
		//			Pointer to MP3_TIME structure
		//
		///	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARKS:
		//		This function returns song length in 3 different formats at once:
		//		Format1: milliseconds ( ms )
		//		Format2: seconds ( sec )
		//		Format3: HMS format ( song length presented by hours, minutes, seconds and milliseconds )
		//
		//		
		//
		//
		// typedef struct {
		//	unsigned int ms;				// number of milliseconds ( whole song length in milliseconds )
		//	unsigned int sec;				// number of seconds ( whole song length in seconds ) 
		//	unsigned int bytes;				// number of bytes
		//	unsigned int frames;			// number of frames
		//	unsigned int hms_hour;			// HMS format: hours
		//	unsigned int hms_minute;		// HMS format:minutes
		//	unsigned int hms_second;		// HMS format:seconds
		//	unsigned int hms_millisecond;	// HMS format: milliseconds
		// } MP3_TIME;



// =============================================================================================================

		// get bitrate 

W_DECLSPEC int __stdcall Mp3_GetBitrate(
			char *objptr,	// Pointer to class instance.
			int fAverage	// specifies average bitrate of decoded frame  or current bitrate of decoded frame
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fAverage
		//			Value 1 specifies that function returns average bitrate of last decoded frame.
		//			Value 0 specifies that function returns real bitrate of last decoded frame.
		//
		//	RETURN VALUES:
		//		Return bitrate in kbps.


// =============================================================================================================

		// get current status 

W_DECLSPEC int __stdcall Mp3_GetStatus(
			char *objptr,		// Pointer to class instance.
			MP3_STATUS *pStatus	// pointer to MP3_STATUS structure
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//
		//		pStatus		
		//			Pointer to MP3_STATUS structure receiving status informations.
		//
		//	RETURN VALUES:
		//		1	- all OK
		//		0	- error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//typedef struct {
		//	int fPlay;			// if song is playing this value is nonzero 
		//	int fPause;			// if song is paused this value is nonzero 
		//	int fStop;			// if song is stoped this value is nonzero 
		//	int fEcho;			// if echo is enabled this value is nonzero 
		//	int nSfxMode;		// return current echo mode
		//	int fExternalEQ;	// if external equalizer is enabled this value is nonzero 
		//	int fInternalEQ;	// if internal equalizer is enabled this value is nonzero	
		//	int fVocalCut;		// if vocal cut is enabled this value is nonzero
		//	int fChannelMix;	// if channel mixing is enabled this value is nonzero
		//	int fFadeIn;		// if song is in "fade in" interval this value is nonzero
		//	int fFadeOut;		// if song is in "fade out" interval this value is nonzero
		//	int fInternalVolume;// if internal volume is enabled this value is nonzero
		//	int fLoop;			// if song is in loop this value is nonzero
		//	int fReverse;		// if song is in reverse mode this value is nonzero
		//	int reservd1;		// reserved, this value is undefined
		//	int reservd2;		// reserved, this value is undefined
		//	int reservd3;		// reserved, this value is undefined
		//	int reservd4;		// reserved, this value is undefined
		//} MP3_STATUS;
		//
		//
		// MP3_STATUS status;
		// mp3->GetStatus(&status)
		//
		// if(status.play)
		//	printf("Playing song");



// =============================================================================================================

		// mix left and right channel into one mono channel
	
W_DECLSPEC int __stdcall Mp3_MixChannels(
			char *objptr,				// Pointer to class instance.
			int fEnable,				// flag for enabling or disabling channel mixing
			unsigned int nLeftPercent,	// percent of left channel in resulting sound ( 0 - 100 )
			unsigned int nRightPercent	// percent of right channel in resulting sound ( 0 - 100 )
);
		
		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fEnable
		//			Enables or disables channel mixing. Value 1 enables mixing, value 0 disables mixing.
		//
		//		nLeftPercent
		//			Percent of left channel in resulting sound. Range is from 0 to 100.	
		//
		//		nRightPercent
		//			Percent of right channel in resulting sound. Range is from 0 to 100.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		If you mix 50 % left and 50 % right you get MONO output
		//		If you mix 100 % left and 0 % right you get LEFT channel output
		//		If you mix 0 % left and 100 % right you get RIGHT channel output
		//
		// e.g.
		//
		//	mp3->MixChannels(1, 50,50); // this will convert stereo to mono
		//
		//


// =============================================================================================================

		// return VU data for left and right channel

W_DECLSPEC int __stdcall Mp3_GetVUData(
			char *objptr,					// Pointer to class instance.
			unsigned int *pnLeftChannel,	// pointer to integer receiving left channel data
			unsigned int *pnRightChannel	// pointer to integer receiving right channel data
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pnLeftChannel
		//			Pointer to integer receiving left channel VU level. Range is from 0 to 100
		//
		//		pnRightChannel
		//			Pointer to integer receiving right channel VU level. Range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string

// =============================================================================================================

		// enable simple vocal cut

W_DECLSPEC int __stdcall Mp3_VocalCut(
			char *objptr,	// Pointer to class instance.
			int fEnable		// flag for enabling or disabling vocal cut
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fEnable
		//			Enables or disables vocal cut. Value 1 enables vocal cut, value 0 disables vocal cut
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		This function has effect only on stereo channel mode.


// =============================================================================================================

		// fade volume

W_DECLSPEC int __stdcall Mp3_FadeVolume(
			char *objptr,		// Pointer to class instance.
			int fMode,			// specifies fade mode ( fade in ot fade out )
			int fFormat,		// flag specifying time format
			MP3_TIME *pTime	// pointer to MP3_TIME structure specifying fade interval
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fMode
		//			Specifies fade mode. This parameter can be one of the following values:
		//
		//			FADE_IN
		//				Using this mode, in specified interval volume will rise up
		//				from fade out volume to current volume ( maximum ) 
		//				This mode restores "fade out" volume to normal volume.
		//
		//			FADE_IN
		//				Using this mode, in specified interval volume will drop down
		//				from current volume to 0 (silence) 
		//				Use FADE_IN mode to restore volume back to normal.				
		//
		//		fFormat
		//			Flag specifying time format.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pTime		
		//			Pointer to MP3_TIME structure with fade interval.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		Stop() and Seek() functions cancel fade effect

// =============================================================================================================

// fade volume 

W_DECLSPEC int __stdcall Mp3_FadeVolumeEx(
			char *objptr,		// Pointer to class instance.
			int fMode,			// specifies fade mode ( fade in or fade out )
			int fFormat,		// flag specifying time format
			MP3_TIME *pTime		// pointer to MP3_TIME structure specifying fade interval
		);

		//	PARAMETERS:
		//		fMode
		//			Specifies fade mode. This parameter can be one of the following values:
		//
		//			FADE_IN
		//				Using this mode, volume will drop down to 0 (silence) and then rise up
		//				 to current volume ( maximum ) in specified interval 
		//
		//			FADE_IN
		//				Using this mode, volume will be set to maximum and then drop down
		//				from current volume to 0 (silence)  in specified interval.
		//				Use FADE_IN mode to restore volume back to normal.				
		//
		//		fFormat
		//			Flag specifying time format.
		//			TIME_FORMAT_MS	specifies that ms member of MP3_TIME is valid
		//			TIME_FORMAT_SEC specifies that sec member of MP3_TIME is valid
		//			TIME_FORMAT_HMS specifies that hms_hour, hms_minute,hms_second and hms_millisecond members
		//			of MP3_TIME are valid.
		//
		//		pTime		
		//			Pointer to MP3_TIME structure with fade interval.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		Stop() and Seek() functions cancel fade effect

// =============================================================================================================


		// enable equalizer or disable equalizer

W_DECLSPEC int __stdcall Mp3_EnableEQ(
			char *objptr,	// Pointer to class instance.
			int fEnable,	//  flag for enabling or disabling equalizer
			int fExternal	//  flag for internal or external equalizer
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fEnable
		//			Specifies whether to enable or disable equalizer.
		//			Value 1 enables equalizer, 0 disables equalizer.
		//
		//		fExternal
		//			Specifies whether to enable or disable internal or external equalizer.
		//			Value 1 specifies external built-in Shibatch Super Equalizer,
		//			slow but accurate with additional functions.
		//			Value 0 specifies libmad internal subband equalizer, fast equalizer,
		//			not accurate.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//		There are two equalizers in this class. Internal equalizer is based on
		//		libmad decoding	engine and this equalizer is part of decoding process.
		//		External Shibatch Super Equalizer is based on advanced equalizer engine and
		//		modifies audio samples after samples are decoded from mp3 frames. This eualizer
		//		has multiple features. See function CreateEqBands.
		//
		//		You can enable both equalizers.



// =============================================================================================================


		// create new equalizer bands for external equalizer

W_DECLSPEC int __stdcall Mp3_CreateEqBands(
			char *objptr,		// Pointer to class instance.
			int *pnFreqPoint,	// pointer to array of integers
			int nNumOfPoints	// number of elements in pnFreqPoint array( min value is 2)
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pnFreqPoint
		//			Specifies frequency points for band limits. Frequency band has lower and upper point.
		//			For one band you need 2 points. Two bands needs 3 points because middle point is
		//			upper point for first band and lower point for second band at the same time.
		//			Number of created bands is nNumOfPoints - 1
		//	
		//		nNumOfPoints
		//			Number of points in pnFreqPoint. Must be at least 2 because you need 2 points
		//			to define first band.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		Use this function to specify new bands. You need to specify limit frequencies for bands.
		//		Lowest frequency is 0 and highest frequency is EQ_MAX_FREQ (samplerate). 
		//		Highest frequency depends on samplerate. If you set highest frequency to EQ_MAX_FREQ then highest
		//		fequency is set to samplerate frequency.
		//		Basicly, you need to specify frequency points to divide whole band into subbands.
		//		You don't need to start from 0 Hz. First band can start from higher frequency. And you don't need to end
		//		with EQ_MAX_FREQ. You can end with lower frequency.
		//
		//		Number of bands created is nNumOfPoints - 1
		//
		//		Class has 10 frequency bands by default. You can create your bands.
		//		There is no limit on number of bands.
		//
		//	Default bands on new created class: 
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		// Example 1: ( create your frequency bands )
		//
		//	int freq_points[7] = { 100, 400, 1000, 3000, 5000, 10000, 15000};
		//	CreateEqBands(freq_points, 7);
		//
		// this function creates 6 bands: 
		//
		//			band:		        0     1      2      3      4       5       
		//			FreqPoint (Hz): 100 - 400 - 1000 - 3000 - 5000 - 10000 - 15000 
		//
		//	In this example band 0 controls range 100 - 400 Hz. Range 0 - 100 isn't available with
		//	this set of FreqPoint. Also range 1500 - EQ_MAX_FREQ isn't available with this set of FreqPoint
		//
		//
		// Example 2: ( create your frequency bands )
		//
		//	int freq_points[7] = { 0, 400, 1000, 3000, 5000, 10000, 15000};
		//	CreateEqBands(freq_points, 7);
		//
		// this function creates 6 bands: 
		//
		//			band:		       0     1      2      3      4       5       
		//			FreqPoint (Hz):  0 - 400 - 1000 - 3000 - 5000 - 10000 - 15000 
		//
		//	In this example band 0 controls range 0 - 400 Hz.
		//	Range 1500 - EQ_MAX_FREQ isn't available with this set of FreqPoint


// =============================================================================================================

		// get eq bands limit frequencies for external equelizer

W_DECLSPEC int __stdcall Mp3_GetEqBands(
			char *objptr,		// Pointer to class instance.
			int *pnFreqPoint	// pointer to array of integers
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pnFreqPoint
		//			Pointer to array of integers receiving band limit points.
		//			If this value is NULL, the function returns the required number of elements
		//			in pnFreqPoint array.
		//
		//	RETURN VALUES:
		//		Function returns the required number of elements
		//			in pnFreqPoint array.
		//
		//	REMARKS:
		//		New created class has 11 frequency points ( for 10 bands ) 	
		//
		//	Default bands on new created class: 
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ


// =============================================================================================================

		// set equalizer data

W_DECLSPEC int __stdcall Mp3_SetEQParam(
			char *objptr,		// Pointer to class instance.
			int fExternal,		// flag specifying internal or external equalizer
			int nPreAmpGain,	// preamp gain
			int *pnBandGain,	// array of gain for each band
			int nNumberOfBands	// number of frequency bands
);


		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//
		//		fExternal		
		//			Specifies external or internal equalizer.
		//			Value 1 specifies external (advanced) equalizer.
		//			Value 0 specifies internal equalizer 
		//
		//		nPreAmpGain		
		//			Preamp gain in decibels. Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands.
		//
		//		pnBandGain		
		//			Array of gain for each band ( decibels ). Positive values boost volume,
		//			negative value drops volume.
		//
		//		nNumberOfBands	 
		//			Number of frequency bands. Class has by default 10 eq bands, but you can create
		//			new bands using CreateEqBands function ( only for external equalizer ).
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//	Default bands on new created class: 
		//
		//			SUBBAND FREQUENCY for external Shibatch Super Equalizer
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		//
		//
		//			SUBBAND FREQUENCY for libmad internal  equalizer
		//
		//			index:		       0     1      2      3      4      5      6        7       8       9 
		//			FreqPoint (Hz):  0 - 600 - 1600 - 2000 - 3000 - 4000 - 6000 - 10000  - 13000 - 17000 - EQ_MAX_FREQ
		//
		//
		//		If you use your own eq bands ( CreateEqBands ) you need to send gain for each your band.
		//		If you create 20 eq bands, then you need to send pointer to 20 values as pnBandValue parameter
		//
		//
		// Example:
		//
		// int eq_values[10];
		// eq_values[0] = -12;
		// eq_values[1] = -12;  // cut bas 12 db
		// eq_values[2] = 0;
		// eq_values[3] = 0;  // unchanged
		// eq_values[4] = 0;
		// eq_values[5] = 0;
		// eq_values[6] = 0;
		// eq_values[7] = 12; // boost high tones 12 db
		// eq_values[8] = 12;
		// eq_values[9] = 0;
		// SetEQParam(1, eq_values, 10);


// =============================================================================================================


	// set equalizer data

W_DECLSPEC int __stdcall Mp3_SetEQParamEx(
			char *objptr,		// Pointer to class instance.
			int fExternal,		// flag specifying internal or external equalizer
			int nPreAmpGain,	// preamp gain
			int *pnBandGain,	// array of gain for each band
			int nNumberOfBands	// number of frequency bands
		);


		//	PARAMETERS:
		//
		//		fExternal		
		//			Specifies external or internal equalizer.
		//			Value 1 specifies external (advanced) equalizer.
		//			Value 0 specifies internal equalizer 
		//
		//		nPreAmpGain		
		//			Preamp gain in millidecibels ( thousandth of decibel ). Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands.
		//
		//		pnBandGain		
		//			Array of gain for each band millidecibels ( thousandth of decibel ). Positive values boost volume,
		//			negative value drops volume.
		//
		//		nNumberOfBands	 
		//			Number of frequency bands. Class has by default 10 eq bands, but you can create
		//			new bands using CreateEqBands function ( only for external equalizer ).
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//
		//	Default bands on new created class: 
		//
		//			SUBBAND FREQUENCY for external Shibatch Super Equalizer
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		//
		//
		//			SUBBAND FREQUENCY for libmad internal  equalizer
		//
		//			index:		       0     1      2      3      4      5      6        7       8       9 
		//			FreqPoint (Hz):  0 - 600 - 1600 - 2000 - 3000 - 4000 - 6000 - 10000  - 13000 - 17000 - EQ_MAX_FREQ
		//
		//
		//		If you use your own eq bands ( CreateEqBands ) you need to send gain for each your band.
		//		If you create 20 eq bands, then you need to send pointer to 20 values as pnBandValue parameter
		//
		//
		// Example:
		//
		// int eq_values[10];
		// eq_values[0] = -12000;
		// eq_values[1] = -12000;  // cut bas 12 db
		// eq_values[2] = 0;
		// eq_values[3] = 0;  // unchanged
		// eq_values[4] = 0;
		// eq_values[5] = 0;
		// eq_values[6] = 0;
		// eq_values[7] = 12000; // boost high tones 12 db
		// eq_values[8] = 12500;
		// eq_values[9] = 0;
		// SetEQParam(1, 0, eq_values, 10);


// =============================================================================================================

		// get equalizer data

W_DECLSPEC int __stdcall Mp3_GetEQParam(
			char *objptr,		// Pointer to class instance.
			int fExternal,		// flag specifying internal or external equalizer
			int *pnPreAmpGain,	// pointer to integer receiving preamp gain
			int *pnBandGain		// pointer to variable receiving gain for each band
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//
		//		fExternal		
		//			Specifies external or internal equalizer.
		//			Value 1 specifies external (advanced) equalizer.
		//			Value 0 specifies internal equalizer 
		//
		//		pnPreAmpGain		
		//			Pointer to integer receiving preamp gain in decibels.
		//			If this value is NULL function returns number of equalizer bands.
		//
		//		pnBandGain		
		//			Pointer to variable receiving gain for each band in decibels.
		//			If this value is NULL function returns number of equalizer bands.
		//
		//
		//	RETURN VALUES:
		//		number of bands
		//
		//	REMARKS:
		//
		//	Default bands on new created class: 
		//
		//			SUBBAND FREQUENCY for external Shibatch Super Equalizer
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		//
		//
		//			SUBBAND FREQUENCY for libmad internal  equalizer
		//
		//			index:		       0     1      2      3      4      5      6        7       8       9 
		//			FreqPoint (Hz):  0 - 600 - 1600 - 2000 - 3000 - 4000 - 6000 - 10000  - 13000 - 17000 - EQ_MAX_FREQ
		//
		//

// =============================================================================================================


	// get equalizer data

W_DECLSPEC int __stdcall Mp3_GetEQParamEx(
			char *objptr,		// Pointer to class instance.
			int fExternal,		// flag specifying internal or external equalizer
			int *pnPreAmpGain,	// pointer to integer receiving preamp gain ( millidecibels)
			int *pnBandGain		// pointer to variable receiving gain for each band ( millidecibels)
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fExternal		
		//			Specifies external or internal equalizer.
		//			Value 1 specifies external (advanced) equalizer.
		//			Value 0 specifies internal equalizer 
		//
		//		pnPreAmpGain		
		//			Pointer to integer receiving preamp gain in millidecibels
		//			If this value is NULL function returns number of equalizer bands.
		//
		//		pnBandGain		
		//			Pointer to variable receiving gain for each band in millidecibels.
		//			If this value is NULL function returns number of equalizer bands.
		//
		//
		//	RETURN VALUES:
		//		number of bands
		//
		//	REMARKS:
		//
		//	Default bands on new created class: 
		//
		//			SUBBAND FREQUENCY for external Shibatch Super Equalizer
		//
		//			band:			  0     1     2     3     4      5      6      7       8       9 
		//			FreqPoint (Hz): 0 - 115 - 240 - 455 - 800 - 2000 - 4500 - 9000 - 13000 - 15000 - EQ_MAX_FREQ
		//
		//
		//
		//			SUBBAND FREQUENCY for libmad internal  equalizer
		//
		//			index:		       0     1      2      3      4      5      6        7       8       9 
		//			FreqPoint (Hz):  0 - 600 - 1600 - 2000 - 3000 - 4000 - 6000 - 10000  - 13000 - 17000 - EQ_MAX_FREQ
		//
		//

// =============================================================================================================

		// load ID3 data
	
W_DECLSPEC int __stdcall Mp3_LoadID3(
			char *objptr,		// Pointer to class instance.
			int nId3Version,	// ID3 version
			ID3_INFO *pId3Info	// pointer to ID3_INFO structure
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		nId3Version
		//			Specifies ID3 version. Value ID3_VERSION1 loads ID3v1 data.
		//			Value ID3_VERSION2 loads ID3v2 data.
		//
		//		pId3Info
		//			Pointer tu structure receiving ID3 data.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// typedef struct {
		//	char *Title;
		//	char *Artist;
		//	char *Album;
		//	char *Year;
		//	char *Comment;
		//	char *TrackNum; 
		// } ID3_INFO;


// =============================================================================================================	



		// sound processing echo and reverb
		// enable echo and set echo parematers

		
W_DECLSPEC int __stdcall Mp3_SetSfxParam(
			char *objptr,		// Pointer to class instance.
			int fEnable,		// flag for enabling or disabling sfx processing
			int nMode,			// echo mode
			int nDelayMs,		// delay
			int nInputGain,		// gain of input sound
			int nEchoGain,		// gain of added echo sound
			int nOutputGain		// gain of output sound
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//
		//		fEnable		
		//			Specifies whether to enable or disable the sfx engine.
		//			If this parameter is 1 sfx engine is enabled.
		//			If this parameter is 0 sfx engine is disables.
		//
		//		nMode		
		//			Specifies echo mode. Range is from 0 to 9.
		//
		//		nDelayMs		
		//			Echo delay in millisecond ( 50 milliseconds step ), max 1000 ms
		//
		//		nInputGain
		//			Gain of input sound in decibels.
		//			Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands. 
		//
		//		nEchoGain
		//			Gain of added echo sound in decibels
		//			Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands
		//
		//		nOutputGain
		//			Gain of output sound in decibels
		//			Value 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string


// =============================================================================================================

		// get sfx param

		
W_DECLSPEC int __stdcall Mp3_GetSfxParam(
			char *objptr,		// Pointer to class instance.
			int *pnMode,		// pointer to variable receiving current mode
			int *pnDelayMs,		// pointer to variable receiving echo delay in millisecond
			int *pnInputGain,	// pointer to variable receiving gain of input sound in decibels
			int *pnEchoGain,	// pointer to variable receiving  gain of added echo sound in decibels
			int *pnOutputGain	// pointer to variable receiving gain of output sound in decibels
);


		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//
		//		pnMode		
		//			Pointer to variable receiving current mode.
		//			Mode range is from 0 to 9.
		//
		//		nDelayMs		
		//			Pointer to variable receiving echo delay in millisecond.
		//
		//		pnInputGain
		//			Pointer to variable receiving gain of input sound in decibels.
		//			Gain 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands. 
		//
		//		pnEchoGain
		//			Pointer to variable receiving  gain of added echo sound in decibels.
		//			Gain 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands
		//
		//		pnOutputGain
		//			Pointer to variable receiving gain of output sound in decibels.
		//			Gain 0 specifies no change. Positive values boost volume,
		//			negative value drops volume. This value has effect on all bands
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string



// =============================================================================================================

		// set sfx mode data

W_DECLSPEC int __stdcall Mp3_SetSfxModeData(
			char *objptr,			// Pointer to class instance.
			int nMode,				// specifies sfx mode
			int *pnModeDataLeft,	// pointer to sfx mode data for left channel
			int *pnModeDataRight,	// pointer to sfx mode data for right channel
			int nSize				// must be ECHO_MAX_DELAY_NUMBER ( 20 )
);


		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		nMode		
		//			Specifies echo mode. Range is from 0 to 9.
		//
		//		pnModeDataLeft		
		//			Pointer to array of 20 integers specifying mode data for left channel.
		//			See Remarks section.
		//
		//		pnModeDataRight
		//			Pointer to array of 20 integers specifying mode data for right channel.
		//			See Remarks section. 
		//
		//		nSize
		//			This value must be 20.
		//
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//
		// REMARKS:
		//	
		//		New created instance of class has all mode set to default values.		
		//
		//		Sfx engine has 	20 buffers, each buffer has about 50 milliseconds audio data.
		//		20 bufers * 50 ms = 1 second of audio data.
		//		First buffer (pnModeDataLeft[0])  represents current playing buffer 
		//		Second buffer (pnModeDataLeft[1])  is 50 ms old ( 50 ms delay) , third is 100 ms old ( 100 ms delay) ....
		//		Last buffer (pnModeDataLeft[19]) is 1000 ms old ( 1000 ms delay)
		// 
		//		Data in these buffers are half volume of original data. And these buffers will mix with half volume
		//		of current playing data.
		//
		//		In pnModeDataLeft and pnModeDataRight you need to specify these mixing ratios for each buffer.
		//
		//	Example 1: { 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
		//
		//	This settings mix half volume original data and 100 %  volume of second buffer (50 ms delay) and you get
		//	simple full volume echo of 50 ms delay
		//
		//  Example 2: { 0, 50, 0, 0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
		//
		//	This settings mix half volume original data + 50 %  volume of second buffer (50 ms delay) and 
		//	half volume original + 50 %  volume of seventh buffer (300 ms delay) and
		//  you get full volume output data wit double echo ( first echo at 50 ms delay and second at 300 ms delay )
		//
		//
		//	Example 3: { 0, 10, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 40, 10, 5, 3, 0, 0, 0 }
		//
		//		Advanced multiple echo.
		//
		//
		//	You can set echo mode for left and right channel separately. You can create different echo effect
		//	on left and right channel at the same time.


// =============================================================================================================	


		// get sfx mode data
		// 
		//
		// INPUT:
		//			int nMode				- identify sfx mode ( 0 - 9 ) 
		//			int *pnModeDataLeft		- pointer to variable receiving mode data for left channel
		//			int *pnModeDataRight	- pointer to variable receiving mode data for right channel
		// RETURN:
		//		number of elements in pnModeDataLeft array ( ECHO_MAX_DELAY_NUMBER )
		//
		// REMARKS:
		//		If pnModeDataLeft is 0, function return number of elements needed for pnModeDataLeft array
		//		Read Remarks section for SetSfxModeData function

		
W_DECLSPEC int __stdcall Mp3_GetSfxModeData(
			char *objptr,			// Pointer to class instance.
			int nMode,				// identify sfx mode
			int *pnModeDataLeft,	// pointer to variable receiving mode data for left channel
			int *pnModeDataRight	// pointer to variable receiving mode data for right channel
);


		
		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		nMode		
		//			Specifies echo mode. Range is from 0 to 9.
		//
		//		pnModeDataLeft
		//			Pointer to variable receiving mode data for left channel.
		//			If this value is 0 function returns number of elements
		//			needed for pnModeDataLeft array 
		//
		//		pnModeDataRight
		//			Pointer to variable receiving mode data for right channel
		//			If this value is 0 function returns number of elements
		//			needed for pnModeDataLeft array 
		//
		// RETURN:
		//		number of elements in pnModeDataLeft array ( ECHO_MAX_DELAY_NUMBER )
		//
		// REMARKS:
		//		If pnModeDataLeft is 0, function return number of elements needed for pnModeDataLeft array
		//		Read Remarks section for SetSfxModeData function


// =============================================================================================================

		// enable reverse mode ( in this mode song plays backward )

W_DECLSPEC int __stdcall Mp3_ReverseMode(
			char *objptr,	// Pointer to class instance.
			int fEnable	//  flag for enabling or disabling reverse mode
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		fEnable
		//			Specifies whether to enable or disable reverse mode.
		//			Value 1 enables reverse mode, 0 disables reverse mode.
		//
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		// REMARK:
		//
		// This function scans whole stream to enumerate all frames. This takes some time.
		// But this scan is preformad only once on stream. If you intend to use reverse mode
		// you can call this function when file is open with parameter 0. This will enumerate
		// all frames and prepare stream for reverse mode. 
		// Subsequent calls to this function will not start enumeration of frames. 
		//
		// Enabling this mode, song will play backward. You need to seek from the beginning of
		// song and then play backward to the song start. You can't play backward from 0 position.
		// You need to seek song first and then play backward. 
		// You can change reverse mode while song is playing to change playing direction.
		//
		// NOTE:
		//	You CAN'T use this function on managed stream.




// =============================================================================================================-


        // Set output volume of wave out device driver

W_DECLSPEC int __stdcall Mp3_SetMasterVolume(
			char *objptr,	// Pointer to class instance.
			unsigned int nLeftVolume,	// left channel volume
			unsigned int nRightVolume	// right channel volume
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		nLeftVolume
		//			Specifies volume for left channel. Volume range is from 0 to 100
		//
		//		nRightVolume
		//			Specifies volume for right channel. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function changes wave out volume affecting device driver and all sound on computer 


// =============================================================================================================-


        // Set internal volume ( modify PCM samples to control volume )

W_DECLSPEC int __stdcall Mp3_SetPlayerVolume(
			char *objptr,	// Pointer to class instance.
			unsigned int nLeftVolume,	// left channel volume
			unsigned int nRightVolume	// right channel volume
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		nLeftVolume
		//			Specifies volume for left channel. Volume range is from 0 to 100
		//
		//		nRightVolume
		//			Specifies volume for right channel. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//
		//	REMARKS:
		//		This function changes internal volume without affecting wave out device driver.


// ============================================================================================================

		// get output volume of wave out device driver

W_DECLSPEC int __stdcall Mp3_GetMasterVolume(
			char *objptr,	// Pointer to class instance.
			unsigned int *pnLeftVolume,	// pointer to variable receiving left volume
			unsigned int *pnRightVolume	// pointer to variable receiving right volume
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pnLeftVolume
		//			Pointer to variable receiving left volume. Volume range is from 0 to 100
		//
		//		pnRightVolume
		//			Pointer to variable receiving right volume. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//


// =============================================================================================================


		// get internal volume

W_DECLSPEC int __stdcall Mp3_GetPlayerVolume(
			char *objptr,	// Pointer to class instance.
			unsigned int *pnLeftVolume,	// pointer to variable receiving left volume
			unsigned int *pnRightVolume	// pointer to variable receiving right volume
);

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//		pnLeftVolume
		//			Pointer to variable receiving left volume. Volume range is from 0 to 100
		//
		//		pnRightVolume
		//			Pointer to variable receiving right volume. Volume range is from 0 to 100
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string
		//


// =============================================================================================================

		// calculate FFT values from currently playing PCM data 
    	
W_DECLSPEC int __stdcall Mp3_GetFFTValues(
								char *objptr,	// Pointer to class instance.
								int nFFTPoints,			// specify number of fft points. Set this value to:  32, 64, 128, 256, 512, 1024, 2048, 8192, 16384
								int nFFTWindow,		// specify FFT window (	FFT_RECTANGULAR, FFT_HAMMING, FFT_HANN, FFT_COSINE, ... )  	   
								int fFlag,				// flags specifing data we need from this function
								int *pnHarmonicNumber, // pointer to variable receiving number of harmonics
								int *pnHarmonicFreq,	// address of buffer for harmonic frequencies ( can be NULL )
								int *pnLeftAmplitude,	// address of buffer for amplitude of left channel harmonics ( can be NULL )
								int *pnRightAmplitude,	// address of buffer for amplitude of right channel harmonics ( can be NULL )
								int *pnLeftPhase,		// address of buffer for phases of left channel harmonics ( can be NULL )
								int *pnRightPhase		// address of buffer for phases of right channel harmonics ( can be NULL )
) ;

		//	PARAMETERS:
		//		objptr
		//			Pointer to class instance.
		//
		//			
		//		nFFTPoints
		//				Set this value to specify FFT size ( number of samples to proccess with FFT algorithm.
		//				This parameter can be one of following values: 32, 64, 128, 256, 512, 1024, 2048, 8192, 16384
		//				Harmonic frequencies and band size depends on this value. Use Google to get more info about FFT, harmonics, ...
		//
		//		nFFTWindow
		//				Set this value to specify FFT window. Use one of the following values:
		//
		//				FFT_RECTANGULAR
		//				FFT_HAMMING
		//				FFT_HANN 
		//				FFT_COSINE
		//				FFT_LANCZOS 
		//				FFT_BARTLETT
		//				FFT_TRIANGULAR
		//				FFT_GAUSS
		//				FFT_BARTLETT_HANN
		//				FFT_BLACKMAN 
		//				FFT_NUTTALL
		//				FFT_BLACKMAN_HARRIS
		//				FFT_BLACKMAN_NUTTALL
		//				FFT_FLAT_TOP
		//
		//				Use Google to get more info about FFT windows.
		//
		//		fFlag
		//			Flag specifying data we need to retreive. Combine these values:
		//				FFT_HARMONIC_NUM
		//				FFT_HARMONIC_FREQ
		//				FFT_LEFT_AMPLITUDE
		//				FFT_RIGHT_AMPLITUDE
		//				FFT_LEFT_PHASE
		//				FFT_RIGHT_PHASE
		//
		//		pnHarmonicNumber
		//				Pointer to variable receiving number of harmonics returned from FFT analysis.
		//				Returned value will be  = (nFFTPoints/2 + 1).
		//				If FFT_HARMONIC_NUM flag isn't set, this parameter isn't used.
		//
		
		//
		//		pnHarmonicFreq
		//				Set this parameter to adress of int array to receive harmonics frequencies in Hz.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If FFT_HARMONIC_FREQ flag isn't set, this parameter isn't used.
		//
		//				pnHarmonicFreq[0] is 0 Hz, pnHarmonicFreq[0] is sampling_rate / nFFTPoints ( first harmonic ), pnHarmonicFreq[1] is sampling_rate / nFFTPoints * 2 ( second harmonic ), ...
		//			
		//		pnLeftAmplitude
		//				Set this value to address of int array to receive amplitude for each harmonic of left channel.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If FFT_LEFT_AMPLITUDE flag isn't set, this parameter isn't used.
		//
		//				Amplitude range is from 0 to about 120 dB.
		//
		//		pnRightAmplitude
		//				Set this value to address of int array to receive amplitude for each harmonic of right channel.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If FFT_RIGHT_AMPLITUDE flag isn't set, this parameter isn't used.
		//
		//				Amplitude range is from 0 to about 120 dB.
		//
		//		pnLeftPhase
		//				Set this value to address of int array to receive phase for each harmonic of left channel.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If FFT_LEFT_PHASE flag isn't set, this parameter isn't used.
		//
		//				Phase range is from -90 to 90 degrees.
		//
		//		pnRighttPhase
		//				Set this value to address of int array to receive phase for each harmonic of right channel.
		//				User needs to allocate memory for this array { malloc(nHarmonicNumber * sizeof(int)); }
		//				If FFT_RIGHT_PHASE flag isn't set, this parameter isn't used.
		//
		//				Phase range is from -90 to 90 degrees.
		//
		//		You must specify valid nFFTPoints and nFFTWindow parameter. And you must specify valid pointers for
		//		pnHarmonicFreq, pnLeftAmplitude, pnRightAmplitude, pnLeftPhase and  pnRighttPhase.
		//		If you call this function with wrong, or uninitialized pointers,
		//		you will have memory error or application crash.
		//
		//	RETURN VALUES:
		//		1 - all OK
		//		0 - error, call GetError() to get error string

// =============================================================================================================


// =============================================================================================================
//
//END OF C/C++ WRAPPER FOR WMP3 CLASS
//
// =============================================================================================================


#ifdef __cplusplus
}
#endif

#endif

