cmake_minimum_required(VERSION 3.15)
project(ttyshark CXX)

cmake_policy(SET CMP0111 NEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)

#find_package(libmodbus REQUIRED)

add_executable(ttyshark src/ttyshark.cpp src/main.cpp
        src/modbusRTU/modbusrtu.cpp
        src/modbusRTU/modbusrtu.h
        src/serialcap/serialcap.cpp
        src/serialcap/serialcap.h
        src/IGMnet/igmnet.h)


find_package(ftxui REQUIRED)
target_link_libraries(ttyshark PRIVATE ftxui::ftxui)
#target_link_libraries(ttyshark PRIVATE libmodbus::libmodbus)

install(TARGETS ttyshark DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
