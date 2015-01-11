@ECHO OFF
SET "PROJECT_DIR=%~dp0"
SET "PROJECT_DIR=%PROJECT_DIR:~0,-1%"
"%PROJECT_DIR%/thirdparty/bin/make/make.exe" %*