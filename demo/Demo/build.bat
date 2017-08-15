@echo off
pushd %cd%
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64 
popd
echo %cd% 
REM optional: /Wall
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:demo.exe
cl.exe %compilerflags% *.cpp stl/*.cpp stl/containers/*.cpp /link %linkerflags%
echo Build completed.