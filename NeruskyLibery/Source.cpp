#include "pch.h"
#include <stdio.h>
#include <wtypes.h> 
#include <comdef.h>
#include <windows.h>
#include "Preser.h"
#include <iostream> 
HANDLE _hComPort;
int atteintion = 0;
extern "C"
{
    __declspec(dllexport) BSTR   DisplayHelloFromDLL()
    {
       return SysAllocString(L"I am a happy BSTR");

    }
    __declspec(dllexport) BSTR   SensorConnect()
    {
         _hComPort = CreateFile( // open the serial port
            L"\\\\.\\COM5",
            GENERIC_READ | GENERIC_WRITE,
            0,    // Must be opened with exclusive-access.
            NULL, // No security attributes.
            OPEN_EXISTING, // Must use OPEN_EXISTING.
            0,    // Not overlapped I/O.
            NULL  // hTemplate must be NULL for comm devices.
        );
        
         if (_hComPort == INVALID_HANDLE_VALUE) {

             return SysAllocString(L"Connection Faild");
         }
         return SysAllocString(L"Connection Successed");

    }
 
    __declspec(dllexport) int  getAtteintion() {
        Preser* p;
        while (1) {
            p = new Preser(_hComPort);
            // First 2 Package - Sync BYTE 

            if (p->vlidation_package() && p->vlidation_package()) {
                break;
            }
            free(p);
            Sleep(200);
        }
        // THIRD Byte - lenght packge  
        p->read_Lenght_package();
        int len = p->get_len();


        // checkSum -TODO
        p->read_checkSum();

        // Reading the rest of the package - DATA section 
        for (size_t i = 0; i < len; i++) {
            p->read_data_byte();
        }


        if (len == 32) {

            if (p->check_attention_byte()) {
                printf("attention is : ");

                 atteintion = p->get_attention();

            }
        }


        free(p);
        return atteintion;
    }
    __declspec(dllexport) BSTR   SensorDisconnect() {
        CloseHandle(_hComPort);
        return SysAllocString(L"The connection is end");
    }

}