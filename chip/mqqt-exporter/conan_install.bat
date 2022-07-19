rmdir /q /s build 2>nul

conan remote clean
conan remote add conancenter https://center.conan.io --force --insert=2

conan install . -if ./build/Debug -g cmake_find_package_multi --build missing -s build_type=Debug
conan install . -if ./build/Release -g cmake_find_package_multi --build missing -s build_type=Release
