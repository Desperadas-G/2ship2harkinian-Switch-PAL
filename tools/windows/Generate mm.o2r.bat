@echo off
rem Drop your Majora's Mask ROM on this file (or put it next to it and double-click).
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0generator\generate-mm-o2r.ps1" "%~1"
echo.
pause
