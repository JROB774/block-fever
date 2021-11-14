@echo off

:: This will be different for other people...
set emsdk_location=..\..\..\.emsdk

set path=%path%;%~dp0

if not exist %emsdk_location% goto no_emscripten
pushd %emsdk_location%
call emsdk_env.bat
cls
popd
goto end

:no_emscripten
echo Emscripten could not be found, web builds cannot be made!

:end
cd ..\..
