@ECHO OFF

FOR /D %%d IN (*) DO CALL :removeTempDirsForProject "%~dp0%%d"

ECHO Cleaning %~dp0
RD /S /Q "%~dp0\Debug" >NUL 2>&1
RD /S /Q "%~dp0\Release" >NUL 2>&1
RD /S /Q "%~dp0\ipch" >NUL 2>&1
DEL /Q "%~dp0\*.sdf" >NUL 2>&1
ATTRIB -h "%~dp0\*.suo" >NUL 2>&1
DEL /Q "%~dp0\*.suo" >NUL 2>&1

GOTO :EOF

:removeTempDirsForProject
	ECHO	Cleaning %1
	RD /S /Q %1\Debug >NUL 2>&1
	RD /S /Q %1\Release >NUL 2>&1
	DEL /Q %1\*.filters >NUL 2>&1
	DEL /Q %1\*.user >NUL 2>&1
	GOTO	:EOF
