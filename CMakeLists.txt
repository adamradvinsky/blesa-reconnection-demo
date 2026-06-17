cmake_minimum_required(VERSION 3.10)

project("state-machine-vulnerability")


add_executable(
    smv 
    src/main.cpp 
    src/Client.cpp 
    src/Server.cpp
)


target_link_libraries(smv
    ws2_32
)