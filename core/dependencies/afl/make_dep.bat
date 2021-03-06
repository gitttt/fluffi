::   Copyright 2017-2019 Siemens AG
::
::   Licensed under the Apache License, Version 2.0 (the "License");
::   you may not use this file except in compliance with the License.
::   You may obtain a copy of the License at
::
::       http://www.apache.org/licenses/LICENSE-2.0
::
::   Unless required by applicable law or agreed to in writing, software
::   distributed under the License is distributed on an "AS IS" BASIS,
::   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
::   See the License for the specific language governing permissions and
::   limitations under the License.
:: 
:: Author(s): Thomas Riedmaier, Pascal Eckmann


IF NOT DEFINED VCVARSALL (
		ECHO Environment Variable VCVARSALL needs to be set!
		goto errorDone
)



RMDIR /Q/S lib

MKDIR lib
MKDIR lib\x64
MKDIR lib\x86

RMDIR /Q/S afl

REM Getting afl

git clone https://github.com/mirrorer/afl.git
cd afl
git checkout 2fb5a3482ec27b593c57258baae7089ebdc89043

Rem Apply patch that allows us to integrate the AFL Havoc mutations into FLUFFI

"C:\Program Files\Git\usr\bin\patch.exe" -p0 -i ..\afl.patch

REM Building AFL

mkdir build64
mkdir build86
SETLOCAL
cd build64
call %VCVARSALL% x64
cl.exe /MT /c /TP /EHsc ..\afl-fuzz.c
LIB.EXE /OUT:afl-fuzz.LIB afl-fuzz.obj
cl.exe /MTd /Debug /c /TP /EHsc ..\afl-fuzz.c
LIB.EXE /OUT:afl-fuzzd.LIB afl-fuzz.obj
cd ..
ENDLOCAL

SETLOCAL
cd build86
call %VCVARSALL% x86
cl.exe /MT /c /TP /EHsc ..\afl-fuzz.c
LIB.EXE /OUT:afl-fuzz.LIB afl-fuzz.obj
cl.exe /MTd /Debug /c /TP /EHsc ..\afl-fuzz.c
LIB.EXE /OUT:afl-fuzzd.LIB afl-fuzz.obj
cd ..
ENDLOCAL
cd ..


copy afl\build64\afl-fuzz.LIB lib\x64

copy afl\build64\afl-fuzzd.LIB lib\x64

copy afl\build86\afl-fuzz.LIB lib\x86

copy afl\build86\afl-fuzzd.LIB lib\x86


waitfor SomethingThatIsNeverHappening /t 10 2>NUL
::reset errorlevel
ver > nul

RMDIR /Q/S afl

goto done

:errorDone
exit /B 1

:done
exit /B 0
