cmake_minimum_required(VERSION 3.16)
project(strands_game CXX)

set(CMAKE_CXX_STANDARD 17)

# Fetch FTXUI
include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
  GIT_TAG v5.0.0   # pick latest stable tag
)
FetchContent_MakeAvailable(ftxui)

# Build your app
add_executable(strands_game main.cpp)
target_link_libraries(strands_game PRIVATE ftxui::component)