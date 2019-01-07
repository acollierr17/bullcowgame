cmake_minimum_required(VERSION 3.13)
project(BullCowGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Debug)

add_executable(BullCowGame
        Debug/BullCowGame.pch
        FBullCowGame.cpp
        FBullCowGame.h
        main.cpp
        pch.cpp
        pch.h)
