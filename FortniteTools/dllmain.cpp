#include "build.h"

#include <windows.h>

#include "util.h"
#include "core.h"

/*
 * FortniteTools by Cyuubi
 * 
 * NOTES:
 * - Choose which UE version to target in "build.h", not all options work with every version.
 * - UE32_4_12/Alpha should be built with Win32, everything else should be built with x64.
 * - UE32_4_12/Alpha supports PROCESSEVENT_HOOK, but it's quite broken and probably needs to be fixed.
 * - PROCESSEVENT_HOOK should be used for debugging, it is not intended for public usage.
 */

DWORD WINAPI Main(LPVOID lpParam)
{
    Util::InitConsole();

    printf("\nFortniteTools (designed) for UE %s by Cyuubi.\n", UE_VERSION);

    Util::InitCore();

#ifdef PROCESSEVENT_HOOK
    printf("Initializing ProcessEvent... ");

    if (Core::InitProcessEvent())
    {
        printf("Success!\n");
    }
    else
    {
        printf("Failed.\n");
    }
#endif // PROCESSEVENT_HOOK

    printf("Initializing Console... ");

    if (Core::InitConsole())
    {
        printf("Success, you can press \"`\" to bring up Console!\n\n");
    }
    else
    {
        printf("Failed, Console is already initialized.\n\n");
    }

    return NULL;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason,
    LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 0, Main, hModule, 0, 0);
    }

    return TRUE;
}

