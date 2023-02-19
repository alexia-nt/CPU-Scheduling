cmake_minimum_required(VERSION 3.24)
project(opsysProj C)

set(CMAKE_C_STANDARD 17)

add_executable(fcfs fcfs.c)
add_executable(sjf sjf.c)
add_executable(srtf srtf.c)
add_executable(rr rr.c)