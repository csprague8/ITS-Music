#include "stdafx.h"
#include "SoundCaptureDevice.h"
#include "SoundCaptureBase.h"
#include <Mmreg.h>
//using Microsoft.DirectX.DirectSound;

#include <list>

bool SoundCaptureBase::IsCapturing()
{
   return isCapturing;
}

int SoundCaptureBase::SampleRate()
{
   return sampleRate;
}

void SoundCaptureBase::SampleRate(int value)
{
   if (sampleRate <= 0)
   {
      //throw new ArgumentOutOfRangeException();
   }

   EnsureIdle();

   sampleRate = value;
}

SoundCaptureBase::SoundCaptureBase()
{
   SoundCaptureDevice::GetDefaultDevice();
}

SoundCaptureBase::SoundCaptureBase(SoundCaptureDevice device)
{
   device = device;

   //positionEvent = new AutoResetEvent(false);
   //positionEventHandle = positionEvent.SafeWaitHandle;
   //terminated = new ManualResetEvent(true);
}

void SoundCaptureBase::EnsureIdle()
{
   if (IsCapturing)
   {
      MessageBox(NULL, L"Warning", L"Capture is in process", 0);
   }
}

/// <summary>
/// Starts capture process.
/// </summary>
void SoundCaptureBase::Start()
{
   EnsureIdle();

   isCapturing = true;

   WAVEFORMATEX format;
   format.wFormatTag = WAVE_FORMAT_PCM;
   format.nChannels = ChannelCount;
   format.nSamplesPerSec = SampleRate();
   format.wBitsPerSample = BitsPerSample;
   format.nBlockAlign = (short)((format.nChannels * format.wBitsPerSample + 7) / 8);
   format.nAvgBytesPerSec = format.nBlockAlign  * format.nSamplesPerSec;

   bufferLength = format.nAvgBytesPerSec * BufferSeconds;
   DSCBUFFERDESC desciption;
   desciption.lpwfxFormat = &format;
   desciption.dwBufferBytes = bufferLength;

   HRESULT hr;
   hr = DirectSoundCaptureCreate8(&device.Id, &capture, NULL);
   hr = capture->CreateCaptureBuffer(&desciption, &buffer, NULL);

   int waitHandleCount = BufferSeconds * NotifyPointsInSecond;
   LPDSBPOSITIONNOTIFY positions = new DSBPOSITIONNOTIFY[waitHandleCount];
   for (int i = 0; i < waitHandleCount; i++)
   {
      positions[i].dwOffset = (i + 1) * bufferLength / waitHandleCount - 1;
      positions[i].hEventNotify = positionEventHandle.DangerousGetHandle();
   }

   buffer->QueryInterface(IID_IDirectSoundNotify8, (LPVOID*)&notify);
   notify->SetNotificationPositions(waitHandleCount, positions);

   terminated.Reset();

   thread = new std::thread(&ThreadLoop);
}

void SoundCaptureBase::ThreadLoop()
{
   buffer->Start(true);

   try
   {
      int nextCapturePosition = 0;
      WaitHandle handles[] = new WaitHandle[] { terminated, positionEvent };
      
      while (WaitHandle.WaitAny(handles) > 0)
      {
         DWORD capturePosition, readPosition;
         buffer->GetCurrentPosition(&capturePosition, &readPosition);

         int lockSize = readPosition - nextCapturePosition;
         if (lockSize < 0) lockSize += bufferLength;
         if ((lockSize & 1) != 0) lockSize--;

         int itemsCount = lockSize >> 1;

         short data[] = (short[])buffer->Read(nextCapturePosition, typeof(short), LockFlag.None, itemsCount);
         ProcessData(data, itemsCount);
         nextCapturePosition = (nextCapturePosition + lockSize) % bufferLength;
      }
   }
   catch (...)
   {
   }

   buffer->Stop();
}

/// <summary>
/// Stops capture process.
/// </summary>
void SoundCaptureBase::Stop()
{
   if (isCapturing)
   {
      isCapturing = false;

      terminated.Set();
      thread->join();

      notify->Release();
      buffer->Release();
      capture->Release();
   }
}

SoundCaptureBase::~SoundCaptureBase()
{
   Dispose(false);
}


void SoundCaptureBase::Dispose(bool disposing)
{
   if (disposed) return;

   disposed = true;
   GC.SuppressFinalize(this);
   if (IsCapturing) Stop();
   positionEventHandle.Dispose();
   positionEvent.Close();
   terminated.Close();
}
   