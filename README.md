# NativeMode-Sample
This is a **native mode** sample application that is called during the BootExecute phase of the Session Manager during the Windows boot process.

This program runs on the following operating systems:
- Windows Vista
- Windows 7
- Windows 8
- Windows 8.1
- Windows 10
- Windows 11
  
> [!CAUTION]
> This tool directly intervenes in the Windows **boot process (BootExecute)**.<br>ncorrect settings may cause **Windows to fail to start**.<br> Installation, modification, and execution are **at your own risk**.<br> The developer **assumes no responsibility** for any damage or malfunction.

> [!WARNING]
> On Windows XP, the following message appears and the program does not run.<img width="521" height="126" alt="image" src="https://github.com/user-attachments/assets/ba029a34-d1f7-423a-aa23-cfaa153bccc3" />


# Build command
You need a **Developer Command Prompt for VS**.
```cmd
if not exist bin mkdir bin
cl /nologo /Zl /GS- /W0 src\native_hello.c ^
/Fo:bin\native_hello.obj /Fe:bin\native_hello.exe ^
/link /SUBSYSTEM:NATIVE /NODEFAULTLIB /ENTRY:NtProcessStartup ntdll.lib
```

# How to Run
1. Copy the compiled binary to `C:\Windows\System32`
1. Open `BootExecute` in `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager`.
1. Add the following line:
```
native_hello.exe
```
4. Reboot

# Removal Process
If the program fails to boot for any reason after modifying the registry, remove it by running the following command from Windows RE:
```cmd
reg load HKLM\BROKEN C:\Windows\System32\Config\SYSTEM
reg add "HKLM\BROKEN\ControlSet001\Control\Session Manager" /v BootExecute ^
/t REG_MULTI_SZ /d "autocheck autochk *" /f
reg unload HKLM\BROKEN
```

# Notes
* The program must be placed in System32 because `BootExecute` does not allow absolute paths.
* This runs before Win32, so only the NT Native API is available.
* printf, MessageBox, Win32 API, and CRT functions cannot be used.
* Make sure `autocheck autochk *` is always kept in `BootExecute` to avoid boot issues.

# Contributions
All pull requests will be ignored, but you are welcome to fork and change the message or display time!

# Screenshots
Below is a screenshot of it working properly (on Windows 8.1).
<img width="1024" height="768" alt="image" src="https://github.com/user-attachments/assets/270546b6-a2bd-4773-ae8f-024f56355e83" />

