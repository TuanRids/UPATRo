@echo off

REM Move up three directories
cd ..\..\..

echo Current directory: %CD%

xcopy /Y "%CD%\Lib\x64-release\*" "%CD%\out\build\x64-release\"
xcopy /Y "%CD%\Bin\x64-release\*" "%CD%\out\build\x64-release\"
xcopy /Y /s "%CD%\plugins\release\platforms\*" "%CD%\out\build\x64-release\platforms\"

xcopy /Y "%CD%\Lib\x64-debug\*" "%CD%\out\build\x64-debug\"
xcopy /Y "%CD%\Bin\x64-debug\*" "%CD%\out\build\x64-debug\"
xcopy /Y /s "%CD%\plugins\debug\platforms\*" "%CD%\out\build\x64-debug\platforms\"
