cmake_minimum_required(VERSION 2.6)
project(toy-rsa)

add_executable(toy_rsa
	src/random.cc
	src/main.cc
	src/bigint.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
