# 3d-again

conan install . --output-folder=build --build=missing --settings=build_type=Debug
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build build
make --build build --target test