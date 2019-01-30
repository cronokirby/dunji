project(dunji)

add_executable(${PROJECT_NAME} src/main.cpp src/graphics.cpp)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} X11)
