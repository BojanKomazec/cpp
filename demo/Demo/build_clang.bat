@echo off
pushd %cd%

REM Setting the compiler environment before calling Ninja generation
call "c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64 10.0.16299.0
popd
echo %cd% 
REM optional: /Wall
REM set compilerflags=/Od /Zi /EHsc
REM set linkerflags=/OUT:demo.exe

mkdir build-ninja
cd build-ninja

echo Executing cmake...
REM Call a CMake Ninja generator which generates required Ninja build files (build.ninja, rules.ninja, CMakeCache.txt, CMakeFiles, cmake_install.cmake)
cmake .. -G Ninja -DCMAKE_CXX_COMPILER="c:/Program Files/LLVM/bin/clang-cl.exe" -DCMAKE_C_COMPILER="c:/Program Files/LLVM/bin/clang-cl.exe" -DCMAKE_LINKER:PATH="C:/Program Files/LLVM/bin/lld-link.exe" -DCMAKE_SYSTEM_VERSION=10.0.16299.0 -DCMAKE_BUILD_TYPE='Debug' -DCMAKE_SYSTEM_NAME='Generic'

echo Executing ninja...
ninja -v

cd ..

echo Build completed.