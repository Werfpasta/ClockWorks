:: Win32/64 makefile, to be updated in lock-step with multi platform makefile.
@ECHO OFF
ECHO.
GOTO :CALL_TARGETS

:SETUP_ENV :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:: User Config

SET "STANDARD=-std=c++1z -nostdlib -nostdinc"

SET "WARNING=-Wall"
SET "ERROR=-pedantic-errors"

SET "DEBUG=-g -fstandalone-debug"

SET "OPTIMIZATION="
SET "OPTIMIZATION_RELEASE=-O3"
SET "OPTIMIZATION_DEBUG=-O0"

SET "DEFINE=CW_OS_WIN"
SET "DEFINE_x86=CW_ARCH_x86"
SET "DEFINE_x64=CW_ARCH_x64"

SET "LIBS_x86="
SET "LIBS_x64="
SET "THIRDPARTY_LIBS_x86=mssdk7.1a-x86\kernel32.lib mssdk7.1a-x86\user32.lib mssdk7.1a-x86\opengl32.lib"
SET "THIRDPARTY_LIBS_x64=mssdk7.1a-x64\kernel32.lib mssdk7.1a-x64\user32.lib mssdk7.1a-x64\opengl32.lib"

:: WINDOWS
SET "SUBSYSTEM=CONSOLE"
SET "ENTRY=CWMain"

::INSTANT FAST SLOW
SET "CRINKLER_COMP_DEBUG=INSTANT"
SET "CRINKLER_COMP_RELEASE=SLOW"

:: Paths
SET "PROJECT_DIR=%~dp0"
SET "PROJECT_DIR="%PROJECT_DIR:~0,-1%""
SET "PROJECT_DIR=%PROJECT_DIR:\=/%"
SET "SRC_DIR="%PROJECT_DIR:"=%/src""
SET "INC_DIR="%PROJECT_DIR:"=%/inc""
SET "LIB_DIR="%PROJECT_DIR:"=%/lib""
SET "BIN_DIR="%PROJECT_DIR:"=%/bin""
SET "DOC_DIR="%PROJECT_DIR:"=%/doc""

SET "BACKUP_DIR="%PROJECT_DIR:"=%/../backups""

SET "THIRDPARTY_DIR="%PROJECT_DIR:"=%/thirdparty""
SET "THIRDPARTY_SRC_DIR="%THIRDPARTY_DIR:"=%/src""
SET "THIRDPARTY_INC_DIR="%THIRDPARTY_DIR:"=%/inc""
SET "THIRDPARTY_LIB_DIR="%THIRDPARTY_DIR:"=%/lib""
SET "THIRDPARTY_BIN_DIR="%THIRDPARTY_DIR:"=%/bin""
SET "THIRDPARTY_DOC_DIR="%THIRDPARTY_DIR:"=%/doc""

:: Compiler Options
SET "CXX="%THIRDPARTY_BIN_DIR:"=%/clang/clang++.exe""

SET "EXCEPTIONS=-fno-exceptions"
SET "RTTI=-fno-rtti"

SET "DIAGNOSTICS=-fshow-column -fshow-source-location -fcaret-diagnostics"
SET "DIAGNOSTICS=%DIAGNOSTICS% -fcolor-diagnostics -fdiagnostics-format=clang"
SET "DIAGNOSTICS=%DIAGNOSTICS% -fdiagnostics-show-option"
SET "DIAGNOSTICS=%DIAGNOSTICS% -fdiagnostics-show-category=name"
SET "DIAGNOSTICS=%DIAGNOSTICS% -fdiagnostics-fixit-info"
SET "DIAGNOSTICS=%DIAGNOSTICS% -fdiagnostics-print-source-range-info"
SET "DIAGNOSTICS=%DIAGNOSTICS% -fdiagnostics-parseable-fixits"
SET "DIAGNOSTICS=%DIAGNOSTICS% -fno-elide-type -fdiagnostics-show-template-tree"

SET "CLANG_TARGET_x86=--target=i386-pc-windows-msvc"
SET "CLANG_TARGET_x64=--target=x86_64-pc-windows-msvc"

