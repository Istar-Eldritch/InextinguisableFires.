call vars.bat

setlocal enabledelayedexpansion

FOR /D %%i IN (..\modules\*) DO (
    set filename=%%~ni

    rmdir "!DAYZ_PATH!\!filename!" /s /q
    rmdir "P:\!filename!" /s /q
)

endlocal


@REM IEF

rmdir "%DAYZ_PATH%\IEF" /s /q
rmdir "P:\IEF" /s /q

@REM Community Framework

rmdir "%DAYZ_PATH%\JM\COT" /s /q
rmdir "P:\JM\COT" /s /q

rmdir "%DAYZ_PATH%\JM" /s /q
rmdir "P:\JM" /s /q

rmdir "P:\Mods" /s /q

start /wait /D "%WORKDRIVE_PATH%" WorkDrive.exe /Dismount P