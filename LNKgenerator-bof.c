#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include "LNKgenerator.h"
#include "beacon.h"

#define CLSCTX_INPROC_SERVER 0x1


// BOF Defs
WINBASEAPI HRESULT WINAPI OLE32$CoInitialize(LPVOID pvReserved);
WINBASEAPI HRESULT WINAPI OLE32$CoCreateInstance(REFCLSID  rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv);
WINBASEAPI void WINAPI OLE32$CoUninitialize();
WINBASEAPI size_t __cdecl MSVCRT$wcslen(const wchar_t* str);
// ref - https://www.codeproject.com/Articles/11467/How-to-create-short-cuts-link-files-#xx3649586xx
static HRESULT create_lnk(LPWSTR pszTargetfile, LPWSTR pszTargetargs, LPWSTR pszLinkfile, LPWSTR pszDescription, int iShowmode, LPWSTR pszCurdir, LPWSTR pszIconfile, int iIconindex) {

    HRESULT hRes;  /* Returned COM result code */
    IShellLinkW*   pShellLink = NULL;     /* IShellLink object pointer */
    IPersistFile*  pPersistFile = NULL;   /* IPersistFile object pointer */

    // COM CLSID and IID definitions
    static GUID IID_IShellLinkW = { 0x000214F9L, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46} };
    static GUID CLSID_ShellLink = { 0X00021401, 0 , 0, {0XC0,  0, 0, 0, 0, 0, 0, 0x46} };
    static GUID IID_IPersistFile = { 0x0000010b, 0 , 0, {0XC0,  0, 0, 0, 0, 0, 0, 0x46} };
    
	OLE32$CoInitialize(NULL);
	hRes = E_INVALIDARG;

    // Create COM
    hRes = OLE32$CoCreateInstance(
        &CLSID_ShellLink,     /* pre-defined CLSID of the IShellLink object */
        NULL,                 /* pointer to parent interface if part of aggregate */
        CLSCTX_INPROC_SERVER, /* caller and called code are in same process */
        &IID_IShellLinkW,      /* pre-defined interface of the IShellLink object */
        &pShellLink);

    BeaconPrintf(CALLBACK_OUTPUT,"[+] Creating LNK file...\n");
    if (SUCCEEDED(hRes))
	{
        // Set the target path
        hRes = pShellLink->lpVtbl->SetPath(pShellLink, pszTargetfile);
        if (FAILED(hRes)) {
            BeaconPrintf(CALLBACK_OUTPUT,"[-] Failed to set target path\n");
            goto cleanup;
        }
        
        // Set arguments if provided
        if (pszTargetargs && MSVCRT$wcslen(pszTargetargs) > 0) {
            hRes = pShellLink->lpVtbl->SetArguments(pShellLink, pszTargetargs);
            if (FAILED(hRes)) {
                BeaconPrintf(CALLBACK_OUTPUT,"[-] Failed to set arguments\n");
            }
        }
        
        // Set description if provided
        if (pszDescription && MSVCRT$wcslen(pszDescription) > 0) {
            hRes = pShellLink->lpVtbl->SetDescription(pShellLink, pszDescription);
            if (FAILED(hRes)) {
                BeaconPrintf(CALLBACK_OUTPUT,"[-] Failed to set description\n");
            }
        }
        
        // Set show mode if provided
        if (iShowmode > 0) {
            hRes = pShellLink->lpVtbl->SetShowCmd(pShellLink, iShowmode);
            if (FAILED(hRes)) {
                BeaconPrintf(CALLBACK_OUTPUT,"[-] Failed to set show mode\n");
            }
        }
        
        // Set working directory if provided
        if (pszCurdir && MSVCRT$wcslen(pszCurdir) > 0) {
            hRes = pShellLink->lpVtbl->SetWorkingDirectory(pShellLink, pszCurdir);
            if (FAILED(hRes)) {
                BeaconPrintf(CALLBACK_OUTPUT,"[-] Failed to set working directory\n");
            }
        }
        
        // Set icon if provided
        if (pszIconfile && MSVCRT$wcslen(pszIconfile) > 0 && iIconindex >= 0) {
            hRes = pShellLink->lpVtbl->SetIconLocation(pShellLink, pszIconfile, iIconindex);
            if (FAILED(hRes)) {
                BeaconPrintf(CALLBACK_OUTPUT,"[-] Failed to set icon location\n");
            }
        }
        
        // Get IPersistFile interface to save the link
        hRes = pShellLink->lpVtbl->QueryInterface(pShellLink, &IID_IPersistFile, (void**)&pPersistFile);
        if (SUCCEEDED(hRes)) {
            BeaconPrintf(CALLBACK_OUTPUT,"[+] Success QueryInterface\n");
            hRes = pPersistFile->lpVtbl->Save(pPersistFile, pszLinkfile, TRUE);
            if (SUCCEEDED(hRes)) {
                BeaconPrintf(CALLBACK_OUTPUT,"[+] LNK file created successfully!\n");
            } else {
                BeaconPrintf(CALLBACK_OUTPUT,"[-] Failed to save LNK file (HRESULT: 0x%08lx)\n", hRes);
            }
            pPersistFile->lpVtbl->Release(pPersistFile);
        } else {
            BeaconPrintf(CALLBACK_OUTPUT,"[-] Failed QueryInterface (HRESULT: 0x%08lx)\n", hRes);
        }
        
cleanup:
    pShellLink->lpVtbl->Release(pShellLink);
    } else {
        BeaconPrintf(CALLBACK_OUTPUT,"[-] Error CoCreateInstance (HRESULT: 0x%08lx)\n", hRes);
    }
    
    OLE32$CoUninitialize();
    return hRes;
    
}
    
void go(char * buf, int len){
    datap parser;

    wchar_t* targetFile = NULL;
    wchar_t* targetArgs = NULL;
    wchar_t* lnkFileLocation = NULL;
    wchar_t* description = NULL;
    wchar_t* curDir = NULL;
    wchar_t* iconFile = NULL;
    int iShowmode = SW_NORMAL; // Default show mode
    int iIconindex = 0; // Default icon index

    HRESULT hRes;
    
    BeaconDataParse(&parser, buf, len);

    targetFile = (wchar_t *) BeaconDataExtract(&parser, NULL);
    targetArgs = (wchar_t *) BeaconDataExtract(&parser, NULL);
    lnkFileLocation = (wchar_t *) BeaconDataExtract(&parser, NULL);
    description = (wchar_t *) BeaconDataExtract(&parser, NULL);
    curDir = (wchar_t *) BeaconDataExtract(&parser, NULL);
    iconFile = (wchar_t *) BeaconDataExtract(&parser, NULL);
    iShowmode = BeaconDataInt(&parser);
    iIconindex = BeaconDataInt(&parser);
    
    // BeaconPrintf(CALLBACK_OUTPUT, "targetFile: %ls", targetFile);

    hRes = create_lnk(
        (LPWSTR)targetFile, 
        (LPWSTR)targetArgs, 
        (LPWSTR)lnkFileLocation, 
        (LPWSTR)description, 
        iShowmode, 
        (LPWSTR)curDir, 
        (LPWSTR)iconFile, 
        iIconindex
    );
    if (FAILED(hRes)){
        BeaconPrintf(CALLBACK_ERROR, "[-] Failed to create shortcut\n");
    }
    
}