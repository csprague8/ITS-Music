#include "stdafx.h"
#include "SoundCaptureDevice.h"
#include "SoundCaptureBase.h"
#include <Mmreg.h>
//using Microsoft.DirectX.DirectSound;



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

   positionEvent = new AutoResetEvent(false);
   positionEventHandle = positionEvent.SafeWaitHandle;
   terminated = new ManualResetEvent(true);
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

   WAVEFORMAT format;
   format.nChannels = ChannelCount;
   format.BitsPerSample = BitsPerSample;
   format.nSamplesPerSec = SampleRate;
   format.wFormatTag = WaveFormatTag.Pcm;
   format.nBlockAlign = (short)((format.nChannels * format.BitsPerSample + 7) / 8);
   format.nAvgBytesPerSec = format.nBlockAlign  * format.nSamplesPerSec;

   bufferLength = format.AverageBytesPerSecond * BufferSeconds;
   CaptureBufferDescription desciption = new CaptureBufferDescription();
   desciption.Format = format;
   desciption.BufferBytes = bufferLength;

   capture = new Capture(device.Id);
   buffer = new CaptureBuffer(desciption, capture);

   int waitHandleCount = BufferSeconds * NotifyPointsInSecond;
   BufferPositionNotify[] positions = new BufferPositionNotify[waitHandleCount];
   for (int i = 0; i < waitHandleCount; i++)
   {
      BufferPositionNotify position = new BufferPositionNotify();
      position.Offset = (i + 1) * bufferLength / positions.Length - 1;
      position.EventNotifyHandle = positionEventHandle.DangerousGetHandle();
      positions[i] = position;
   }

   notify = new Notify(buffer);
   notify.SetNotificationPositions(positions);

   terminated.Reset();
   thread = new Thread(new ThreadStart(ThreadLoop));
   thread.Name = "Sound capture";
   thread.Start();
}

void SoundCaptureBase::ThreadLoop()
{
   buffer.Start(true);

   try
   {
      int nextCapturePosition = 0;
      WaitHandle[] handles = new WaitHandle[] { terminated, positionEvent };
      while (WaitHandle.WaitAny(handles) > 0)
      {
         int capturePosition, readPosition;
         buffer.GetCurrentPosition(out capturePosition, out readPosition);

         int lockSize = readPosition - nextCapturePosition;
         if (lockSize < 0) lockSize += bufferLength;
         if ((lockSize & 1) != 0) lockSize--;

         int itemsCount = lockSize >> 1;

         short[] data = (short[])buffer.Read(nextCapturePosition, typeof(short), LockFlag.None, itemsCount);
         ProcessData(data);
         nextCapturePosition = (nextCapturePosition + lockSize) % bufferLength;
      }
   }


   buffer.Stop();   
}

/// <summary>
/// Processes the captured data.
/// </summary>
/// <param name="data">Captured data</param>
void SoundCaptureBase::ProcessData(short[] data);

/// <summary>
/// Stops capture process.
/// </summary>
void SoundCaptureBase::Stop()
{
   if (isCapturing)
   {
      isCapturing = false;

      terminated.Set();
      thread.Join();

      notify.Dispose();
      buffer.Dispose();
      capture.Dispose();
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
   