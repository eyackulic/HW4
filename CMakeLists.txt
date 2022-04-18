cmake_minimum_required(VERSION 3.16)
project(HW4)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW4_main main.cpp BLAST_DB.cpp FASTAreadset_HT.cpp FASTAreadset_LL.cpp test.cpp)
