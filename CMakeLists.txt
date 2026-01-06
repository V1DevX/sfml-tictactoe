cmake_minimum_required(VERSION 3.20)
project(sfml_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main 
  src/main.cpp
  src/App.cpp
  src/Board.cpp
)

find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)

target_link_libraries(main PRIVATE
  SFML::Graphics
  SFML::Window
  SFML::System
)
