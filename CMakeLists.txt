# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Project Metadata
cmake_minimum_required(VERSION 3.12)
project(
	sunkell
	VERSION 0.0.0
	LANGUAGES CXX
)

# Cache Variables
set(ENABLE_NONPORTABLE_OPTIMIZATIONS OFF CACHE BOOL "Enables optimizations that may prevent the target from working on other systems")
set(BUILD_EXAMPLES OFF CACHE BOOL "Build example applications")

# C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(tests)
