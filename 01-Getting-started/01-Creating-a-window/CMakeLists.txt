cmake_minimum_required(VERSION 2.9)

project(main)

aux_source_directory(. C_SRCs)

add_executable(main ${C_SRCs} /usr/include/glad/glad.c)

target_link_libraries(main GLEW glfw GL X11 pthread Xrandr Xi dl)
