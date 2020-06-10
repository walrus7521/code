/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    driver and application

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_udrv,
    0xc63a9d1a,0xa2a1,0x42c1,0xb9,0xf1,0x17,0x0f,0xc8,0x63,0x0f,0xa8);
// {c63a9d1a-a2a1-42c1-b9f1-170fc8630fa8}
