@echo off
echo 清除所有obj pch idb pdb ncb opt plg res sbr ilk suo文件，请稍等......
pause
del /f /s /q .\*.obj
del /f /s /q .\*.pch
del /f /s /q .\*.idb
del /f /s /q .\*.pdb
del /f /s /q .\*.ncb 
del /f /s /q .\*.opt 
del /f /s /q .\*.plg
del /f /s /q .\*.res
del /f /s /q .\*.sbr
del /f /s /q .\*.ilk
del /f /s /q .\*.aps
del /f /s /q .\*.sdf
del /f /s /q .\*.suo
del /f /s /q .\*.sdf
del /f /s /q .\*.tlog
del /f /s /q .\*.exp

REM 以下针对网狐中的
rd /s /q Obj
for /f "delims=" %%i in ('dir /ad /b /s "Obj"') do (
   rd /s /q "%%i"
)

rd /s /q Publish
for /f "delims=" %%i in ('dir /ad /b /s "ipch"') do (
   rd /s /q "%%i"
)  
      
rd /s /q Release_Unicode
for /f "delims=" %%i in ('dir /ad /b /s "Release_Unicode"') do (
   rd /s /q "%%i"
)

rd /s /q Backup
for /f "delims=" %%i in ('dir /ad /b /s "Backup"') do (
   rd /s /q "%%i"
)

for /f "delims=" %%i in ('dir /ad /b /s "Cookies"') do (
   rd /s /q "%%i"
)

rd /s /q obj
for /f "delims=" %%i in ('dir /ad /b /s "obj"') do (
   rd /s /q "%%i"
)

rd /s /q assets
for /f "delims=" %%i in ('dir /ad /b /s "assets"') do (
   rd /s /q "%%i"
)

rd /s /q bin
for /f "delims=" %%i in ('dir /ad /b /s "bin"') do (
   rd /s /q "%%i"
)

rd /s /q gen
for /f "delims=" %%i in ('dir /ad /b /s "gen"') do (
   rd /s /q "%%i"
)

rd /s /q _UpgradeReport_Files
for /f "delims=" %%i in ('dir /ad /b /s "_UpgradeReport_Files"') do (
   rd /s /q "%%i"
)

rd /s /q Ruler
for /f "delims=" %%i in ('dir /ad /b /s "Ruler"') do (
   rd /s /q "%%i"
)

rd /s /q Debug
for /f "delims=" %%i in ('dir /ad /b /s "Debug"') do (
   rd /s /q "%%i"
)
echo 清除文件完成！
echo. & pause