@echo off

del /s *.vc.db
del /s *.tlog
del /s *.log
del /s *.idb
del /s *.pdb
del /s *.lastbuildstate
del /s *.ilk
del /s *.exp
del /s *.obj
del /s *.iobj
del /s *.ipch
del /s *.tlh
del /s *.obj.enc
del /s *.tli
del /s *.exp
del /s *.pch
del /s *.res

for /f "delims=" %%a in ('dir /ad /b /s "%CD%"^|sort /r') do (
   rd "%%a">nul 2>nul && echo Remove "%%a"
)

pause