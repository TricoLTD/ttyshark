cmake_minimum_required(VERSION 3.15)
project(ttyshark CXX)



add_executable(ttyshark src/ttyshark.cpp src/main.cpp)



install(TARGETS ttyshark DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
