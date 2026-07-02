cmake_minimum_required(VERSION 3.22)
project(AutoPick C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)
set(CMAKE_EXE_LINKER_FLAGS -m32)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

add_executable(AutoPick
        Main.c
        Game.c
        Memory.c
        Process.c
)

# 清单文件
target_sources(AutoPick PRIVATE "res.rc")
