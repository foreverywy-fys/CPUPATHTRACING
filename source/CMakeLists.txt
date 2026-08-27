set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CPU_PATH_TRACING_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(CPUPathTracing ${CPU_PATH_TRACING_SOURCES}
    src/renderer/base_renderer.cpp
    src/until/profile.cpp
    include/accelerate/bounds.hpp
    include/sample/spherical.hpp
    include/material/material.hpp
    include/material/diffuse_material.hpp
    include/material/specular_material.hpp
    src/material/specular_material.cpp
    include/material/dieletric_material.hpp)

add_custom_command(TARGET CPUPathTracing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/models"
        "$<TARGET_FILE_DIR:CPUPathTracing>/models"
)

target_include_directories(CPUPathTracing PUBLIC
    include
    "${CMAKE_SOURCE_DIR}/thirdparty/SFML/include"
)

target_link_libraries(CPUPathTracing PRIVATE glm::glm rapidobj::rapidobj SFML::Graphics)
target_compile_definitions(CPUPathTracing PUBLIC
    GLM_FORCE_DEPTH_ZERO_TO_ONE
    GLM_FORCE_RADIANS
    GLM_FORCE_LEFT_HANDED
    WITH_DEBUG_INFO
)
target_compile_features(CPUPathTracing PRIVATE cxx_std_17)
