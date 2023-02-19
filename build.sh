mkdir -p build

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -H./ -B./build
cmake --build build/ --config Debug --target Graphs-Practice -j 4