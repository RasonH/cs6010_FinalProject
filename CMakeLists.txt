

cmake_minimum_required(VERSION 3.15)

# the game ( Xcode devs please comment the tests section below )

project(finalProject)

add_executable(finalProject src/main.cpp src/components/Cell.hpp src/components/Grid.hpp src/utils/Canvas.hpp src/utils/Constants.hpp src/utils/Frame.hpp)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

find_package(SFML 2.5 COMPONENTS audio REQUIRED)

target_link_libraries(finalProject sfml-graphics sfml-audio)

target_compile_options(finalProject PUBLIC -std=c++17)

# the tests

project(finalProjectTests)

add_executable(finalProjectTests src/tests.cpp src/components/Cell.hpp src/components/Grid.hpp src/utils/Canvas.hpp src/utils/Constants.hpp src/utils/Frame.hpp)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

find_package(SFML 2.5 COMPONENTS audio REQUIRED)

target_link_libraries(finalProjectTests sfml-graphics sfml-audio)

target_compile_options(finalProjectTests PUBLIC -std=c++17)