#include "stdafx.h"
#include <string>
#include <list>
#include "SoundCaptureDevice.h"
#include <rpc.h>

//using Microsoft.DirectX.DirectSound;
#include <dshow.h>

#pragma comment(lib, "strmiids")

HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum)
{
   // Create the System Device Enumerator.
   ICreateDevEnum *pDevEnum;
   HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
      CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

   if (SUCCEEDED(hr))
   {
      // Create an enumerator for the category.
      hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
      if (hr == S_FALSE)
      {
         hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
      }
      pDevEnum->Release();
   }
   return hr;
}

bool SoundCaptureDevice::IsDefault()
{
   return m_id == GUID_NULL;
}

std::string SoundCaptureDevice::Name()
{
   return m_name;
}

GUID SoundCaptureDevice::Id()
{
   return m_id;
}

SoundCaptureDevice::SoundCaptureDevice(GUID id, std::string name)
{
   m_id = id;
   m_name = name;
}

std::list<SoundCaptureDevice> SoundCaptureDevice::GetDevices()
{
   std::list<SoundCaptureDevice> devices;

   HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
   if (!SUCCEEDED(hr))
      return devices;

   IEnumMoniker *pEnum;
   hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
   if (!SUCCEEDED(hr))
      return devices;


   IMoniker *pMoniker = NULL;

   while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
   {
      IPropertyBag *pPropBag;
      HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
      if (FAILED(hr))
      {
         pMoniker->Release();
         continue;
      }

      VARIANT var;
      VariantInit(&var);

      CString listMsg;
      CString tmp;

      // Get description or friendly name.
      hr = pPropBag->Read(L"Description", &var, 0);
      if (FAILED(hr))
      {
         hr = pPropBag->Read(L"FriendlyName", &var, 0);
      }
      if (SUCCEEDED(hr))
      {
         tmp.Format(L"%S\n", (LPCTSTR)var.bstrVal);
         listMsg += tmp;
         VariantClear(&var);
      }

      hr = pPropBag->Write(L"FriendlyName", &var);

      // WaveInID applies only to audio capture devices.
      hr = pPropBag->Read(L"WaveInID", &var, 0);
      if (SUCCEEDED(hr))
      {
         tmp.Format(L"WaveIn ID: %d\n", var.lVal);
         listMsg += tmp;
         VariantClear(&var);
      }

      hr = pPropBag->Read(L"DevicePath", &var, 0);
      if (SUCCEEDED(hr))
      {
         // The device path is not intended for display.
         tmp.Format(L"Device path: %S\n", (LPCTSTR)var.bstrVal);
         listMsg += tmp;
         VariantClear(&var);
      }

      MessageBox(NULL, L" ", listMsg, 0);

      pPropBag->Release();
      pMoniker->Release();

      //SoundCaptureDevice device =
      //   SoundCaptureDevice(
      //   captureDevice.DriverGuid,
      //   captureDevice.Description);
      //
      //devices.push_back(device);
   }






   //CaptureDevicesCollection captureDevices = new CaptureDevicesCollection();
   //
   //for each(DeviceInformation captureDevice in captureDevices)
   //{
   //   SoundCaptureDevice device = 
   //      SoundCaptureDevice(
   //         captureDevice.DriverGuid, 
   //         captureDevice.Description);
   //
   //   devices.push_back(device);
   //}

   return devices;
}

SoundCaptureDevice SoundCaptureDevice::GetDefaultDevice()
{
   //CaptureDevicesCollection captureDevices = new CaptureDevicesCollection();
   SoundCaptureDevice *device = NULL;

   //for each(DeviceInformation captureDevice in captureDevices)
   //{
   //   if (captureDevice.DriverGuid == GUID_NULL)
   //   {
   //      device = new SoundCaptureDevice(
   //         captureDevice.DriverGuid, captureDevice.Description);
   //      break;
   //   }
   //}
   //
   //if (device == NULL)
   //{
   //   MessageBox(NULL, L"Warning", L"Default capture device is not found", 0);
   //}

   return *device;
}

