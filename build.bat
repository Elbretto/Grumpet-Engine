@echo off
setlocal enabledelayedexpansion

set scripts=
for /r %%f in (*.c) do (
    set scripts=!scripts! %%f
)

set executableName=engine
set flags=-g -Wall -Werror
set includes=-Isrc
set linkers=-L../bin/
set defines=-D_DEBUG -D_EXPORT

echo building engine...
clang %scripts% -o../bin/%executableName%.exe %includes% %linkers% %flags% %defines%
echo build complete