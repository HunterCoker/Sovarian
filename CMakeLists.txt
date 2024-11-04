cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(sovarian VERSION 1.0 LANGUAGES C CXX)

set(EXECUTABLE ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Enable unit tests" OFF)

include_directories(
	# ...
)

if(WIN32)
    message(STATUS "Including Win32 support")
    set(PLATFORM_SRC_FILES
        src/rendering/dx12/render_system_dx12.cpp
    )
    set(PLATFORM_HEADER_FILES
        src/rendering/dx12/render_system_dx12.h
    )
elseif(APPLE)
    message(STATUS "Including macOS support")
    set(APPEND PLATFORM_SRC_FILES
        src/rendering/metal/render_system_metal.cpp
    )
    set(APPEND PLATFORM_HEADER_FILES
        src/rendering/metal/render_system_metal.h
    )
elseif(UNIX AND NOT APPLE)
    message(FATAL_ERROR "Linux support is not implemented")
endif()

set(SRC_FILES
	src/main.cpp
	src/game/game.cpp
    ${PLATFORM_SRC_FILES}
)

set(HEADER_FILES
	src/game/game.h
	src/game/timing/timer.h
    ${PLATFORM_HEADER_FILES}
)

add_executable(${EXECUTABLE} ${SRC_FILES} ${HEADER_FILES} ${PLATFORM_SRC_FILES})

target_link_libraries(${PROJECT_NAME}
    # PRIVATE ...
)

# Include directories for the main target
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    # ...
)


if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS_PLATFORM)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
elseif(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MACOS_PLATFORM)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(UNIX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX_PLATFORM)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:DEBUG>:DEBUG>
    $<$<CONFIG:RELEASE>:RELEASE>
)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:RELEASE>:-O3>
)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
