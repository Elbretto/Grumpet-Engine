@echo off
setlocal enabledelayedexpansion

set scripts=
for /r %%f in (*.c) do (
    set scripts=!scripts! %%f
)

set executableName=test
set flags=-g -Wall -Werror
set includes=-Isrc
set linkers=-L../bin/
set defines=-D_DEBUG -D_EXPORT

echo building test...
clang %scripts% -o../bin/%executableName%.exe %includes% %linkers% %flags% %defines%
echo build complete