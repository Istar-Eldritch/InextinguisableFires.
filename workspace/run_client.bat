call vars.bat


set "mod=P:\Mods\@CF;P:\Mods\@Community-Online-Tools;P:\Mods\@IEF;%BUILD_PATH%"


start /D "%DAYZ_PATH%" DayZDiag_x64.exe "-mod=%mod%"^
    "-name=Istar Eldritch" -newErrorsAreWarnings=1 -filePatching -connect=127.0.0.1 -port=2302 -window