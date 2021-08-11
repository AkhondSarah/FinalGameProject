# CMakeList.txt : CMake project for FinalProjectGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (FinalProjectGamePUBLIC "FinalProjectGame.cpp"   "GameController.h" "Player.h" "Tetris.h")

# TODO: Add tests and install targets if needed.
target_include_directories(FinalProjectGamePUBLIC PUBLIC "sfml/include")
target_link_directories(FinalProjectGamePUBLIC PUBLIC "sfml/lib")
target_link_libraries(FinalProjectGamePUBLIC "openal32.dll")
target_link_libraries(FinalProjectGamePUBLIC "sfml-system-d.dll")
target_link_libraries(FinalProjectGamePUBLIC "sfml-window-d.dll")
target_link_libraries(FinalProjectGamePUBLIC "sfml-graphics-d.dll")