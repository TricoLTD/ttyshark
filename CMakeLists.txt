cmake_minimum_required(VERSION 3.15)
project(ttyshark CXX)

cmake_policy(SET CMP0111 NEW)

set(CMAKE_CXX_STANDARD 23)

#find_package(libmodbus REQUIRED)

add_executable(ttyshark src/ttyshark.cpp src/main.cpp
        src/modbusRTU/modbusrtu.cpp
        src/modbusRTU/modbusrtu.h
        src/serialcap/serialcap.cpp
        src/serialcap/serialcap.h
        src/IGMnet/igmnet.h)

#target_link_libraries(ttyshark PRIVATE libmodbus::libmodbus)

install(TARGETS ttyshark DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
