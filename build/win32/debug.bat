@echo off
setlocal

call findvs.bat
call config.bat
call %VSDevPath% -no_logo -arch=%Architecture%
devenv %OutputExecutable%.exe

endlocal
