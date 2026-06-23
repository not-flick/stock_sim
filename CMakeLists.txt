cmake_minimum_required(VERSION 3.20)

project(stock_sim)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(matplotplusplus)

add_executable(stock_sim
    Src/main.cpp
)

target_link_libraries(
    stock_sim
    PRIVATE
    Matplot++::matplot
)