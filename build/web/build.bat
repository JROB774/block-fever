@echo off
setlocal

if "%1"=="" ( set BuildMode=release ) else ( set BuildMode=%1 )

if %BuildMode%==release goto success
if %BuildMode%==final goto success

goto failure

:success

call config.bat

if not exist %OutputPath% mkdir %OutputPath%

call timer.bat emcc %InputSource% %IncludeDirs% %Libraries% %Defines% %CompilerFlags% %LinkerFlags% --preload-file %AssetPath% -o %OutputExecutable%.html

if %BuildMode%==final goto package

goto end

:package
pushd %OutputPath%
set ZipName=%OutputName%-v%Version%-Web.zip
if exist %ZipName% rm %ZipName%
tar -a -c --exclude=%OutputName%.html -f %ZipName% * -C ../../source/Platform/HTML/ index.html loading.png
popd

goto end

:failure
echo Invalid build target selected!
goto end

:end

endlocal
