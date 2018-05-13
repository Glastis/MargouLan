cmake_minimum_required(VERSION 3.10)
project(esp8266_lamp C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories("/home/glastis/bin/arduino-1.8.5/hardware/arduino/avr/cores/arduino")

add_executable(esp8266_lamp
        esp8266_lamp.ino
        main.h
        utilities.cpp)
