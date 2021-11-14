@echo off
setlocal

call config.bat
pushd %OutputPath%
%OutputName%.exe %*
popd

endlocal
