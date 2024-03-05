#!/bin/bash


if [ "$1" = "clean" ]
then
    rm -rf build
    rm compile_commands.json
elif [ "$1" = "debug" ]
then
    cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build
    cmake --build build --parallel
    cmake --install build
    ln -sfr build/compile_commands.json compile_commands.json
else
    cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
    cmake --build build --parallel
    cmake --install build
    ln -sfr build/compile_commands.json compile_commands.json
fi


