@echo off
pushd %cd%
call "c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64 10.0.16299.0
popd
echo %cd% 
REM optional: /Wall
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:demo.exe
"c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.13.26128\bin\Hostx64\x64\cl.exe" %compilerflags% *.cpp stl/*.cpp stl/containers/*.cpp /link %linkerflags%
echo Build completed.