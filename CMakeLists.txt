cmake_minimum_required(VERSION 3.19)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(PasswordManager main.cpp Category.h PasswordRecord.h)