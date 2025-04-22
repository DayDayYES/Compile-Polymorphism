cmake_minimum_required(VERSION 3.30)
project(Compile_Polymorphism)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compile_Polymorphism main.cpp
        Logger.cpp
        Logger.h
        Task.cpp
        Task.h
        TaskManger.cpp
        TaskManger.h
        Command.cpp
        Command.h)
