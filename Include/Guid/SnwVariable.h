/** @file
  Vendor variable for Sn0wSeven

  Copyright (c) 2026, ilikesn0w. All rights reserved.
  SPDX-License-Identifier: BSD-3-Clause
**/

#pragma once

//
// C8AD0BB7-E83A-47A8-8956-5858E8C98D33
// Our vendor variable GUID we will store everything there
//
#define SNW_VENDOR_VARIABLE_GUID \
  { 0xC8AD0BB7, 0xE83A, 0x47A8, \
     { 0x89, 0x56, 0x58, 0x58, 0xE8, 0xC9, 0x8D, 0x33 } }

//
// SNW_VENDOR_VARIABLE_GUID
//
extern EFI_GUID gSnwVendorVariableGuid;
