cmake_minimum_required(VERSION 3.10)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
  set(PATCH_NUM $ENV{GITHUB_RUN_NUMBER})
else()
  set(PATCH_NUM 0)
endif()

project(my_allocator
  LANGUAGES CXX
  VERSION 0.0.${PATCH_NUM}
)

set(CMAKE_BUILD_TYPE Debug)

configure_file(version.h.in version.h)
include_directories(${CMAKE_BINARY_DIR})

option(BUILD_TESTS "Build unittests" OFF)

add_executable(my_allocator
			         src/main.cpp
			         src/allocator.h
			         src/list.h
)

target_compile_features(my_allocator PUBLIC cxx_std_14)
 

if(BUILD_TESTS)
    enable_testing()
	
	# Test target
	add_executable(
    Hello
    my_tests/test_hello.cpp
	)

	# Add src to the include directories for the test target
	target_include_directories(
    Hello PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
	)

	# Link test target against gtest libraries
	target_link_libraries(
    Hello PRIVATE
    gtest gtest_main
	)
	
	add_subdirectory(
		"${CMAKE_CURRENT_SOURCE_DIR}/googletests"
		"googletests"
	)
	if (MSVC)
		# @see https://github.com/google/googletest/blob/master/googletest/README.md
		# Visual Studio Dynamic vs Static Runtimes
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	
		target_compile_options(
			my_allocator PRIVATE
			/W4
		)
		target_compile_options(
			Hello PRIVATE
			/W4
		)
  else ()
    target_compile_options(
        my_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        Hello PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
	endif()
endif()

install(TARGETS my_allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

