cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
  set(PATCH_NUM $ENV{GITHUB_RUN_NUMBER})
else()
  set(PATCH_NUM 0)
endif()

project(MyApp LANGUAGES CXX
  VERSION 0.0${PATCH_NUM}
)

set(CMAKE_BUILD_TYPE Debug)

add_executable(MyApp
			   src/main.cpp
			   src/hello.h
			   src/hello.cpp
)

target_compile_features(MyApp PUBLIC cxx_std_11)

install(TARGETS MyApp RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

include(CPack)