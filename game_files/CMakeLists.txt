cmake_minimum_required(VERSION 3.16)

option(CMAKE_INSTALL_PREFIX "Path to install")

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(puzzle15 Singleton.cpp Command.cpp Subject.cpp Observer.cpp main.cpp)
target_link_libraries(puzzle15 sfml-graphics sfml-audio)

install(TARGETS puzzle15 DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

#add_dependencies(puzzle15 ${CMAKE_INSTALL_PREFIX}/bin/font.ttf)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/font.ttf
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

add_custom_command(
        TARGET puzzle15 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/font.ttf
                ${CMAKE_INSTALL_PREFIX}/bin/font.ttf)





