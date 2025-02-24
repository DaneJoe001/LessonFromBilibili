cmake_minimum_required(VERSION 3.18)

project(Lesson02 LANGUAGES CXX)

set(CXX_STANDARD 17)

set(CXX_STANDARD_REQUIRED on)

add_subdirectory(Client)

add_subdirectory(Server)