cmake_minimum_required(VERSION 3.5)

project(crc_TEST)

set(MAIN_TEST crc_test.h tests.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929 # release-1.10.0
)

FetchContent_MakeAvailable(googletest)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(CMAKE_GTEST_)
add_executable(${PROJECT_NAME} ${MAIN_TEST})

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../crc_main
)

target_link_libraries(
        ${PROJECT_NAME}
        gtest_main
)

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME}
        XML_OUTPUT_DIR lab_1/Unit_test)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Werror -Wall -Wimplicit-fallthrough -pedantic-errors
            )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_HOME_DIRECTORY}/lab_1/Unit_test)
install(FILES ${MAIN_TEST} DESTINATION ${CMAKE_HOME_DIRECTORY}/lab_1/Unit_test )

#set(CPACK_GENERATOR "DEB")
#include(CPack)