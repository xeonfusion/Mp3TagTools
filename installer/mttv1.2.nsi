; mtt-v1.2.nsi
;
; This script is based on example2.nsi of NSISv1.98
;

SetCompress auto
SetDateSave on
SetDatablockOptimize on
CRCCheck on

; The name of the installer
Name "mtt-v1.2"
Caption "Mp3 Tag Tools v1.2 Setup"

; The file to write
OutFile "mtt-v1.2.exe"

; License page
 LicenseText "This installer will install the Mp3 Tag Tools v1.2 Please read the license below."
; use the default license :)
 LicenseData License.txt

; The default installation directory
InstallDir $PROGRAMFILES\Mp3TagToolsv12
; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM SOFTWARE\mtt12 "Install_Dir"

; The text to prompt the user to enter a directory
ComponentText "This will install the Mp3 Tag Tools v1.2 on your computer"
; The text to prompt the user to enter a directory
DirText "Choose a directory to install in to:"

ShowInstDetails "show"

; The stuff to install
Section "Program with Help File (required)"
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  ; Put file there
  File "F:\IDtagprogram\MTTv1.2.008 installer\mp3tagtools.exe"
  File "F:\IDtagprogram\MTTv1.2.008 installer\mtthelp.chm"	
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\mtt12 "Install_Dir" "$INSTDIR"
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\mtt12" "DisplayName" "Mp3 Tag Tools v1.2"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\mtt12" "UninstallString" '"$INSTDIR\uninstall.exe"'
WriteUninstaller "uninstall.exe"
SectionEnd

; optional section
Section "Start Menu Shortcuts"
SetShellVarContext all
  CreateDirectory "$SMPROGRAMS\Mp3 Tag Tools v1.2"
  CreateShortCut "$SMPROGRAMS\Mp3 Tag Tools v1.2\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
CreateShortCut "$SMPROGRAMS\Mp3 Tag Tools v1.2\Help.lnk" "$INSTDIR\mtthelp.chm" "" "$INSTDIR\mtthelp.chm" 0 
  CreateShortCut "$SMPROGRAMS\Mp3 Tag Tools v1.2\Mp3 Tag Tools v1.2.lnk" "$INSTDIR\mp3tagtools.exe" "" "$INSTDIR\mp3tagtools.exe" 0 
SectionEnd

Section "Desktop Shortcut"
SetShellVarContext all
CreateShortCut "$DESKTOP\Mp3 Tag Tools v1.2.008.lnk" "$INSTDIR\mp3tagtools.exe" "" "$INSTDIR\mp3tagtools.exe" 0 
SectionEnd

; uninstall stuff

UninstallText "This will uninstall Mp3 Tag Tools v1.2. Hit next to continue."

; special uninstall section.
Section "Uninstall"
SetShellVarContext all
  ; remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\mtt12"
  DeleteRegKey HKLM SOFTWARE\mtt12
  ; remove files
  Delete $INSTDIR\mp3tagtools.exe
  Delete $INSTDIR\mtthelp.chm
  Delete $INSTDIR\*.*	
  ; MUST REMOVE UNINSTALLER, too
  Delete $INSTDIR\uninstall.exe
  ; remove shortcuts, if any.
  Delete "$SMPROGRAMS\Mp3 Tag Tools v1.2\*.*"
  Delete "$DESKTOP\Mp3 Tag Tools v1.2.008.lnk"
  ; remove directories used.
  RMDir "$SMPROGRAMS\Mp3 Tag Tools v1.2"
  RMDir "$INSTDIR"
SectionEnd

; eof
