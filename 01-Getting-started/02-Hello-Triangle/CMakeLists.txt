cmake_minimum_required(VERSION 2.9)

project(main)

add_compile_options(-g)
aux_source_directory(. C_SRCs)

add_executable(main ${C_SRCs})

target_link_libraries(main GLEW glfw GL X11 pthread Xrandr Xi simpidbit dl)