SET "OBJECT_FLAG=-c"
SET "OUTPUT-FLAG=-o"
SET "SYSTEM-INCLUDE-FLAG=-isystem"
SET "INCLUDE-FLAG=-I"

:: Linker x86

:: Crinkler
SET "GIT="%THIRDPARTY_BIN_DIR:"=%/git/git.exe""

:: Crinkler
SET "CRINKLER="%THIRDPARTY_BIN_DIR:"=%/crinkler14/crinkler.exe""
SET "CRINKLER_OPT=/UNSAFEIMPORT /NOINITIALIZERS /SUBSYSTEM:%SUBSYSTEM%"
SET "CRINKLER_OPT=%CRINKLER_OPT% /ENTRY:%ENTRY%"

:: kkrunchy
SET "KKRUNCHY="%THIRDPARTY_BIN_DIR:"=%"/kkrunchy023/kkrunchy.exe""

:: kkrunchy2
SET "KKRUNCHY_K7="%THIRDPARTY_BIN_DIR:"=%/kkrunchy023/kkrunchy_k7.exe""

CALL :RESOLVE_LIB_PATHS
EXIT /B REM ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:clean
CALL :ECHOEX RD /S /Q %BIN_DIR%
CALL :init
EXIT /B 1

:init
CALL :MKDIR %SRC_DIR%
CALL :MKDIR %INC_DIR%
CALL :MKDIR %LIB_DIR%
CALL :MKDIR %BIN_DIR%
CALL :MKDIR %DOC_DIR%
CALL :MKDIR %THIRDPARTY_DIR%
CALL :MKDIR %THIRDPARTY_SRC_DIR%
CALL :MKDIR %THIRDPARTY_INC_DIR%
CALL :MKDIR %THIRDPARTY_LIB_DIR%
CALL :MKDIR %THIRDPARTY_BIN_DIR%
CALL :MKDIR %THIRDPARTY_DOC_DIR%
EXIT /B

:all
ECHO all not implemented.
EXIT /B 1

:x86-release
CALL :clean
CALL :cxx-x86-release
CALL :crinkle-x86-release
call :run-x86-release
EXIT /B 1

:x64-release
CALL :clean
CALL :cxx-x64-release
CALL :link-x64-release
EXIT /B 1

:x86-debug
CALL :clean
CALL :cxx-x86-debug
CALL :crinkle-x86-debug
EXIT /B 1

:x64-debug
CALL :clean
CALL :cxx-x64-debug
CALL :link-x64-debug
EXIT /B 1

:run-x86-release
CALL :ECHOEX "%BIN_DIR:"=%/x86-release.exe"
EXIT /B

:run-x64-release
CALL :ECHOEX "%BIN_DIR:"=%/x64-release.exe"
EXIT /B

:run-x86-debug
CALL :ECHOEX "%BIN_DIR:"=%/x86-debug.exe"
EXIT /B

:run-x64-debug
CALL :ECHOEX "%BIN_DIR:"=%/x64-debug.exe"
EXIT /B

:cxx-x86-release
CALL :ECHOEX %CXX% %STANDARD% %WARNING% %ERROR% %CLANG_TARGET_x86% %EXCEPTIONS% ^
%DIAGNOSTICS% %RTTI% %OPTIMIZATION_RELEASE% ^
%INCLUDE-FLAG%%INC_DIR% %INCLUDE-FLAG%%THIRDPARTY_INC_DIR% %OBJECT_FLAG% ^
%OUTPUT-FLAG% "%BIN_DIR:"=%/x86-release.obj" "%SRC_DIR:"=%\main.cpp"
EXIT /B

:cxx-x64-release
CALL :ECHOEX %CXX% %STANDARD% %WARNING% %ERROR% %CLANG_TARGET_x64% %EXCEPTIONS% ^
%DIAGNOSTICS% %RTTI% %OPTIMIZATION_RELEASE% ^
%INCLUDE-FLAG%%INC_DIR% %INCLUDE-FLAG%%THIRDPARTY_INC_DIR% %OBJECT_FLAG% ^
%OUTPUT-FLAG% "%BIN_DIR:"=%/x64-release.obj" "%SRC_DIR:"=%\main.cpp"
EXIT /B

