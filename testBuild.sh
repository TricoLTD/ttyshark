#!/bin/bash
# for doing test compiles and launchs of the project
# -c | --clean to cleanbuild Debug
FLAG_PASSED=false
while [[ $# -gt 0 ]]; do
  case "$1" in
  -c | --clean)
    FLAG_PASSED=true
    shift
    ;;
  *)
    shift
    ;;
  esac
done

if [ "$FLAG_PASSED" = true ]; then
  rm -rf build/Debug
  conan install . --output-folder=build/Debug --build=missing -s build_type=Debug
  cmake -S . -B build/Debug -DCMAKE_TOOLCHAIN_FILE=build/Debug/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
  cmake --build build/Debug
  ./build/Debug/ttyshark
else
  cmake --build build/Debug
  ./build/Debug/ttyshark
fi
