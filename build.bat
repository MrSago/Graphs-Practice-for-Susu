@echo off

mkdir build 2>nul

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -H.\ -B.\build -G "MinGW Makefiles"
cmake --build build\ --config Debug --target Graphs-Practice -j 4