@ECHO OFF

SET GAME_DIR=%~dp0
SET PLATFORM=x32
SET CONFIG=Release
SET PLATFORM_DIR=%GAME_DIR%Shinra\%PLATFORM%\%CONFIG%\

GOTO :MAIN

:MKLINK
IF EXIST %1 DEL %1
MKLINK %1 %2
IF ERRORLEVEL 1 COPY %2 %1

GOTO :EOF

:MAIN

FOR %%X in ( D3D9, D3D11, DXGI ) DO CALL :MKLINK "%GAME_DIR%%%X.dll" "%PLATFORM_DIR%Shim%%X.dll"
FOR %%X in ( 1_3, 1_4, 9_1_0 ) DO CALL :MKLINK "%GAME_DIR%XInput%%X.dll" "%PLATFORM_DIR%ShimXInput.dll"
FOR %%X in ( CloudCoreClient, d3dcompiler_47 ) DO CALL :MKLINK "%GAME_DIR%%%X.dll" "%PLATFORM_DIR%%%X.dll"