:cxx-x86-debug
CALL :ECHOEX %CXX% %STANDARD% %WARNING% %ERROR% %CLANG_TARGET_x86% %EXCEPTIONS% ^
%DIAGNOSTICS% %RTTI% %DEBUG% %OPTIMIZATION_DEBUG% ^
%INCLUDE-FLAG%%INC_DIR% %INCLUDE-FLAG%%THIRDPARTY_INC_DIR% %OBJECT_FLAG% ^
%OUTPUT-FLAG% "%BIN_DIR:"=%/x86-debug.obj" "%SRC_DIR:"=%\main.cpp"
EXIT /B

:cxx-x64-debug
CALL :ECHOEX %CXX% %STANDARD% %WARNING% %ERROR% %CLANG_TARGET_x64% %EXCEPTIONS% ^
%DIAGNOSTICS% %RTTI% %DEBUG% %OPTIMIZATION_DEBUG% ^
%INCLUDE-FLAG%%INC_DIR% %INCLUDE-FLAG%%THIRDPARTY_INC_DIR% %OBJECT_FLAG% ^
%OUTPUT-FLAG% "%BIN_DIR:"=%/x64-debug.obj" "%SRC_DIR:"=%\main.cpp"
EXIT /B

:link
ECHO link not implemented.
EXIT /B 1

:link-x64-debug
SET "CLANG_LLD="%THIRDPARTY_BIN_DIR:"=%/clang/lld.exe""
SET "CLANG_LLD_OPT=/NODEFAULTLIB /SUBSYSTEM:%SUBSYSTEM% /ENTRY:%ENTRY% /INCREMENTAL:NO /MERGE:.rdata=.text /DEBUG"
CALL :ECHOEX %CLANG_LLD% -flavor link %CLANG_LLD_OPT% "/out:%BIN_DIR:"=%/x64-debug.exe" ^
%LIBS_x64_R% "%BIN_DIR:"=%/x64-debug.obj"
EXIT /B

:crinkle-x86-release
CALL :ECHOEX %CRINKLER% %CRINKLER_OPT% /COMPMODE:%CRINKLER_COMP_RELEASE% "/out:%BIN_DIR:"=%/x86-release.exe" ^
%LIBS_x86_R% "%BIN_DIR:"=%/x86-release.obj"
EXIT /B 1

:crinkle-x86-debug
CALL :ECHOEX %CRINKLER% %CRINKLER_OPT% /COMPMODE:%CRINKLER_COMP_DEBUG% "/out:%BIN_DIR:"=%/x86-debug.exe" ^
%LIBS_x86_R% "%BIN_DIR:"=%/x86-debug.obj"
EXIT /B 1

:kkrunch
:: http://www.farbrausch.de/~fg/kkrunchy/ When the time comes to move to 64k
ECHO kkrunch not implemented.
EXIT /B 1

:version
ECHO version not implemented.
EXIT /B 1

:potato
ECHO LostOfThought assumes the form of a potato...
EXIT /B

:local-backup
CALL :GEN_TIMESTAMP
CALL :MKDIR "%BACKUP_DIR:"=%/%TIMESTAMP%"
CALL :ECHOEXS ROBOCOPY %PROJECT_DIR% "%BACKUP_DIR:"=%/%TIMESTAMP%" /E /COPYALL /MT
CALL :MKDIR "%BACKUP_DIR:"=%/zip"
CALL :ZIPDIR "%BACKUP_DIR:"=%/%TIMESTAMP%" "%BACKUP_DIR:"=%/zip/%TIMESTAMP%.zip"
EXIT /B

:git-stage-all
%GIT% add -A %PROJECT_DIR%
EXIT /B

:git-commit-auto
%GIT% commit -m "Auto commit by make.cmd"
EXIT /B

:git-commit
%GIT% commit
EXIT /B

:git-init
%GIT% init
EXIT /B

:git-status
%GIT% status
EXIT /B

:git-branch-develop
EXIT /B

:git-branch-master
EXIT /B

