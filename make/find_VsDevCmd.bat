@ECHO OFF
SET VsDevCmd=%~dp0
SET VsDevCmd=%VsDevCmd%VsDevCmd.location
IF EXIST %VsDevCmd% (
    SET /p VsDevCmd=<%VsDevCmd%
	IF NOT EXIST %VsDevCmd% (
		GOTO find
	)
) ELSE (
:find
    PUSHD C:\
	DIR /S /B VsDevCmd.bat > %VsDevCmd%
	SET /p VsDevCmd=<%VsDevCmd%
	POPD
)
call "%VsDevCmd%" x86
@ECHO ON