# LNKgenerator-BOF
BOF for creating LNKs

## Usage
```
Usage: LNKgenerator <targetFile> <targetArgs> <lnkFileLocation> <description> <curDir> <iconFile> [iShowmode] [iIconindex]

Example: LNKgenerator "C:\Program Files\Google\Chrome\Application\chrome.exe" "--remote-debugging-port=9222 --remote-allow-origins=* --user-data-dir=C:\Users\Public\Documents" "C:\Users\defaultuser\Desktop\test.lnk" "Internet Access" "C:\Program Files\Google\Chrome\Application" "C:\Program Files\Google\Chrome\Application\chrome.exe" 1 0 
```

LNK Show Modes: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow

## References
https://www.codeproject.com/Articles/11467/How-to-create-short-cuts-link-files-#xx3649586xx