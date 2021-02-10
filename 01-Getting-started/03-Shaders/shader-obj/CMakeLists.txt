cmake_minimum_required(VERSION 2.9)

project(main)

add_compile_options(-g)
aux_source_directory(. CXX_SRCs)

add_executable(main ${CXX_SRCs})

target_link_libraries(main glfw GL simpidbitxx dl m spshader)
