cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 17)

find_package(Git)

if(GIT_EXECUTABLE)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

if(PROJECT_VERSION STREQUAL "")
  set(PROJECT_VERSION 0.0.0)
  message(WARNING "Failed to determine version from Git tags. Using default version \"${PROJECT_VERSION}\".")
endif()

message("Version is \"${PROJECT_VERSION}\".")

project(fashio_mnist VERSION ${PROJECT_VERSION})
# project(fashio_mnist)

add_executable(fashio_mnist
    main.cpp
    tfclassifier.h
    tfclassifier.cpp
    helpers.cpp
    helpers.h
)

target_include_directories(fashio_mnist PUBLIC include)
target_link_libraries(fashio_mnist tensorflow)

find_package(GTest)

add_executable(test_fashio_mnist
    test/tftest.cpp
    helpers.cpp
    helpers.h
    tfclassifier.h
    tfclassifier.cpp
)

target_include_directories(test_fashio_mnist PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(test_fashio_mnist PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

include_directories(${GTEST_INCLUDE_DIRS}) 

target_link_libraries(test_${CMAKE_PROJECT_NAME} gmock gtest pthread tensorflow)

if(LINUX)
# -- install command was introduced in 3.15 version of cmake
# -- we can use sudo make install from build folder
    install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)
    set(CPACK_GENERATOR DEB)
    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
    set(CPACK_PACKAGE_CONTACT dmitriirylko@gmail.com)
    include(CPack)
endif()

# enable_testing()
# add_test(test_fashio_mnist test_fashio_mnist)

