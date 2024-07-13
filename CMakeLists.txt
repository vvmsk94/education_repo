cmake_minimum_required(VERSION 3.10)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
  set(PATCH_NUM $ENV{GITHUB_RUN_NUMBER})
else()
  set(PATCH_NUM 0)
endif()

project(ip_filter
  LANGUAGES CXX
  VERSION 0.0.${PATCH_NUM}
)

set(CMAKE_BUILD_TYPE Debug)

configure_file(version.h.in version.h)
include_directories(${CMAKE_BINARY_DIR})

option(BUILD_TESTS "Build unittests" OFF)

#add_subdirectory(src)

add_executable(ip_filter
			         src/main.cpp
			         src/hello.h
			         src/hello.cpp
)

target_compile_features(ip_filter PUBLIC cxx_std_14)

#if(BUILD_TESTS)
#    enable_testing()
#	add_subdirectory(
#		"${CMAKE_CURRENT_SOURCE_DIR}/tests/v1.10.x/googletest"
#		"googletest"
#	)
#	if (MSVC)
#		# @see https://github.com/google/googletest/blob/master/googletest/README.md
#		# Visual Studio Dynamic vs Static Runtimes
#		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#	
#		target_compile_options(
#			ip_filter PRIVATE
#			/W4
#		)
#		target_compile_options(
#			test_list PRIVATE
#			/W4
#		)
#	endif()
#endif()

#install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

