/** @file
  Bootstrap for Sn0wSeven

  Copyright (c) 2026, ilikesn0w. All rights reserved.
  SPDX-License-Identifier: BSD-3-Clause
**/

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Protocol/DevicePath.h>
#include <Protocol/LoadedImage.h>

#define SNW_APP_PATH L"\\EFI\\SNW\\Sn0wSeven.efi"

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                 Status;
  EFI_LOADED_IMAGE_PROTOCOL  *LoadedImage;
  EFI_DEVICE_PATH_PROTOCOL   *SnwPath;
  EFI_HANDLE                 SnwImageHandle;

  DEBUG ((DEBUG_INFO, "BS: Sn0wSeven bootstrap started\n"));

  LoadedImage = NULL;

  //
  // Handle LoadedImage protocol
  //
  DEBUG ((DEBUG_INFO, "BS: Trying to handle LoadedImage protocol\n"));
  Status = gBS->HandleProtocol (ImageHandle, &gEfiLoadedImageProtocolGuid, (VOID **)&LoadedImage);
  if (EFI_ERROR (Status) || LoadedImage == NULL) {
    DEBUG ((DEBUG_ERROR, "BS: Failed to handle LoadedImage: %r\n", Status));
    return Status;
  }

  DEBUG ((DEBUG_INFO, "BS: Successfully handled LoadedImage protocol\n"));

  //
  // Create device path to Sn0wSeven
  //
  DEBUG ((DEBUG_INFO, "BS: Trying to create device path for Sn0wSeven\n"));
  SnwPath = FileDevicePath (LoadedImage->DeviceHandle, SNW_APP_PATH);
  if (SnwPath == NULL) {
    DEBUG ((DEBUG_ERROR, "BS: Failed to create device path\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  DEBUG ((DEBUG_INFO, "BS: Successfully created device path for Sn0wSeven\n"));

  SnwImageHandle = NULL;

  //
  // Load Sn0wSeven
  //
  DEBUG ((DEBUG_INFO, "BS: Trying load Sn0wSeven\n"));
  Status = gBS->LoadImage (
                  FALSE,
                  ImageHandle,
                  SnwPath,
                  NULL,
                  0,
                  &SnwImageHandle
                  );

  if (EFI_ERROR (Status) || SnwImageHandle == NULL) {
    DEBUG ((DEBUG_ERROR, "BS: Failed to load Sn0wSeven: %r\n", Status));
    gBS->FreePool (SnwPath);
    return Status;
  }

  DEBUG ((DEBUG_INFO, "BS: Sn0wSeven loaded successfully\n"));

  //
  // Start Sn0wSeven
  //
  DEBUG ((DEBUG_INFO, "BS: Trying to start Sn0wSeven\n"));
  Status = gBS->StartImage (SnwImageHandle, NULL, NULL);

  gBS->FreePool (SnwPath);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "BS: Failed to start Sn0wSeven: %r\n", Status));
    return Status;
  }

  return Status;
}
