cmake_minimum_required (VERSION 3.1)
project(main)

find_package(Threads REQUIRED QUIET)
find_package(OpenGL REQUIRED QUIET)

set(CMAKE_CXX_STANDARD 20)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_BINARY_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/glm
)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui)
set(IMGUI_SOURCES 
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# The main executable
add_executable(main
  src/Application.cpp
  src/Application.cpp
  src/MyApplication.cpp
  src/MyApplication.cpp
  src/glError.hpp
  src/glError.cpp
  src/main.cpp
  src/Shader.hpp
  src/Shader.cpp
  ${IMGUI_SOURCES}
)

if (EMSCRIPTEN)
  target_link_libraries(main PUBLIC "-s USE_GLFW=3")
  target_link_libraries(main PUBLIC "-s USE_WEBGL2=1")
  target_link_libraries(main PUBLIC "-s WASM=1")

  # Copy the index.html file.
  FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/index.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  foreach(asset "shader/shader.frag" "shader/shader.vert")
    FILE(COPY ${asset} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)
  endforeach(file)

  # Allow the directories /shader and /data to be fetched by the web browser.
  set_property(TARGET main APPEND_STRING PROPERTY LINK_FLAGS
    "--preload-file ${CMAKE_CURRENT_BINARY_DIR}/shader/@/shader/")
  
# else() # Not Web
#   # glfw
#   add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
#   target_link_libraries(main PRIVATE glfw)
#   # glew
#   add_definitions(-DGLEW_STATIC)
#   add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
#   target_link_libraries(main PRIVATE libglew_static)
endif()

add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/asset.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/src/asset.hpp
)
