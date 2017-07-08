//using System;
//using System.Collections.Generic;
//using System.Text;
//using Microsoft.DirectX.DirectSound;


/// <summary>
/// Capture device.
/// </summary>
class SoundCaptureDevice
{
   GUID m_id;
   std::string m_name;

public:
   bool IsDefault();
   std::string Name();
   GUID Id();
   SoundCaptureDevice(GUID id, std::string name);

   static std::list<SoundCaptureDevice> GetDevices();
   static SoundCaptureDevice GetDefaultDevice();
};
