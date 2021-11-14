@echo off
setlocal

if "%1"=="" ( set BuildMode=debug ) else ( set BuildMode=%1 )

if %BuildMode%==debug goto success
if %BuildMode%==release goto success
if %BuildMode%==final goto success

goto failure

:success

call findvs.bat
call config.bat

call %VSDevPath% -no_logo -arch=%Architecture%

if not exist %OutputPath% mkdir %OutputPath%

if not exist %OutputPath%\SDL2.dll copy %SDL2BinDir%\SDL2.dll %OutputPath%
if not exist %OutputPath%\SDL2_mixer.dll copy %SDL2MixerBinDir%\SDL2_mixer.dll %OutputPath%

if %BuildMode%==release goto icon
if %BuildMode%==final goto icon

goto build

:icon
rc -nologo -i %ResourcePath% %ResourceFile%

:build

call timer.bat "cl %IncludeDirs% %Defines% %CompilerFlags% %CompilerWarnings% -Fe%OutputExecutable% %InputSource% -link %LinkerFlags% %LinkerWarnings% %LibraryDirs% %Libraries% %InputResource%"

del *.obj

if %BuildMode%==release goto resources
if %BuildMode%==final goto resources

goto end

:resources
if exist %OutputPath%\Resources\ (
    rmdir /s /q %OutputPath%\Resources\
)
xcopy assets %OutputPath%\Resources\ /E

if %BuildMode%==final goto package

goto end

:package
pushd %OutputPath%
set ZipName=%OutputName%.zip
if exist %ZipName% rm %ZipName%
tar -a -c --exclude=save.dat --exclude=*.log --exclude=*.pdb --transform 's,^,RUNNER/,' -f %ZipName% *
popd

goto end

:failure
echo Invalid build target selected!
goto end

:end

endlocal
