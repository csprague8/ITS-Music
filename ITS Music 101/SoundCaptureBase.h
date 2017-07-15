//using System;
//using System.Threading;
//using Microsoft.DirectX.DirectSound;
//using Microsoft.Win32.SafeHandles;

#include <thread>
#include <dsound.h>

/// <summary>
/// Base class to capture audio samples.
/// </summary>
class SoundCaptureBase
{
   const int BufferSeconds = 3;
   const int NotifyPointsInSecond = 2;

   // change in next two will require also code change
   const int BitsPerSample = 16;
   const int ChannelCount = 1;

   int sampleRate = 44100;
   bool isCapturing = false;
   bool disposed = false;

public:
   SoundCaptureBase();
   ~SoundCaptureBase();
   void Start();
   void Stop();
   bool IsCapturing();
   int SampleRate();
   void SampleRate(int value);
   
   SoundCaptureBase();
   SoundCaptureBase(SoundCaptureDevice device);

private:
   void EnsureIdle();
   void ThreadLoop();
   void Dispose(bool disposing);
   
protected: 
   virtual void ProcessData(short *data, int length);

public:
   int bufferLength;
   IDirectSoundCapture* capture;
   IDirectSoundCaptureBuffer* buffer;
   IDirectSoundNotify *notify;

   //AutoResetEvent positionEvent;
   //SafeWaitHandle positionEventHandle;
   //ManualResetEvent terminated;

   std::thread *thread;
   SoundCaptureDevice device;
};

