@ECHO OFF
SETLOCAL
SET "PROJECT_DIR=%~dp0"
"%PROJECT_DIR:~0,-1%/thirdparty/bin/make/make.exe" %*
ENDLOCAL