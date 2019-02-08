project(dunji)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/area.cpp
    src/enemies.cpp
    src/graphics.cpp
    src/player.cpp
)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} X11)