:git-auto
CALL :git-stage-all
CALL :git-commit-auto
EXIT /B

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:CALL_TARGETS
IF [%~1]==[] (GOTO :potato)
SET "CALL_TARGETS_ERROR=0"
CALL :SETUP_ENV
CALL :init
:CALL_TARGETS_while
IF [%~1]==[] (GOTO :CALL_TARGETS_break)
CALL :LABLE_EXIST %~1
IF [%RESULT%]==[0] (
	CALL ERROR: Target '%~1' not recognised.
	SET "CALL_TARGETS_ERROR=1"
) ELSE (
	CALL :%~1
)
ECHO.
SHIFT
GOTO :CALL_TARGETS_while
:CALL_TARGETS_break
IF [%CALL_TARGETS_ERROR%]==[0] (
	ECHO All operations completed sucessfuly
) ELSE (
	CALL ERROR: Not all targets were recognised.
)
EXIT /B

:RESOLVE_LIB_PATHS
SET "LIBS_x86_R="
SET "LIBS_x64_R="

FOR /F %%P IN ("%LIBS_x86%") DO (
	SET "LIBS_x86_R=%LIBS_x86_R% "%LIB_DIR%/%%P" "
)

FOR /F %%P IN ("%LIBS_x64%") DO (
	SET "LIBS_x64_R=%LIBS_x64_R% "%LIB_DIR%/%%P" "
)

FOR /F %%P IN ("%THIRDPARTY_LIBS_x86%") DO (
	SET "LIBS_x86_R=%LIBS_x86_R% "%THIRDPARTY_LIB_DIR%/%%P" "
)

FOR /F %%P IN ("%THIRDPARTY_LIBS_x64%") DO (
	SET "LIBS_x64_R=%LIBS_x64_R% "%THIRDPARTY_LIB_DIR%/%%P" "
)
EXIT /B

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:STRIP_QUOTES [string]
SET "RESULT=%~1"
SET "RESULT=%RESULT:"=%"
EXIT /B

:GIT_IGNORE_FOLDER [path]
CALL :MKDIR %~1
CALL :STRIP_QUOTES %~1
>"%RESULT%/.gitignore" ECHO *
>>"%RESULT%/.gitignore" ECHO !.gitignore
EXIT /B

:LABLE_EXIST [lable]
FINDSTR /r "^:%~1\>" "%~f0" >nul
IF ERRORLEVEL 0 (
	SET "RESULT=1"
) ELSE (
	SET "RESULT=0"
)
EXIT /B

:GEN_TIMESTAMP
SETLOCAL
FOR /f "tokens=2 delims==" %%a IN ('wmic OS Get localdatetime /value') DO SET "dt=%%a"
SET "YY=%dt:~2,2%" & SET "YYYY=%dt:~0,4%" & SET "MM=%dt:~4,2%" & SET "DD=%dt:~6,2%"
SET "HH=%dt:~8,2%" & SET "Min=%dt:~10,2%" & SET "Sec=%dt:~12,2%"
ENDLOCAL & SET "TIMESTAMP=%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%"
EXIT /B

:FILE_EMPTY [path]
SETLOCAL
FOR /f %%i IN (%~1) DO (SET "SIZE=%%~zi")
ENDLOCAL & IF [%SIZE%]==[] (SET "RESULT=1") ELSE (SET "RESULT=0")
EXIT /B

:GET_OUTPUT
SETLOCAL
%LINKER% 1>%LTMP% 2>&1
MORE +0 <%LTMP% >%LTMP2%
SET /p "LINKERV="<%LTMP2% >nul
EXIT /B

:MKDIR [dir]
IF NOT EXIST "%~1" (
	CALL :ECHOEX MKDIR "%~1"
)
EXIT /B

:ZIPDIR [from] [to]
SETLOCAL
PUSHD %1
CALL :ECHOEXS "%THIRDPARTY_BIN_DIR:"=%/zip/zip.exe" -r -q %2 "."
POPD
EXIT /B

:ECHOEX
ECHO %*
%*
EXIT /B

:ECHOEXS
ECHO %*
2>&1 >NUL %*
EXIT /B