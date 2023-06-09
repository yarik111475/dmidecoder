cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME dmidecoder)
set(TARGET_NAME dmidecoder)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
    set(LINUX_LINK_STATIC
        -static-libgcc
        -static-libstdc++
        )
endif()

set(PROJECT_SOURCES
    main.cpp
    dmi/Entry.h
    dmi/Structure.h
    dmi/Decoder.h
    dmi/Decoder.cpp
)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(${TARGET_NAME}
    ${PROJECT_SOURCES}
)

target_link_libraries(${TARGET_NAME} PRIVATE
    Qt5::Core
    ${LINUX_LINK_STATIC}
)

install(TARGETS ${TARGET_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
