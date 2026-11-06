@echo off
rem Merges every training session in the pgo folder into bouquet.profdata.
cd /d "%~dp0"
if not exist pgo\*.profraw (
  echo No profile found in the pgo folder. Play a few minutes first, then close Bouquet.
  pause
  exit /b 1
)
llvm-profdata.exe merge -o bouquet.profdata pgo\*.profraw
if errorlevel 1 (
  echo The merge failed.
  pause
  exit /b 1
)
echo.
echo Done: bouquet.profdata is next to this file. Send it to be built into Bouquet.
pause
