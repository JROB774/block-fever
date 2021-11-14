@echo off
setlocal

call config.bat

cd %OutputPath%
start python -m http.server

endlocal
