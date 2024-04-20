call vars.bat

if not exist "%SCRIPT_DIR%\mission" (
    mkdir "%SCRIPT_DIR%\mission"
    xcopy /s "%DAYZ_SERVER_PATH%\mpmissions\dayzOffline.chernarusplus" "%SCRIPT_DIR%\mission\dayzOffline.chernarusplus"
)

set "mod=P:\Mods\@CF;P:\Mods\@Community-Online-Tools;P:\Mods\@IEF;%BUILD_PATH%"

start /D "%DAYZ_PATH%" DayZDiag_x64.exe "-mission=%SCRIPT_DIR%\mission\dayzOffline.chernarusplus" "-mod=%mod%"^
 -server -newErrorsAreWarnings=1 -filePatching "-profiles=%SCRIPT_DIR%\profiles" "-config=%SCRIPT_DIR%\serverDZ.cfg"